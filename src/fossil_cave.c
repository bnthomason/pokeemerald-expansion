#include "global.h"
#include "malloc.h"
#include "bg.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "field_camera.h"
#include "field_effect.h"
#include "fieldmap.h"
#include "gpu_regs.h"
#include "menu.h"
#include "random.h"
#include "palette.h"
#include "palette_util.h"
#include "script.h"
#include "sound.h"
#include "sprite.h"
#include "task.h"
#include "window.h"
#include "constants/event_objects.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "constants/metatile_labels.h"

struct MetatileCoords
{
    u8 x;
    u8 y;
    u16 metatileId;
};

struct BgRegOffsets
{
    u16 bgHOFS;
    u16 bgVOFS;
};


struct FallAnim_Cave
{
    u8 *disintegrateRand;
    u8 disintegrateIdx;
};


#define TAG_CEILING_CRUMBLE 4000

#define FOSSIL_CAVE_GFX_LENGTH (sizeof(sBlankTile_Gfx) + sizeof(sFossilCave_Gfx))

static const struct SpriteSheet sCeilingCrumbleSpriteSheets[];
static const s16 sCeilingCrumblePositions[][3];

static void PlayerDescendFossilCave(u8);
static void DoScreenShake(u8);
static void IncrementCeilingCrumbleFinishedCount(void);
static void WaitCeilingCrumble(u8);
static void FinishCeilingCrumbleTask(u8);
static void CreateCeilingCrumbleSprites(void);
static void SpriteCB_CeilingCrumble(struct Sprite *);
static void DoFossilCaveDisintegration(u8);
static void InitFossilCaveShake(u8);
static void UpdateDisintegrationEffect(u8 *, u16, u8, u8, u8);


static const u8 ALIGNED(2) sBlankTile_Gfx[32] = {0};
static const u8 sFossilCave_Gfx[] = INCBIN_U8("graphics/misc/fossil_cave.4bpp");
static const u16 sFossilCaveTilemap[] = INCBIN_U16("graphics/misc/fossil_cave.bin");
static const u8 sFossilCaveCrumbles_Gfx[] = INCBIN_U8("graphics/misc/mirage_tower_crumbles.4bpp");
static const u16 sFossilCrumbles_Palette[] = INCBIN_U16("graphics/misc/mirage_tower_crumbles.gbapal");

static const s16 sCeilingCrumblePositions[][3] =
{
    {  0,  10,  65},
    { 17,   3,  50},
    {-12,   0,  75},
    { 10,  15,  90},
    {  7,   8,  65},
    {-18,   5,  75},
    { 22, -10,  55},
    {-24,  -4,  65},
};

static const struct SpriteSheet sCeilingCrumbleSpriteSheets[] =
{
    {sFossilCaveCrumbles_Gfx, sizeof(sFossilCaveCrumbles_Gfx), TAG_CEILING_CRUMBLE},
    {}
};

static const struct MetatileCoords sInvisibleFossilCaveMetatiles[] =
{
	{1, 3, 0x1DD},
	{2, 3, 0x1DC},
	{3, 3, 0x1DD},
	{4, 3, 0x1DC},
	{5, 3, 0x1DD},
	{6, 3, 0x1DC},
	{7, 3, 0x1DD},
	{8, 3, 0x1DC},
	{9, 3, 0x1DD},
	{10, 3, 0x1DC},
	{11, 3, 0x1DD},
	{12, 3, 0x1DC},
	{13, 3, 0x1DD},
	{14, 3, 0x1DC},
	{15, 3, 0x1DD},
	{1, 4, 0x1D5},
	{2, 4, 0x1D4},
	{3, 4, 0x1D5},
	{4, 4, 0x1D4},
	{5, 4, 0x1D5},
	{6, 4, 0x1D4},
	{7, 4, 0x1D5},
	{8, 4, 0x1D4},
	{9, 4, 0x1D5},
	{10, 4, 0x1D4},
	{11, 4, 0x1D5},
	{12, 4, 0x1D4},
	{13, 4, 0x1D5},
	{14, 4, 0x1D4},
	{15, 4, 0x1D5},
	{1, 5, 0x1DD},
	{2, 5, 0x1DC},
	{3, 5, 0x1DD},
	{4, 5, 0x1DC},
	{5, 5, 0x1DD},
	{6, 5, 0x1DC},
	{7, 5, 0x1DD},
	{8, 5, 0x1DC},
	{9, 5, 0x1DD},
	{10, 5, 0x1DC},
    {11, 5, 0x1DD},
	{12, 5, 0x1DC},
	{13, 5, 0x1DD},
	{14, 5, 0x1DC},
	{15, 5, 0x1DD},
	{6, 6, 0x1D4},
	{7, 6, 0x1D5},
	{8, 6, 0x1D4},
	{9, 6, 0x1D5},
	{10, 6, 0x1D4},
	{11, 6, 0x1D5},
	{6, 7, 0x1DC},
	{7, 7, 0x1DD},
	{8, 7, 0x1DC},
	{9, 7, 0x1DD},
	{10, 7, 0x1DC},
	{11, 7, 0x1DD},
};

static const union AnimCmd sAnim_CeilingCrumbleSmall[] =
{
    ANIMCMD_FRAME(0, 12),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const sAnims_CeilingCrumbleSmall[] =
{
    sAnim_CeilingCrumbleSmall,
};

static const struct OamData sOamData_CeilingCrumbleSmall =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(8x8),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(8x8),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};

static const struct SpriteTemplate sSpriteTemplate_CeilingCrumbleSmall =
{
    .tileTag = TAG_CEILING_CRUMBLE,
    .paletteTag = TAG_NONE,
    .oam = &sOamData_CeilingCrumbleSmall,
    .anims = sAnims_CeilingCrumbleSmall,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_CeilingCrumble
};

static const union AnimCmd sAnim_CeilingCrumbleLarge[] =
{
    ANIMCMD_FRAME(0, 12),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const sAnims_CeilingCrumbleLarge[] =
{
    sAnim_CeilingCrumbleLarge,
};

static const struct OamData sOamData_CeilingCrumbleLarge =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(16x16),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(16x16),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};

static const struct SpriteTemplate sSpriteTemplate_CeilingCrumbleLarge =
{
    .tileTag = TAG_CEILING_CRUMBLE,
    .paletteTag = TAG_NONE,
    .oam = &sOamData_CeilingCrumbleLarge,
    .anims = sAnims_CeilingCrumbleLarge,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_CeilingCrumble
};



EWRAM_DATA static u8 *sFossilCaveGfxBuffer = NULL;
EWRAM_DATA static u8 *sFossilCaveTilemapBuffer = NULL;
EWRAM_DATA static struct FallAnim_Cave *sFallingCave = NULL;
EWRAM_DATA static struct BgRegOffsets *sBgShakeOffsets = NULL;

// Holds data about the disintegration effect for Mirage Tower / the unchosen fossil.
// Never read, presumably for debugging
static u16 sDebug_DisintegrationData[8];

bool8 IsFossilTowerVisible(void)
{
    if (!(gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(ROUTE103) && gSaveBlock1Ptr->location.mapNum == MAP_NUM(ROUTE103)))
        return FALSE;
    return FlagGet(FLAG_FOSSIL_CAVE_VISIBLE);
}


void SetFossilCaveVisibility(void)
{

    if (VarGet(VAR_FOSSIL_CAVE_STATE))
    {
        // Mirage Tower event has already been completed, hide it
        FlagClear(FLAG_FOSSIL_CAVE_VISIBLE);
        return;
    }
    else
    {
        FlagSet(FLAG_FOSSIL_CAVE_VISIBLE);
        return;
    }

    FlagClear(FLAG_FOSSIL_CAVE_VISIBLE);
}
void StartPlayerDescendFossilCave(void)
{
    CreateTask(PlayerDescendFossilCave, 8);
}

static void PlayerDescendFossilCave(u8 taskId)
{
    u8 objectEventId;
    struct ObjectEvent *fallingPlayer;
    struct ObjectEvent *player;

    TryGetObjectEventIdByLocalIdAndMap(LOCALID_ROUTE103_PLAYER_FALLING, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup, &objectEventId);
    fallingPlayer = &gObjectEvents[objectEventId];
    gSprites[fallingPlayer->spriteId].y2 += 2;
    player = &gObjectEvents[gPlayerAvatar.objectEventId];
    if ((gSprites[fallingPlayer->spriteId].y + gSprites[fallingPlayer->spriteId].y2) >=
        (gSprites[player->spriteId].y + gSprites[player->spriteId].y2))
    {
        DestroyTask(taskId);
        ScriptContext_Enable();
    }
}

#define tXShakeOffset data[0]
#define tTimer        data[1]
#define tNumShakes    data[2]
#define tShakeDelay   data[3]
#define tYShakeOffset data[4]

static void StartScreenShake(u8 yShakeOffset, u8 xShakeOffset, u8 numShakes, u8 shakeDelay)
{
    u8 taskId = CreateTask(DoScreenShake, 9);
    gTasks[taskId].tXShakeOffset = xShakeOffset;
    gTasks[taskId].tTimer = 0;
    gTasks[taskId].tNumShakes = numShakes;
    gTasks[taskId].tShakeDelay = shakeDelay;
    gTasks[taskId].tYShakeOffset = yShakeOffset;
    SetCameraPanningCallback(NULL);
    PlaySE(SE_M_STRENGTH);
}

static void DoScreenShake(u8 taskId)
{
    s16 *data;

    data = gTasks[taskId].data;
    tTimer++;
    if (tTimer % tShakeDelay == 0)
    {
        tTimer = 0;
        tNumShakes--;
        tXShakeOffset = -tXShakeOffset;
        tYShakeOffset = -tYShakeOffset;
        SetCameraPanning(tXShakeOffset, tYShakeOffset);
        if (tNumShakes == 0)
        {
            IncrementCeilingCrumbleFinishedCount();
            DestroyTask(taskId);
            InstallCameraPanAheadCallback();
        }
    }
}

#undef tXShakeOffset
#undef tTimer
#undef tNumShakes
#undef tShakeDelay
#undef tYShakeOffset


static void IncrementCeilingCrumbleFinishedCount(void)
{
    u8 taskId = FindTaskIdByFunc(WaitCeilingCrumble);
    if (taskId != TASK_NONE)
        gTasks[taskId].data[0]++;
}


void DoFossilCaveCeilingCrumble(void)
{
    LoadSpriteSheets(sCeilingCrumbleSpriteSheets);
    CreateCeilingCrumbleSprites();
    CreateTask(WaitCeilingCrumble, 8);
    StartScreenShake(2, 1, 16, 3);
}



static void WaitCeilingCrumble(u8 taskId)
{
    u16 *data = (u16*)gTasks[taskId].data;
    data[1]++;
    // Either wait 1000 frames, or until all 16 crumble sprites and the one screen-shake task are completed.
    if (data[1] == 1000 || data[0] == 17)
        gTasks[taskId].func = FinishCeilingCrumbleTask;
}

static void FinishCeilingCrumbleTask(u8 taskId)
{
    FreeSpriteTilesByTag(TAG_CEILING_CRUMBLE);
    DestroyTask(taskId);
    ScriptContext_Enable();
}

static void CreateCeilingCrumbleSprites(void)
{
    u8 i;
    u8 spriteId;

    for (i = 0; i < 8; i++)
    {
        spriteId = CreateSprite(&sSpriteTemplate_CeilingCrumbleLarge, sCeilingCrumblePositions[i][0] + 120, sCeilingCrumblePositions[i][1], 8);
        gSprites[spriteId].oam.priority = 0;
        gSprites[spriteId].oam.paletteNum = 0;
        gSprites[spriteId].data[0] = i;
    }
    for (i = 0; i < 8; i++)
    {
        spriteId = CreateSprite(&sSpriteTemplate_CeilingCrumbleSmall, sCeilingCrumblePositions[i][0] + 115, sCeilingCrumblePositions[i][1] - 3, 8);
        gSprites[spriteId].oam.priority = 0;
        gSprites[spriteId].oam.paletteNum = 0;
        gSprites[spriteId].data[0] = i;
    }
}

static void SpriteCB_CeilingCrumble(struct Sprite *sprite)
{
    sprite->data[1] += 2;
    sprite->y2 = sprite->data[1] / 2;
    if(((sprite->y) + (sprite->y2)) >  sCeilingCrumblePositions[sprite->data[0]][2])
    {
        DestroySprite(sprite);
        IncrementCeilingCrumbleFinishedCount();
    }
}

static void SetInvisibleFossilCaveMetatiles(void)
{
    u8 i;
    for (i = 0; i < ARRAY_COUNT(sInvisibleFossilCaveMetatiles); i++)
        MapGridSetMetatileIdAt(sInvisibleFossilCaveMetatiles[i].x + MAP_OFFSET,
                               sInvisibleFossilCaveMetatiles[i].y + MAP_OFFSET,
                               sInvisibleFossilCaveMetatiles[i].metatileId);
    DrawWholeMapView();
}


void StartFossilCaveDisintegration(void)
{
    CreateTask(DoFossilCaveDisintegration, 9);
}

void StartFossilCaveShake(void)
{
    CreateTask(InitFossilCaveShake, 9);
}

static void SetBgShakeOffsets(void)
{
    SetGpuReg(REG_OFFSET_BG0HOFS, sBgShakeOffsets->bgHOFS);
    SetGpuReg(REG_OFFSET_BG0VOFS, sBgShakeOffsets->bgVOFS);
}

static void UpdateBgShake(u8 taskId)
{
    if (!gTasks[taskId].data[0])
    {
        sBgShakeOffsets->bgHOFS = -sBgShakeOffsets->bgHOFS;
        gTasks[taskId].data[0] = 2;
        SetBgShakeOffsets();
    }
    else
    {
        gTasks[taskId].data[0]--;
    }
}


#define tState data[0]

static void InitFossilCaveShake(u8 taskId)
{
    u8 zero;

    switch (gTasks[taskId].tState)
    {
    case 0:
        FreeAllWindowBuffers();
        SetBgAttribute(0, BG_ATTR_PRIORITY, 2);
        gTasks[taskId].tState++;
        break;
    case 1:
        sFossilCaveGfxBuffer = (u8 *)AllocZeroed(FOSSIL_CAVE_GFX_LENGTH);
        sFossilCaveTilemapBuffer = (u8 *)AllocZeroed(BG_SCREEN_SIZE);
        ChangeBgX(0, 0, BG_COORD_SET);
        ChangeBgY(0, 0, BG_COORD_SET);
        gTasks[taskId].tState++;
        break;
    case 2:
        CpuSet(sBlankTile_Gfx, sFossilCaveGfxBuffer, FOSSIL_CAVE_GFX_LENGTH / 2);
        LoadBgTiles(0, sFossilCaveGfxBuffer, FOSSIL_CAVE_GFX_LENGTH, 0);
        gTasks[taskId].tState++;
        break;
    case 3:
        SetBgTilemapBuffer(0, sFossilCaveTilemapBuffer);
        CopyToBgTilemapBufferRect_ChangePalette(0, &sFossilCaveTilemap, 12, 29, 6, 12, 17);
        CopyBgTilemapBufferToVram(0);
        gTasks[taskId].tState++;
        break;
    case 4:
        ShowBg(0);
        gTasks[taskId].tState++;
        break;
    case 5:
        SetInvisibleFossilCaveMetatiles();
        gTasks[taskId].tState++;
        break;
    case 6:
        sBgShakeOffsets = Alloc(sizeof(*sBgShakeOffsets));
        zero = 0;
        sBgShakeOffsets->bgHOFS = 2;
        sBgShakeOffsets->bgVOFS = zero;
        CreateTask(UpdateBgShake, 10);
        DestroyTask(taskId);
        ScriptContext_Enable();
        break;
    }
}


#define OUTER_BUFFER_LENGTH 0x60
#define INNER_BUFFER_LENGTH 0x30



static void DoFossilCaveDisintegration(u8 taskId)
{
    u8 bgShakeTaskId, j;
    u16 i;
    u8 index;

    switch (gTasks[taskId].tState)
    {
    case 1:
        sFallingCave = AllocZeroed(OUTER_BUFFER_LENGTH * sizeof(struct FallAnim_Cave));
        break;
    case 3:
        if (gTasks[taskId].data[3] <= (OUTER_BUFFER_LENGTH - 1))
        {
            if (gTasks[taskId].data[1] > 1)
            {
                // Initialize disintegration pattern
                index = gTasks[taskId].data[3];
                sFallingCave[index].disintegrateRand = Alloc(INNER_BUFFER_LENGTH);
                for (i = 0; i <= (INNER_BUFFER_LENGTH - 1); i++)
                    sFallingCave[index].disintegrateRand[i] = i;

                // Randomize disintegration pattern
                Shuffle(sFallingCave[index].disintegrateRand, INNER_BUFFER_LENGTH,
                    sizeof(sFallingCave[index].disintegrateRand[0]));

                if (gTasks[taskId].data[3] <= (OUTER_BUFFER_LENGTH - 1))
                    gTasks[taskId].data[3]++;
                gTasks[taskId].data[1] = 0;
            }
            gTasks[taskId].data[1]++;
        }
        index = gTasks[taskId].data[3];
        for (i = (u8)(gTasks[taskId].data[2]); i < index; i++)
        {
            for (j = 0; j < 1; j++)
            {
                UpdateDisintegrationEffect(sFossilCaveGfxBuffer,
                            (OUTER_BUFFER_LENGTH - 1 - i) * INNER_BUFFER_LENGTH + sFallingCave[i].disintegrateRand[sFallingCave[i].disintegrateIdx++],
                            0, INNER_BUFFER_LENGTH, 1);
            }
            if (sFallingCave[i].disintegrateIdx > (INNER_BUFFER_LENGTH - 1))
            {
                FREE_AND_SET_NULL(sFallingCave[i].disintegrateRand);
                gTasks[taskId].data[2]++;
                if ((i % 2) == 1)
                    sBgShakeOffsets->bgVOFS--;
            }
        }
        LoadBgTiles(0, sFossilCaveGfxBuffer, FOSSIL_CAVE_GFX_LENGTH, 0);
        if (sFallingCave[OUTER_BUFFER_LENGTH - 1].disintegrateIdx > INNER_BUFFER_LENGTH - 1)
            break;
        return;
    case 4:
        UnsetBgTilemapBuffer(0);
        bgShakeTaskId = FindTaskIdByFunc(UpdateBgShake);
        if (bgShakeTaskId != TASK_NONE)
            DestroyTask(bgShakeTaskId);
        sBgShakeOffsets->bgVOFS = sBgShakeOffsets->bgHOFS = 0;
        SetBgShakeOffsets();
        break;
    case 5:
        FREE_AND_SET_NULL(sBgShakeOffsets);
        FREE_AND_SET_NULL(sFallingCave);
        FREE_AND_SET_NULL(sFossilCaveGfxBuffer);
        FREE_AND_SET_NULL(sFossilCaveTilemapBuffer);
        break;
    case 6:
        SetGpuRegBits(REG_OFFSET_BG2CNT, BGCNT_PRIORITY(2));
        SetGpuRegBits(REG_OFFSET_BG0CNT, BGCNT_PRIORITY(0));
        SetBgAttribute(0, BG_ATTR_PRIORITY, 0);
        InitStandardTextBoxWindows();
        break;
    case 7:
        ShowBg(0);
        break;
    case 8:
        DestroyTask(taskId);
        ScriptContext_Enable();
        break;
    }
    gTasks[taskId].tState++;
}





static void UpdateDisintegrationEffect(u8 *tiles, u16 randId, u8 c, u8 size, u8 offset)
{
    u8 heightTiles, height, widthTiles, width;
    u16 var, baseOffset;
    u8 col, row;
    u8 flag, tileMask;

    height = randId / size;
    sDebug_DisintegrationData[0] = height;

    width = randId % size;
    sDebug_DisintegrationData[1] = width;

    row = height & 7;
    col = width & 7;
    sDebug_DisintegrationData[2] = height & 7;
    sDebug_DisintegrationData[3] = width & 7;

    widthTiles = width / 8;
    heightTiles = height / 8;
    sDebug_DisintegrationData[4] = width / 8;
    sDebug_DisintegrationData[5] = height / 8;

    var = (size / 8) * (heightTiles * 64) + (widthTiles * 64);
    sDebug_DisintegrationData[6] = var;

    baseOffset = var + ((row * 8) + col);
    baseOffset /= 2;
    sDebug_DisintegrationData[7] = var + ((row * 8) + col);

    flag = ((randId % 2) ^ 1);
    tileMask = (c << (flag << 2)) | 15 << (((flag ^ 1) << 2));
    tiles[baseOffset + (offset * 32)] &= tileMask;
}