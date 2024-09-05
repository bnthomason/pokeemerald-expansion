#include "global.h"
#include "survival_island.h"
#include "apprentice.h"
#include "event_data.h"
#include "battle_setup.h"
#include "overworld.h"
#include "random.h"
#include "text.h"
#include "main.h"
#include "international_string_util.h"
#include "battle.h"
#include "island_util.h"
#include "strings.h"
#include "recorded_battle.h"
#include "easy_chat.h"
#include "gym_leader_rematch.h"
#include "battle_transition.h"
#include "trainer_see.h"
#include "new_game.h"
#include "string_util.h"
#include "data.h"
#include "link.h"
#include "field_message_box.h"
#include "tv.h"
#include "battle_factory.h"
#include "constants/abilities.h"
#include "constants/apprentice.h"
#include "constants/battle_dome.h"
#include "constants/survival_island.h"
#include "constants/survival_island_mons.h"
#include "constants/battle_move_effects.h"
#include "constants/battle_tent.h"
#include "constants/battle_tent_mons.h"
#include "constants/battle_tent_trainers.h"
#include "constants/survival_master.h"
#include "constants/battle_partner.h"
#include "constants/island_util.h"
#include "constants/items.h"
#include "constants/trainers.h"
#include "constants/event_objects.h"
#include "constants/moves.h"


#define NUM_LAYOUT_OFFSETS 8

extern const struct MapLayout *const gMapLayouts[];

struct MasterWildMon
{
    u16 species;
    u8 lvl;
    u8 abilityNum;
    u16 moves[MAX_MON_MOVES];
};

struct MasterFloorTemplate
{
    u8 numItems;
    u8 numTrainers;
    u8 itemPositions;
    u8 trainerPositions;
    u8 runMultiplier;
    u8 layoutOffsets[NUM_LAYOUT_OFFSETS];
};

struct MasterTrainerEncounterMusic
{
    u8 trainerClass;
    u8 trainerEncounterMusic;
};
// EWRAM vars.
EWRAM_DATA const struct SurvivalIslandTrainer *gGameFacilityTrainers = NULL;
EWRAM_DATA const struct TrainerMon *gGameFacilityTrainerMon = NULL;

// IWRAM common
u16 gIslandTempParty[MAX_ISLAND_PARTY_SIZE];

// This file's functions.
static void InitMasterChallenge(void);
static void GetMasterData(void);
static void SetMasterData(void);
static void SetNextMasterOpponent(void);
static void SetMasterBattleWon(void);
// static void AwardSurvivalMasterRibbons(void);
static void SaveMasterChallenge(void);
static void GetOpponentIntroSpeech(void);
static void SurvivalMasterNop1(void);
static void SurvivalMasterNop2(void);
// static void LoadMultiPartnerCandidatesData(void);
// static void ShowPartnerCandidateMessage(void);
// static void LoadLinkMultiOpponentsData(void);
// static void MasterTryCloseLink(void);
// static void SetMultiPartnerGfx(void);
// static void SetMasterInterviewData(void);
// static void ValidateSurvivalMasterRecordChecksums(void);
// static void SaveCurrentWinStreak(void);
// static void ValidateApprenticesChecksums(void);
// static void SetNextBattleTentOpponent(void);
// static void CopyEReaderTrainerFarewellMessage(void);
// static void ClearSurvivalMasterRecord(struct EmeraldSurvivalMasterRecord *record);
static void FillTrainerParty(u16 trainerId, u8 firstMonId, u8 monCount);
// static void FillTentTrainerParty_(u16 trainerId, u8 firstMonId, u8 monCount);
// static void FillFactoryIslandTrainerParty(u16 trainerId, u8 firstMonId);
// static void FillFactoryTentTrainerParty(u16 trainerId, u8 firstMonId);
static u8 GetIslandTrainerFixedIvs(u16 trainerId);
// static void FillPartnerParty(u16 trainerId);
// #if FREE_SURVIVAL_ISLANDE_READER == FALSE
// static void SetEReaderTrainerChecksum(struct SurvivalMasterEReaderTrainer *ereaderTrainer);
// #endif //FREE_SURVIVAL_ISLANDE_READER
// static u8 SetTentPtrsGetLevel(void);

#include "data/survival_island/survival_island_trainer_mons.h"
#include "data/survival_island/survival_island_trainers.h"
#include "data/survival_island/survival_island_mons.h"

const u8 gMasterMaleGameFacilityClasses[30] =
{
    GAME_FACILITY_CLASS_RUIN_MANIAC,
    GAME_FACILITY_CLASS_TUBER_M,
    GAME_FACILITY_CLASS_COOLTRAINER_M,
    GAME_FACILITY_CLASS_RICH_BOY,
    GAME_FACILITY_CLASS_POKEMANIAC,
    GAME_FACILITY_CLASS_SWIMMER_M,
    GAME_FACILITY_CLASS_BLACK_BELT,
    GAME_FACILITY_CLASS_GUITARIST,
    GAME_FACILITY_CLASS_KINDLER,
    GAME_FACILITY_CLASS_CAMPER,
    GAME_FACILITY_CLASS_BUG_MANIAC,
    GAME_FACILITY_CLASS_PSYCHIC_M,
    GAME_FACILITY_CLASS_GENTLEMAN,
    GAME_FACILITY_CLASS_SCHOOL_KID_M,
    GAME_FACILITY_CLASS_POKEFAN_M,
    GAME_FACILITY_CLASS_EXPERT_M,
    GAME_FACILITY_CLASS_YOUNGSTER,
    GAME_FACILITY_CLASS_FISHERMAN,
    GAME_FACILITY_CLASS_CYCLING_TRIATHLETE_M,
    GAME_FACILITY_CLASS_RUNNING_TRIATHLETE_M,
    GAME_FACILITY_CLASS_SWIMMING_TRIATHLETE_M,
    GAME_FACILITY_CLASS_DRAGON_TAMER,
    GAME_FACILITY_CLASS_BIRD_KEEPER,
    GAME_FACILITY_CLASS_NINJA_BOY,
    GAME_FACILITY_CLASS_SAILOR,
    GAME_FACILITY_CLASS_COLLECTOR,
    GAME_FACILITY_CLASS_PKMN_BREEDER_M,
    GAME_FACILITY_CLASS_PKMN_RANGER_M,
    GAME_FACILITY_CLASS_BUG_CATCHER,
    GAME_FACILITY_CLASS_HIKER
};

const u8 gIslandFemaleGameFacilityClasses[20] =
{
    GAME_FACILITY_CLASS_AROMA_LADY,
    GAME_FACILITY_CLASS_TUBER_F,
    GAME_FACILITY_CLASS_COOLTRAINER_F,
    GAME_FACILITY_CLASS_HEX_MANIAC,
    GAME_FACILITY_CLASS_LADY,
    GAME_FACILITY_CLASS_BEAUTY,
    GAME_FACILITY_CLASS_PSYCHIC_F,
    GAME_FACILITY_CLASS_SCHOOL_KID_F,
    GAME_FACILITY_CLASS_POKEFAN_F,
    GAME_FACILITY_CLASS_EXPERT_F,
    GAME_FACILITY_CLASS_CYCLING_TRIATHLETE_F,
    GAME_FACILITY_CLASS_RUNNING_TRIATHLETE_F,
    GAME_FACILITY_CLASS_SWIMMING_TRIATHLETE_F,
    GAME_FACILITY_CLASS_BATTLE_GIRL,
    GAME_FACILITY_CLASS_PARASOL_LADY,
    GAME_FACILITY_CLASS_SWIMMER_F,
    GAME_FACILITY_CLASS_PICNICKER,
    GAME_FACILITY_CLASS_PKMN_BREEDER_F,
    GAME_FACILITY_CLASS_PKMN_RANGER_F,
    GAME_FACILITY_CLASS_LASS
};

const u16 gIslandMaleTrainerGfxIds[30] =
{
    OBJ_EVENT_GFX_HIKER,
    OBJ_EVENT_GFX_TUBER_M,
    OBJ_EVENT_GFX_MAN_3,
    OBJ_EVENT_GFX_RICH_BOY,
    OBJ_EVENT_GFX_MANIAC,
    OBJ_EVENT_GFX_RUNNING_TRIATHLETE_M,
    OBJ_EVENT_GFX_BLACK_BELT,
    OBJ_EVENT_GFX_MAN_5,
    OBJ_EVENT_GFX_MAN_5,
    OBJ_EVENT_GFX_CAMPER,
    OBJ_EVENT_GFX_MANIAC,
    OBJ_EVENT_GFX_PSYCHIC_M,
    OBJ_EVENT_GFX_GENTLEMAN,
    OBJ_EVENT_GFX_SCHOOL_KID_M,
    OBJ_EVENT_GFX_POKEFAN_M,
    OBJ_EVENT_GFX_EXPERT_M,
    OBJ_EVENT_GFX_YOUNGSTER,
    OBJ_EVENT_GFX_FISHERMAN,
    OBJ_EVENT_GFX_CYCLING_TRIATHLETE_M,
    OBJ_EVENT_GFX_RUNNING_TRIATHLETE_M,
    OBJ_EVENT_GFX_RUNNING_TRIATHLETE_M,
    OBJ_EVENT_GFX_MAN_3,
    OBJ_EVENT_GFX_MAN_5,
    OBJ_EVENT_GFX_NINJA_BOY,
    OBJ_EVENT_GFX_SAILOR,
    OBJ_EVENT_GFX_MANIAC,
    OBJ_EVENT_GFX_MAN_4,
    OBJ_EVENT_GFX_CAMPER,
    OBJ_EVENT_GFX_BUG_CATCHER,
    OBJ_EVENT_GFX_HIKER
};

const u16 gIslandFemaleTrainerGfxIds[20] =
{
    OBJ_EVENT_GFX_WOMAN_2,
    OBJ_EVENT_GFX_TUBER_F,
    OBJ_EVENT_GFX_WOMAN_5,
    OBJ_EVENT_GFX_HEX_MANIAC,
    OBJ_EVENT_GFX_WOMAN_2,
    OBJ_EVENT_GFX_BEAUTY,
    OBJ_EVENT_GFX_LASS,
    OBJ_EVENT_GFX_GIRL_3,
    OBJ_EVENT_GFX_POKEFAN_F,
    OBJ_EVENT_GFX_EXPERT_F,
    OBJ_EVENT_GFX_CYCLING_TRIATHLETE_F,
    OBJ_EVENT_GFX_RUNNING_TRIATHLETE_F,
    OBJ_EVENT_GFX_RUNNING_TRIATHLETE_F,
    OBJ_EVENT_GFX_GIRL_3,
    OBJ_EVENT_GFX_WOMAN_5,
    OBJ_EVENT_GFX_RUNNING_TRIATHLETE_F,
    OBJ_EVENT_GFX_PICNICKER,
    OBJ_EVENT_GFX_WOMAN_2,
    OBJ_EVENT_GFX_PICNICKER,
    OBJ_EVENT_GFX_LASS
};

// Excludes the unused RS_GAME_FACILITY_CLASS_BOARDER_1 and _2
static const u8 sRubyGameFacilityClassToEmerald[RS_FACILITY_CLASSES_COUNT - 2][2] =
{
    {RS_GAME_FACILITY_CLASS_AQUA_LEADER_ARCHIE, GAME_FACILITY_CLASS_AQUA_LEADER_ARCHIE},
    {RS_GAME_FACILITY_CLASS_AQUA_GRUNT_M, GAME_FACILITY_CLASS_AQUA_GRUNT_M},
    {RS_GAME_FACILITY_CLASS_AQUA_GRUNT_F, GAME_FACILITY_CLASS_AQUA_GRUNT_F},
    {RS_GAME_FACILITY_CLASS_AROMA_LADY, GAME_FACILITY_CLASS_AROMA_LADY},
    {RS_GAME_FACILITY_CLASS_RUIN_MANIAC, GAME_FACILITY_CLASS_RUIN_MANIAC},
    {RS_GAME_FACILITY_CLASS_INTERVIEWER, GAME_FACILITY_CLASS_INTERVIEWER},
    {RS_GAME_FACILITY_CLASS_TUBER_F, GAME_FACILITY_CLASS_TUBER_F},
    {RS_GAME_FACILITY_CLASS_TUBER_M, GAME_FACILITY_CLASS_TUBER_M},
    {RS_GAME_FACILITY_CLASS_COOLTRAINER_M, GAME_FACILITY_CLASS_COOLTRAINER_M},
    {RS_GAME_FACILITY_CLASS_COOLTRAINER_F, GAME_FACILITY_CLASS_COOLTRAINER_F},
    {RS_GAME_FACILITY_CLASS_HEX_MANIAC, GAME_FACILITY_CLASS_HEX_MANIAC},
    {RS_GAME_FACILITY_CLASS_LADY, GAME_FACILITY_CLASS_LADY},
    {RS_GAME_FACILITY_CLASS_BEAUTY, GAME_FACILITY_CLASS_BEAUTY},
    {RS_GAME_FACILITY_CLASS_RICH_BOY, GAME_FACILITY_CLASS_RICH_BOY},
    {RS_GAME_FACILITY_CLASS_POKEMANIAC, GAME_FACILITY_CLASS_POKEMANIAC},
    {RS_GAME_FACILITY_CLASS_SWIMMER_M, GAME_FACILITY_CLASS_SWIMMER_M},
    {RS_GAME_FACILITY_CLASS_BLACK_BELT, GAME_FACILITY_CLASS_BLACK_BELT},
    {RS_GAME_FACILITY_CLASS_GUITARIST, GAME_FACILITY_CLASS_GUITARIST},
    {RS_GAME_FACILITY_CLASS_KINDLER, GAME_FACILITY_CLASS_KINDLER},
    {RS_GAME_FACILITY_CLASS_CAMPER, GAME_FACILITY_CLASS_CAMPER},
    {RS_GAME_FACILITY_CLASS_BUG_MANIAC, GAME_FACILITY_CLASS_BUG_MANIAC},
    {RS_GAME_FACILITY_CLASS_PSYCHIC_M, GAME_FACILITY_CLASS_PSYCHIC_M},
    {RS_GAME_FACILITY_CLASS_PSYCHIC_F, GAME_FACILITY_CLASS_PSYCHIC_F},
    {RS_GAME_FACILITY_CLASS_GENTLEMAN, GAME_FACILITY_CLASS_GENTLEMAN},
    {RS_GAME_FACILITY_CLASS_ELITE_FOUR_M, GAME_FACILITY_CLASS_ELITE_FOUR_SIDNEY},
    {RS_GAME_FACILITY_CLASS_ELITE_FOUR_F, GAME_FACILITY_CLASS_ELITE_FOUR_PHOEBE},
    {RS_GAME_FACILITY_CLASS_LEADER_F, GAME_FACILITY_CLASS_LEADER_ROXANNE},
    {RS_GAME_FACILITY_CLASS_LEADER_M, GAME_FACILITY_CLASS_LEADER_BRAWLY},
    {RS_GAME_FACILITY_CLASS_LEADER_MF, GAME_FACILITY_CLASS_LEADER_TATE_AND_LIZA},
    {RS_GAME_FACILITY_CLASS_SCHOOL_KID_M, GAME_FACILITY_CLASS_SCHOOL_KID_M},
    {RS_GAME_FACILITY_CLASS_SCHOOL_KID_F, GAME_FACILITY_CLASS_SCHOOL_KID_F},
    {RS_GAME_FACILITY_CLASS_SR_AND_JR, GAME_FACILITY_CLASS_SR_AND_JR},
    {RS_GAME_FACILITY_CLASS_POKEFAN_M, GAME_FACILITY_CLASS_POKEFAN_M},
    {RS_GAME_FACILITY_CLASS_POKEFAN_F, GAME_FACILITY_CLASS_POKEFAN_F},
    {RS_GAME_FACILITY_CLASS_EXPERT_M, GAME_FACILITY_CLASS_EXPERT_M},
    {RS_GAME_FACILITY_CLASS_EXPERT_F, GAME_FACILITY_CLASS_EXPERT_F},
    {RS_GAME_FACILITY_CLASS_YOUNGSTER, GAME_FACILITY_CLASS_YOUNGSTER},
    {RS_GAME_FACILITY_CLASS_CHAMPION, GAME_FACILITY_CLASS_CHAMPION_WALLACE},
    {RS_GAME_FACILITY_CLASS_FISHERMAN, GAME_FACILITY_CLASS_FISHERMAN},
    {RS_GAME_FACILITY_CLASS_CYCLING_TRIATHLETE_M, GAME_FACILITY_CLASS_CYCLING_TRIATHLETE_M},
    {RS_GAME_FACILITY_CLASS_CYCLING_TRIATHLETE_F, GAME_FACILITY_CLASS_CYCLING_TRIATHLETE_F},
    {RS_GAME_FACILITY_CLASS_RUNNING_TRIATHLETE_M, GAME_FACILITY_CLASS_RUNNING_TRIATHLETE_M},
    {RS_GAME_FACILITY_CLASS_RUNNING_TRIATHLETE_F, GAME_FACILITY_CLASS_RUNNING_TRIATHLETE_F},
    {RS_GAME_FACILITY_CLASS_SWIMMING_TRIATHLETE_M, GAME_FACILITY_CLASS_SWIMMING_TRIATHLETE_M},
    {RS_GAME_FACILITY_CLASS_SWIMMING_TRIATHLETE_F, GAME_FACILITY_CLASS_SWIMMING_TRIATHLETE_F},
    {RS_GAME_FACILITY_CLASS_DRAGON_TAMER, GAME_FACILITY_CLASS_DRAGON_TAMER},
    {RS_GAME_FACILITY_CLASS_BIRD_KEEPER, GAME_FACILITY_CLASS_BIRD_KEEPER},
    {RS_GAME_FACILITY_CLASS_NINJA_BOY, GAME_FACILITY_CLASS_NINJA_BOY},
    {RS_GAME_FACILITY_CLASS_BATTLE_GIRL, GAME_FACILITY_CLASS_BATTLE_GIRL},
    {RS_GAME_FACILITY_CLASS_PARASOL_LADY, GAME_FACILITY_CLASS_PARASOL_LADY},
    {RS_GAME_FACILITY_CLASS_SWIMMER_F, GAME_FACILITY_CLASS_SWIMMER_F},
    {RS_GAME_FACILITY_CLASS_PICNICKER, GAME_FACILITY_CLASS_PICNICKER},
    {RS_GAME_FACILITY_CLASS_TWINS, GAME_FACILITY_CLASS_TWINS},
    {RS_GAME_FACILITY_CLASS_SAILOR, GAME_FACILITY_CLASS_SAILOR},
    {RS_GAME_FACILITY_CLASS_COLLECTOR, GAME_FACILITY_CLASS_COLLECTOR},
    {RS_GAME_FACILITY_CLASS_WALLY, GAME_FACILITY_CLASS_WALLY},
    {RS_GAME_FACILITY_CLASS_BRENDAN_1, GAME_FACILITY_CLASS_BRENDAN},
    {RS_GAME_FACILITY_CLASS_BRENDAN_2, GAME_FACILITY_CLASS_BRENDAN_2},
    {RS_GAME_FACILITY_CLASS_BRENDAN_3, GAME_FACILITY_CLASS_BRENDAN_3},
    {RS_GAME_FACILITY_CLASS_MAY_1, GAME_FACILITY_CLASS_MAY},
    {RS_GAME_FACILITY_CLASS_MAY_2, GAME_FACILITY_CLASS_MAY_2},
    {RS_GAME_FACILITY_CLASS_MAY_3, GAME_FACILITY_CLASS_MAY_3},
    {RS_GAME_FACILITY_CLASS_PKMN_BREEDER_M, GAME_FACILITY_CLASS_PKMN_BREEDER_M},
    {RS_GAME_FACILITY_CLASS_PKMN_BREEDER_F, GAME_FACILITY_CLASS_PKMN_BREEDER_F},
    {RS_GAME_FACILITY_CLASS_PKMN_RANGER_M, GAME_FACILITY_CLASS_PKMN_RANGER_M},
    {RS_GAME_FACILITY_CLASS_PKMN_RANGER_F, GAME_FACILITY_CLASS_PKMN_RANGER_F},
    {RS_GAME_FACILITY_CLASS_MAGMA_LEADER, GAME_FACILITY_CLASS_MAGMA_LEADER_MAXIE},
    {RS_GAME_FACILITY_CLASS_MAGMA_GRUNT_M, GAME_FACILITY_CLASS_MAGMA_GRUNT_M},
    {RS_GAME_FACILITY_CLASS_MAGMA_GRUNT_F, GAME_FACILITY_CLASS_MAGMA_GRUNT_F},
    {RS_GAME_FACILITY_CLASS_LASS, GAME_FACILITY_CLASS_LASS},
    {RS_GAME_FACILITY_CLASS_BUG_CATCHER, GAME_FACILITY_CLASS_BUG_CATCHER},
    {RS_GAME_FACILITY_CLASS_HIKER, GAME_FACILITY_CLASS_HIKER},
    {RS_GAME_FACILITY_CLASS_YOUNG_COUPLE, GAME_FACILITY_CLASS_YOUNG_COUPLE},
    {RS_GAME_FACILITY_CLASS_OLD_COUPLE, GAME_FACILITY_CLASS_OLD_COUPLE},
    {RS_GAME_FACILITY_CLASS_SIS_AND_BRO, GAME_FACILITY_CLASS_SIS_AND_BRO},
};

#define PARTNER_TEXTS(name)                                             \
    SurvivalIsland_SurvivalMasterMultiPartnerRoom_Text_##name##Intro,      \
    SurvivalIsland_SurvivalMasterMultiPartnerRoom_Text_##name##Mon1,       \
    SurvivalIsland_SurvivalMasterMultiPartnerRoom_Text_##name##Mon2Ask,    \
    SurvivalIsland_SurvivalMasterMultiPartnerRoom_Text_##name##Accept,     \
    SurvivalIsland_SurvivalMasterMultiPartnerRoom_Text_##name##Reject

static const u8 *const sPartnerApprenticeTexts1[] =
{
    PARTNER_TEXTS(Apprentice1)
};

static const u8 *const sPartnerApprenticeTexts2[] =
{
    PARTNER_TEXTS(Apprentice2)
};

static const u8 *const sPartnerApprenticeTexts3[] =
{
    PARTNER_TEXTS(Apprentice3)
};

static const u8 *const sPartnerApprenticeTexts4[] =
{
    PARTNER_TEXTS(Apprentice4)
};

static const u8 *const sPartnerApprenticeTexts5[] =
{
    PARTNER_TEXTS(Apprentice5)
};

static const u8 *const sPartnerApprenticeTexts6[] =
{
     PARTNER_TEXTS(Apprentice6)
};

static const u8 *const sPartnerApprenticeTexts7[] =
{
     PARTNER_TEXTS(Apprentice7)
};

static const u8 *const sPartnerApprenticeTexts8[] =
{
     PARTNER_TEXTS(Apprentice8)
};

static const u8 *const sPartnerApprenticeTexts9[] =
{
     PARTNER_TEXTS(Apprentice9)
};

static const u8 *const sPartnerApprenticeTexts10[] =
{
     PARTNER_TEXTS(Apprentice10)
};

static const u8 *const sPartnerApprenticeTexts11[] =
{
     PARTNER_TEXTS(Apprentice11)
};

static const u8 *const sPartnerApprenticeTexts12[] =
{
     PARTNER_TEXTS(Apprentice12)
};

static const u8 *const sPartnerApprenticeTexts13[] =
{
     PARTNER_TEXTS(Apprentice13)
};

static const u8 *const sPartnerApprenticeTexts14[] =
{
     PARTNER_TEXTS(Apprentice14)
};

static const u8 *const sPartnerApprenticeTexts15[] =
{
     PARTNER_TEXTS(Apprentice15)
};

static const u8 *const sPartnerApprenticeTexts16[] =
{
     PARTNER_TEXTS(Apprentice16)
};

static const u8 *const sPartnerTextsLass[] =
{
    PARTNER_TEXTS(Lass)
};

static const u8 *const sPartnerTextsYoungster[] =
{
    PARTNER_TEXTS(Youngster)
};

static const u8 *const sPartnerTextsHiker[] =
{
    PARTNER_TEXTS(Hiker)
};

static const u8 *const sPartnerTextsBeauty[] =
{
    PARTNER_TEXTS(Beauty)
};

static const u8 *const sPartnerTextsFisherman[] =
{
    PARTNER_TEXTS(Fisherman)
};

static const u8 *const sPartnerTextsLady[] =
{
    PARTNER_TEXTS(Lady)
};

static const u8 *const sPartnerTextsCyclingTriathleteF[] =
{
    PARTNER_TEXTS(CyclingTriathleteF)
};

static const u8 *const sPartnerTextsBugCatcher[] =
{
    PARTNER_TEXTS(BugCatcher)
};

static const u8 *const sPartnerTextsSchoolKidM[] =
{
    PARTNER_TEXTS(SchoolKidM)
};

static const u8 *const sPartnerTextsRichBoy[] =
{
    PARTNER_TEXTS(RichBoy)
};

static const u8 *const sPartnerTextsBlackBelt[] =
{
    PARTNER_TEXTS(BlackBelt)
};

static const u8 *const sPartnerTextsTuberF[] =
{
    PARTNER_TEXTS(TuberF)
};

static const u8 *const sPartnerTextsHexManiac[] =
{
    PARTNER_TEXTS(HexManiac)
};

static const u8 *const sPartnerTextsPkmnBreederM[] =
{
    PARTNER_TEXTS(PkmnBreederM)
};

static const u8 *const sPartnerTextsRunningTriathleteF[] =
{
    PARTNER_TEXTS(RunningTriathleteF)
};

static const u8 *const sPartnerTextsRunningTriathleteM[] =
{
    PARTNER_TEXTS(RunningTriathleteM)
};

static const u8 *const sPartnerTextsBattleGirl[] =
{
    PARTNER_TEXTS(BattleGirl)
};

static const u8 *const sPartnerTextsCyclingTriathleteM[] =
{
    PARTNER_TEXTS(CyclingTriathleteM)
};

static const u8 *const sPartnerTextsTuberM[] =
{
    PARTNER_TEXTS(TuberM)
};

static const u8 *const sPartnerTextsGuitarist[] =
{
    PARTNER_TEXTS(Guitarist)
};

static const u8 *const sPartnerTextsGentleman[] =
{
    PARTNER_TEXTS(Gentleman)
};

static const u8 *const sPartnerTextsPokefanM[] =
{
    PARTNER_TEXTS(PokefanM)
};

static const u8 *const sPartnerTextsExpertM[] =
{
    PARTNER_TEXTS(ExpertM)
};

static const u8 *const sPartnerTextsExpertF[] =
{
    PARTNER_TEXTS(ExpertF)
};

static const u8 *const sPartnerTextsDragonTamer[] =
{
    PARTNER_TEXTS(DragonTamer)
};

static const u8 *const sPartnerTextsBirdKeeper[] =
{
    PARTNER_TEXTS(BirdKeeper)
};

static const u8 *const sPartnerTextsNinjaBoy[] =
{
    PARTNER_TEXTS(NinjaBoy)
};

static const u8 *const sPartnerTextsParasolLady[] =
{
    PARTNER_TEXTS(ParasolLady)
};

static const u8 *const sPartnerTextsBugManiac[] =
{
    PARTNER_TEXTS(BugManiac)
};

static const u8 *const sPartnerTextsSailor[] =
{
    PARTNER_TEXTS(Sailor)
};

static const u8 *const sPartnerTextsCollector[] =
{
    PARTNER_TEXTS(Collector)
};

static const u8 *const sPartnerTextsPkmnRangerM[] =
{
    PARTNER_TEXTS(PkmnRangerM)
};

static const u8 *const sPartnerTextsPkmnRangerF[] =
{
    PARTNER_TEXTS(PkmnRangerF)
};

static const u8 *const sPartnerTextsAromaLady[] =
{
    PARTNER_TEXTS(AromaLady)
};

static const u8 *const sPartnerTextsRuinManiac[] =
{
    PARTNER_TEXTS(RuinManiac)
};

static const u8 *const sPartnerTextsCoolTrainerM[] =
{
    PARTNER_TEXTS(CoolTrainerM)
};

static const u8 *const sPartnerTextsCoolTrainerF[] =
{
    PARTNER_TEXTS(CoolTrainerF)
};

static const u8 *const sPartnerTextsPokemaniac[] =
{
    PARTNER_TEXTS(Pokemaniac)
};

static const u8 *const sPartnerTextsKindler[] =
{
    PARTNER_TEXTS(Kindler)
};

static const u8 *const sPartnerTextsCamper[] =
{
    PARTNER_TEXTS(Camper)
};

static const u8 *const sPartnerTextsPicnicker[] =
{
    PARTNER_TEXTS(Picnicker)
};

static const u8 *const sPartnerTextsPsychicM[] =
{
    PARTNER_TEXTS(PsychicM)
};

static const u8 *const sPartnerTextsPsychicF[] =
{
    PARTNER_TEXTS(PsychicF)
};

static const u8 *const sPartnerTextsSchoolKidF[] =
{
    PARTNER_TEXTS(SchoolKidF)
};

static const u8 *const sPartnerTextsPkmnBreederF[] =
{
    PARTNER_TEXTS(PkmnBreederF)
};

static const u8 *const sPartnerTextsPokefanF[] =
{
    PARTNER_TEXTS(PokefanF)
};

static const u8 *const sPartnerTextsSwimmerF[] =
{
    PARTNER_TEXTS(SwimmerF)
};

static const u8 *const sPartnerTextsSwimmingTriathleteM[] =
{
    PARTNER_TEXTS(SwimmingTriathleteM)
};

static const u8 *const sPartnerTextsSwimmingTriathleteF[] =
{
    PARTNER_TEXTS(SwimmingTriathleteF)
};

static const u8 *const sPartnerTextsSwimmerM[] =
{
    PARTNER_TEXTS(SwimmerM)
};

struct
{
    u32 facilityClass;
    const u8 *const *strings;
} static const sPartnerTrainerTextTables[] =
{
    {FACILITY_CLASS_LASS,                  sPartnerTextsLass},
    {FACILITY_CLASS_YOUNGSTER,             sPartnerTextsYoungster},
    {FACILITY_CLASS_HIKER,                 sPartnerTextsHiker},
    {FACILITY_CLASS_BEAUTY,                sPartnerTextsBeauty},
    {FACILITY_CLASS_FISHERMAN,             sPartnerTextsFisherman},
    {FACILITY_CLASS_LADY,                  sPartnerTextsLady},
    {FACILITY_CLASS_CYCLING_TRIATHLETE_F,  sPartnerTextsCyclingTriathleteF},
    {FACILITY_CLASS_BUG_CATCHER,           sPartnerTextsBugCatcher},
    {FACILITY_CLASS_SCHOOL_KID_M,          sPartnerTextsSchoolKidM},
    {FACILITY_CLASS_RICH_BOY,              sPartnerTextsRichBoy},
    {FACILITY_CLASS_BLACK_BELT,            sPartnerTextsBlackBelt},
    {FACILITY_CLASS_TUBER_F,               sPartnerTextsTuberF},
    {FACILITY_CLASS_HEX_MANIAC,            sPartnerTextsHexManiac},
    {FACILITY_CLASS_PKMN_BREEDER_M,        sPartnerTextsPkmnBreederM},
    {FACILITY_CLASS_RUNNING_TRIATHLETE_F,  sPartnerTextsRunningTriathleteF},
    {FACILITY_CLASS_RUNNING_TRIATHLETE_M,  sPartnerTextsRunningTriathleteM},
    {FACILITY_CLASS_BATTLE_GIRL,           sPartnerTextsBattleGirl},
    {FACILITY_CLASS_CYCLING_TRIATHLETE_M,  sPartnerTextsCyclingTriathleteM},
    {FACILITY_CLASS_TUBER_M,               sPartnerTextsTuberM},
    {FACILITY_CLASS_GUITARIST,             sPartnerTextsGuitarist},
    {FACILITY_CLASS_GENTLEMAN,             sPartnerTextsGentleman},
    {FACILITY_CLASS_POKEFAN_M,             sPartnerTextsPokefanM},
    {FACILITY_CLASS_EXPERT_M,              sPartnerTextsExpertM},
    {FACILITY_CLASS_EXPERT_F,              sPartnerTextsExpertF},
    {FACILITY_CLASS_DRAGON_TAMER,          sPartnerTextsDragonTamer},
    {FACILITY_CLASS_BIRD_KEEPER,           sPartnerTextsBirdKeeper},
    {FACILITY_CLASS_NINJA_BOY,             sPartnerTextsNinjaBoy},
    {FACILITY_CLASS_PARASOL_LADY,          sPartnerTextsParasolLady},
    {FACILITY_CLASS_BUG_MANIAC,            sPartnerTextsBugManiac},
    {FACILITY_CLASS_SAILOR,                sPartnerTextsSailor},
    {FACILITY_CLASS_COLLECTOR,             sPartnerTextsCollector},
    {FACILITY_CLASS_PKMN_RANGER_M,         sPartnerTextsPkmnRangerM},
    {FACILITY_CLASS_PKMN_RANGER_F,         sPartnerTextsPkmnRangerF},
    {FACILITY_CLASS_AROMA_LADY,            sPartnerTextsAromaLady},
    {FACILITY_CLASS_RUIN_MANIAC,           sPartnerTextsRuinManiac},
    {FACILITY_CLASS_COOLTRAINER_M,         sPartnerTextsCoolTrainerM},
    {FACILITY_CLASS_COOLTRAINER_F,         sPartnerTextsCoolTrainerF},
    {FACILITY_CLASS_POKEMANIAC,            sPartnerTextsPokemaniac},
    {FACILITY_CLASS_KINDLER,               sPartnerTextsKindler},
    {FACILITY_CLASS_CAMPER,                sPartnerTextsCamper},
    {FACILITY_CLASS_PICNICKER,             sPartnerTextsPicnicker},
    {FACILITY_CLASS_PSYCHIC_M,             sPartnerTextsPsychicM},
    {FACILITY_CLASS_PSYCHIC_F,             sPartnerTextsPsychicF},
    {FACILITY_CLASS_SCHOOL_KID_F,          sPartnerTextsSchoolKidF},
    {FACILITY_CLASS_PKMN_BREEDER_F,        sPartnerTextsPkmnBreederF},
    {FACILITY_CLASS_POKEFAN_F,             sPartnerTextsPokefanF},
    {FACILITY_CLASS_SWIMMER_F,             sPartnerTextsSwimmerF},
    {FACILITY_CLASS_SWIMMING_TRIATHLETE_M, sPartnerTextsSwimmingTriathleteM},
    {FACILITY_CLASS_SWIMMING_TRIATHLETE_F, sPartnerTextsSwimmingTriathleteF},
    {FACILITY_CLASS_SWIMMER_M,             sPartnerTextsSwimmerM}
};

static const u8 *const *const sPartnerApprenticeTextTables[NUM_APPRENTICES] =
{
    sPartnerApprenticeTexts1,
    sPartnerApprenticeTexts2,
    sPartnerApprenticeTexts3,
    sPartnerApprenticeTexts4,
    sPartnerApprenticeTexts5,
    sPartnerApprenticeTexts6,
    sPartnerApprenticeTexts7,
    sPartnerApprenticeTexts8,
    sPartnerApprenticeTexts9,
    sPartnerApprenticeTexts10,
    sPartnerApprenticeTexts11,
    sPartnerApprenticeTexts12,
    sPartnerApprenticeTexts13,
    sPartnerApprenticeTexts14,
    sPartnerApprenticeTexts15,
    sPartnerApprenticeTexts16
};

#include "data/battle_island/battle_tent.h"

#include "data/partner_parties.h"
const struct Trainer gBattlePartners[] =
{
#include "data/battle_partners.h"
};

static void (* const sSurvivalMasterFuncs[])(void) =
{
    [SURVIVAL_MASTER_FUNC_INIT]                = InitMasterChallenge,
    [SURVIVAL_MASTER_FUNC_GET_DATA]            = GetMasterData,
    [SURVIVAL_MASTER_FUNC_SET_DATA]            = SetMasterData,
    [SURVIVAL_MASTER_FUNC_SET_OPPONENT]        = SetNextGameFacilityOpponent,
    [SURVIVAL_MASTER_FUNC_SET_BATTLE_WON]      = SetMasterBattleWon,
    [SURVIVAL_MASTER_FUNC_GIVE_RIBBONS]        = AwardSurvivalMasterRibbons,
    [SURVIVAL_MASTER_FUNC_SAVE]                = SaveMasterChallenge,
    [SURVIVAL_MASTER_FUNC_GET_OPPONENT_INTRO]  = GetOpponentIntroSpeech,
    [SURVIVAL_MASTER_FUNC_NOP]                 = SurvivalMasterNop1,
    [SURVIVAL_MASTER_FUNC_NOP2]                = SurvivalMasterNop2,
    [SURVIVAL_MASTER_FUNC_LOAD_PARTNERS]       = LoadMultiPartnerCandidatesData,
    [SURVIVAL_MASTER_FUNC_PARTNER_MSG]         = ShowPartnerCandidateMessage,
    [SURVIVAL_MASTER_FUNC_LOAD_LINK_OPPONENTS] = LoadLinkMultiOpponentsData,
    [SURVIVAL_MASTER_FUNC_TRY_CLOSE_LINK]      = MasterTryCloseLink,
    [SURVIVAL_MASTER_FUNC_SET_PARTNER_GFX]     = SetMultiPartnerGfx,
    [SURVIVAL_MASTER_FUNC_SET_INTERVIEW_DATA]  = SetMasterInterviewData,
};

static const u32 sWinStreakFlags[][2] =
{
    {STREAK_TOWER_SINGLES_50,     STREAK_TOWER_SINGLES_OPEN},
    {STREAK_TOWER_DOUBLES_50,     STREAK_TOWER_DOUBLES_OPEN},
    {STREAK_TOWER_MULTIS_50,      STREAK_TOWER_MULTIS_OPEN},
    {STREAK_TOWER_LINK_MULTIS_50, STREAK_TOWER_LINK_MULTIS_OPEN},
};

static const u32 sWinStreakMasks[][2] =
{
    {~(STREAK_TOWER_SINGLES_50),     ~(STREAK_TOWER_SINGLES_OPEN)},
    {~(STREAK_TOWER_DOUBLES_50),     ~(STREAK_TOWER_DOUBLES_OPEN)},
    {~(STREAK_TOWER_MULTIS_50),      ~(STREAK_TOWER_MULTIS_OPEN)},
    {~(STREAK_TOWER_LINK_MULTIS_50), ~(STREAK_TOWER_LINK_MULTIS_OPEN)},
};

// The challenge number at which an Apprentice can appear, depending on how many of their questions were answered
static const u8 sApprenticeChallengeThreshold[MAX_APPRENTICE_QUESTIONS] =
{
    1, 2, 3, 4, 5, 8, 9, 10, 11, 12
};

// Unclear why this was duplicated
static const u8 sSurvivalMasterPartySizes2[] =
{
    [ISLAND_MODE_SINGLES]     = ISLAND_PARTY_SIZE,
    [ISLAND_MODE_DOUBLES]     = ISLAND_DOUBLES_PARTY_SIZE,
    [ISLAND_MODE_MULTIS]      = ISLAND_MULTI_PARTY_SIZE,
    [ISLAND_MODE_LINK_MULTIS] = ISLAND_MULTI_PARTY_SIZE,
};

// Trainer ID ranges for possible island trainers to encounter on particular challenges
// Trainers are scaled by difficulty, so higher trainer IDs have better teams
static const u16 sIslandTrainerIdRanges[][2] =
{
    {ISLAND_TRAINER_BRADY,   ISLAND_TRAINER_JILL},   //   0 -  99
    {ISLAND_TRAINER_TREVIN,  ISLAND_TRAINER_CHLOE},  //  80 - 119
    {ISLAND_TRAINER_ERIK,    ISLAND_TRAINER_SOFIA},  // 100 - 139
    {ISLAND_TRAINER_NORTON,  ISLAND_TRAINER_JAZLYN}, // 120 - 159
    {ISLAND_TRAINER_BRADEN,  ISLAND_TRAINER_ALISON}, // 140 - 179
    {ISLAND_TRAINER_ZACHERY, ISLAND_TRAINER_LAMAR},  // 160 - 199
    {ISLAND_TRAINER_HANK,    ISLAND_TRAINER_TESS},   // 180 - 219
    {ISLAND_TRAINER_JAXON,   ISLAND_TRAINER_GRETEL}, // 200 - 299
};

static const u16 sIslandTrainerIdRangesHard[][2] =
{
    {ISLAND_TRAINER_ERIK,    ISLAND_TRAINER_CHLOE},  // 100 - 119
    {ISLAND_TRAINER_NORTON,  ISLAND_TRAINER_SOFIA},  // 120 - 139
    {ISLAND_TRAINER_BRADEN,  ISLAND_TRAINER_JAZLYN}, // 140 - 159
    {ISLAND_TRAINER_ZACHERY, ISLAND_TRAINER_ALISON}, // 160 - 179
    {ISLAND_TRAINER_HANK,    ISLAND_TRAINER_LAMAR},  // 180 - 199
    {ISLAND_TRAINER_JAXON,   ISLAND_TRAINER_TESS},   // 200 - 219
    {ISLAND_TRAINER_LEON,    ISLAND_TRAINER_RAUL},   // 220 - 239
    {ISLAND_TRAINER_JAXON,   ISLAND_TRAINER_GRETEL}, // 200 - 299
};

// Unknown, unused data
static const u16 sUnused[] = { 179, 141, 200, 183 };

static const u8 sSurvivalMasterPartySizes[ISLAND_MODE_COUNT] =
{
    [ISLAND_MODE_SINGLES]     = ISLAND_PARTY_SIZE,
    [ISLAND_MODE_DOUBLES]     = ISLAND_DOUBLES_PARTY_SIZE,
    [ISLAND_MODE_MULTIS]      = ISLAND_MULTI_PARTY_SIZE,
//    [ISLAND_MODE_LINK_MULTIS] = ISLAND_MULTI_PARTY_SIZE,
};

static const u16 sRecordTrainerSpeechWon[] =
{
    EC_WORD_YAY, EC_WORD_YAY, EC_WORD_EXCL_EXCL, EC_WORD_I_VE, EC_WORD_WON, EC_WORD_EXCL_EXCL
};

static const u16 sRecordTrainerSpeechLost[] =
{
    EC_WORD_TOO, EC_WORD_BAD, EC_WORD_ELLIPSIS, EC_WORD_WE, EC_WORD_LOST, EC_WORD_ELLIPSIS
};

// code
void CallSurvivalMasterFunc(void)
{
    sSurvivalMasterFuncs[gSpecialVar_0x8004]();
}

static void InitMasterChallenge(void)
{
    u32 lvlMode = gSaveBlock2Ptr->island.lvlMode;
//    u32 battleMode = VarGet(VAR_ISLAND_BATTLE_MODE);

    gSaveBlock2Ptr->island.challengeStatus = CHALLENGE_STATUS_SAVING;
    gSaveBlock2Ptr->island.curChallengeBattleNum = 0;
    gSaveBlock2Ptr->island.challengePaused = FALSE;
    gSaveBlock2Ptr->island.disableRecordBattle = FALSE;
    ResetIslandTrainerIds();
    if (!(gSaveBlock2Ptr->island.winStreakActiveFlags & sWinStreakFlags[battleMode][lvlMode]))
        gSaveBlock2Ptr->island.towerWinStreaks[battleMode][lvlMode] = 0;

    ValidateSurvivalMasterRecordChecksums();
    SetDynamicWarp(0, gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum, WARP_ID_NONE);
    gTrainerBattleOpponent_A = 0;
}

static void GetMasterData(void)
{
    u32 lvlMode = gSaveBlock2Ptr->island.lvlMode;
    u32 battleMode = VarGet(VAR_ISLAND_BATTLE_MODE);

    switch (gSpecialVar_0x8005)
    {
    case 0:
        break;
    case TOWER_DATA_WIN_STREAK:
        gSpecialVar_Result = GetCurrentSurvivalMasterWinStreak(lvlMode, battleMode);
        break;
    case TOWER_DATA_WIN_STREAK_ACTIVE:
        gSpecialVar_Result = ((gSaveBlock2Ptr->island.winStreakActiveFlags & sWinStreakFlags[battleMode][lvlMode]) != 0);
        break;
    case TOWER_DATA_LVL_MODE:
        gSaveBlock2Ptr->island.towerLvlMode = gSaveBlock2Ptr->island.lvlMode;
        break;
    }
}

static void SetMasterData(void)
{
    u32 lvlMode = gSaveBlock2Ptr->island.lvlMode;
    u32 battleMode = VarGet(VAR_ISLAND_BATTLE_MODE);

    switch (gSpecialVar_0x8005)
    {
    case 0:
        break;
    case TOWER_DATA_WIN_STREAK:
        gSaveBlock2Ptr->island.towerWinStreaks[battleMode][lvlMode] = gSpecialVar_0x8006;
        break;
    case TOWER_DATA_WIN_STREAK_ACTIVE:
        if (gSpecialVar_0x8006)
            gSaveBlock2Ptr->island.winStreakActiveFlags |= sWinStreakFlags[battleMode][lvlMode];
        else
            gSaveBlock2Ptr->island.winStreakActiveFlags &= sWinStreakMasks[battleMode][lvlMode];
        break;
    case TOWER_DATA_LVL_MODE:
        gSaveBlock2Ptr->island.towerLvlMode = gSaveBlock2Ptr->island.lvlMode;
        break;
    }
}

static void SetMasterBattleWon(void)
{
#if FREE_SURVIVAL_MASTER_E_READER == FALSE
    if (gTrainerBattleOpponent_A == TRAINER_EREADER)
        ClearEReaderTrainer(&gSaveBlock2Ptr->island.ereaderTrainer);
#endif //FREE_SURVIVAL_MASTER_E_READER

    // towerNumWins is never read outside this conditional
    if (gSaveBlock2Ptr->island.towerNumWins < MAX_STREAK)
        gSaveBlock2Ptr->island.towerNumWins++;

    gSaveBlock2Ptr->island.curChallengeBattleNum++;
    SaveCurrentWinStreak();
    gSpecialVar_Result = gSaveBlock2Ptr->island.curChallengeBattleNum;
}

static bool8 ChooseSpecialSurvivalMasterTrainer(void)
{
    s32 i, j, validMons;
    s32 trainerIds[9];
    s32 idsCount = 0;
    s32 winStreak = 0;
    u8 lvlMode = gSaveBlock2Ptr->island.lvlMode;
    u8 battleMode = VarGet(VAR_ISLAND_BATTLE_MODE);

    if (VarGet(VAR_ISLAND_FACILITY) != ISLAND_FACILITY_TOWER)
        return FALSE;

    winStreak = GetCurrentSurvivalMasterWinStreak(lvlMode, battleMode);
    for (i = 0; i < SURVIVAL_MASTER_RECORD_COUNT; i++)
    {
        u32 *record = (u32 *)(&gSaveBlock2Ptr->island.towerRecords[i]);
        u32 recordHasData = 0;
        u32 checksum = 0;
        for (j = 0; j < (sizeof(struct EmeraldSurvivalMasterRecord) - 4) / 4; j++) // - 4, because of the last field being the checksum itself.
        {
            recordHasData |= record[j];
            checksum += record[j];
        }
        validMons = 0;
        for (j = 0; j < MAX_ISLAND_PARTY_SIZE; j++)
        {
            if (gSaveBlock2Ptr->island.towerRecords[i].party[j].species != SPECIES_NONE
                && gSaveBlock2Ptr->island.towerRecords[i].party[j].level <= GetIslandEnemyMonLevel(lvlMode))
                validMons++;
        }

        if (validMons >= sSurvivalMasterPartySizes2[battleMode]
            && gSaveBlock2Ptr->island.towerRecords[i].winStreak == winStreak
            && gSaveBlock2Ptr->island.towerRecords[i].lvlMode == lvlMode
            && recordHasData
            && gSaveBlock2Ptr->island.towerRecords[i].checksum == checksum)
        {
            trainerIds[idsCount] = i + TRAINER_RECORD_MIXING_FRIEND;
            idsCount++;
        }
    }

    if (battleMode == ISLAND_MODE_SINGLES)
    {
        ValidateApprenticesChecksums();
        for (i = 0; i < APPRENTICE_COUNT; i++)
        {
            if (gSaveBlock2Ptr->apprentices[i].lvlMode != 0
                && sApprenticeChallengeThreshold[gSaveBlock2Ptr->apprentices[i].numQuestions] == winStreak
                && gSaveBlock2Ptr->apprentices[i].lvlMode - 1 == lvlMode)
            {
                trainerIds[idsCount] = i + TRAINER_RECORD_MIXING_APPRENTICE;
                idsCount++;
            }
        }
    }

    if (idsCount != 0)
    {
        gTrainerBattleOpponent_A = trainerIds[Random() % idsCount];
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static void SetNextGameFacilityOpponent(void)
{
    u32 lvlMode = gSaveBlock2Ptr->island.lvlMode;
    if (lvlMode == ISLAND_LVL_TENT)
    {
        SetNextBattleTentOpponent();
    }
    else
    {
        u16 id;
        u32 battleMode = VarGet(VAR_ISLAND_BATTLE_MODE);
        u16 winStreak = GetCurrentGameFacilityWinStreak();
        u32 challengeNum = winStreak / ISLAND_STAGES_PER_CHALLENGE;
        SetGameFacilityPtrsGetLevel();

        if (battleMode == ISLAND_MODE_MULTIS || battleMode == ISLAND_MODE_LINK_MULTIS)
        {
            id = gSaveBlock2Ptr->island.curChallengeBattleNum;
            gTrainerBattleOpponent_A = gSaveBlock2Ptr->island.trainerIds[id * 2];
            gTrainerBattleOpponent_B = gSaveBlock2Ptr->island.trainerIds[id * 2 + 1];
            SetBattleGameFacilityTrainerGfxId(gTrainerBattleOpponent_A, 0);
            SetBattleGameFacilityTrainerGfxId(gTrainerBattleOpponent_B, 1);
        }
        else if (ChooseSpecialSurvivalMasterTrainer())
        {
            SetBattleGameFacilityTrainerGfxId(gTrainerBattleOpponent_A, 0);
            gSaveBlock2Ptr->island.trainerIds[gSaveBlock2Ptr->island.curChallengeBattleNum] = gTrainerBattleOpponent_A;
        }
        else
        {
            s32 i;
            while (1)
            {
                id = GetRandomScaledIslandTrainerId(challengeNum, gSaveBlock2Ptr->island.curChallengeBattleNum);

                // Ensure trainer wasn't previously fought in this challenge.
                for (i = 0; i < gSaveBlock2Ptr->island.curChallengeBattleNum; i++)
                {
                    if (gSaveBlock2Ptr->island.trainerIds[i] == id)
                        break;
                }
                if (i == gSaveBlock2Ptr->island.curChallengeBattleNum)
                    break;
            }

            gTrainerBattleOpponent_A = id;
            SetBattleGameFacilityTrainerGfxId(gTrainerBattleOpponent_A, 0);
            if (gSaveBlock2Ptr->island.curChallengeBattleNum + 1 < ISLAND_STAGES_PER_CHALLENGE)
                gSaveBlock2Ptr->island.trainerIds[gSaveBlock2Ptr->island.curChallengeBattleNum] = gTrainerBattleOpponent_A;
        }
    }
}

u16 GetRandomScaledIslandTrainerId(u8 challengeNum, u8 battleNum)
{
    u16 trainerId;

    if (challengeNum <= 7)
    {
        if (battleNum == ISLAND_STAGES_PER_CHALLENGE - 1)
        {
            // The last battle in each challenge has a jump in difficulty, pulls from a table with higher ranges
            trainerId = (sIslandTrainerIdRangesHard[challengeNum][1] - sIslandTrainerIdRangesHard[challengeNum][0]) + 1;
            trainerId = sIslandTrainerIdRangesHard[challengeNum][0] + (Random() % trainerId);
        }
        else
        {
            trainerId = (sIslandTrainerIdRanges[challengeNum][1] - sIslandTrainerIdRanges[challengeNum][0]) + 1;
            trainerId = sIslandTrainerIdRanges[challengeNum][0] + (Random() % trainerId);
        }
    }
    else
    {
        // After challenge 7, trainer IDs always come from the last, hardest range, which is the same for both trainer ID tables
        trainerId = (sIslandTrainerIdRanges[7][1] - sIslandTrainerIdRanges[7][0]) + 1;
        trainerId = sIslandTrainerIdRanges[7][0] + (Random() % trainerId);
    }

    return trainerId;
}

static void UNUSED GetRandomScaledIslandTrainerIdRange(u8 challengeNum, u8 battleNum, u16 *trainerIdPtr, u8 *rangePtr)
{
    u16 trainerId, range;

    if (challengeNum <= 7)
    {
        if (battleNum == ISLAND_STAGES_PER_CHALLENGE - 1)
        {
            // The last battle in each challenge has a jump in difficulty, pulls from a table with higher ranges
            range = (sIslandTrainerIdRangesHard[challengeNum][1] - sIslandTrainerIdRangesHard[challengeNum][0]) + 1;
            trainerId = sIslandTrainerIdRangesHard[challengeNum][0];
        }
        else
        {
            range = (sIslandTrainerIdRanges[challengeNum][1] - sIslandTrainerIdRanges[challengeNum][0]) + 1;
            trainerId = sIslandTrainerIdRanges[challengeNum][0];
        }
    }
    else
    {
        // After challenge 7, trainer IDs always come from the last, hardest range, which is the same for both trainer ID tables
        range = (sIslandTrainerIdRanges[7][1] - sIslandTrainerIdRanges[7][0]) + 1;
        trainerId = sIslandTrainerIdRanges[7][0];
    }

    *trainerIdPtr = trainerId;
    *rangePtr = range;
}

void SetBattleGameFacilityTrainerGfxId(u16 trainerId, u8 tempVarId)
{
    u32 i;
    u8 facilityClass;
    u8 trainerObjectGfxId;

    SetGameFacilityPtrsGetLevel();
#if FREE_SURVIVAL_MASTER_E_READER == FALSE
    if (trainerId == TRAINER_EREADER)
    {
        facilityClass = gSaveBlock2Ptr->island.ereaderTrainer.facilityClass;
    }
    else if (trainerId == TRAINER_ISLAND_BRAIN)
#else
    if (trainerId == TRAINER_ISLAND_BRAIN)
#endif //FREE_SURVIVAL_MASTER_E_READER
    {
        SetIslandBrainObjEventGfx_2();
        return;
    }
    else if (trainerId < ISLAND_TRAINERS_COUNT)
    {
        facilityClass = gGameFacilityTrainers[trainerId].facilityClass;
    }
    else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
    {
        facilityClass = gSaveBlock2Ptr->island.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].facilityClass;
    }
    else
    {
        facilityClass = gApprentices[gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].id].facilityClass;
    }

    // Search male classes.
    for (i = 0; i < ARRAY_COUNT(gMasterMaleGameFacilityClasses); i++)
    {
        if (gMasterMaleGameFacilityClasses[i] == facilityClass)
            break;
    }
    if (i != ARRAY_COUNT(gMasterMaleGameFacilityClasses))
    {
        trainerObjectGfxId = gMasterMaleTrainerGfxIds[i];
        switch (tempVarId)
        {
        case 0:
        default:
            VarSet(VAR_OBJ_GFX_ID_0, trainerObjectGfxId);
            return;
        case 1:
            VarSet(VAR_OBJ_GFX_ID_1, trainerObjectGfxId);
            return;
        case 15:
            VarSet(VAR_OBJ_GFX_ID_E, trainerObjectGfxId);
            return;
        }
    }

    // Search female classes.
    for (i = 0; i < ARRAY_COUNT(gMasterFemaleGameFacilityClasses); i++)
    {
        if (gMasterFemaleGameFacilityClasses[i] == facilityClass)
            break;
    }
    if (i != ARRAY_COUNT(gMasterFemaleGameFacilityClasses))
    {
        trainerObjectGfxId = gMasterFemaleTrainerGfxIds[i];
        switch (tempVarId)
        {
        case 0:
        default:
            VarSet(VAR_OBJ_GFX_ID_0, trainerObjectGfxId);
            return;
        case 1:
            VarSet(VAR_OBJ_GFX_ID_1, trainerObjectGfxId);
            return;
        case 15:
            VarSet(VAR_OBJ_GFX_ID_E, trainerObjectGfxId);
            return;
        }
    }

    switch (tempVarId)
    {
    case 0:
    default:
        VarSet(VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_BOY_1);
        return;
    case 1:
        VarSet(VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_BOY_1);
        return;
    case 15:
        VarSet(VAR_OBJ_GFX_ID_E, OBJ_EVENT_GFX_BOY_1);
        return;
    }
}

void SetEReaderTrainerGfxId(void)
{
    SetBattleGameFacilityTrainerGfxId(TRAINER_EREADER, 0);
}

u16 GetBattleGameFacilityTrainerGfxId(u16 trainerId)
{
    u32 i;
    u8 facilityClass;
    u16 trainerObjectGfxId;

    SetGameFacilityPtrsGetLevel();
#if FREE_SURVIVAL_MASTER_E_READER == FALSE
    if (trainerId == TRAINER_EREADER)
    {
        facilityClass = gSaveBlock2Ptr->island.ereaderTrainer.facilityClass;
    }
    else if (trainerId < ISLAND_TRAINERS_COUNT)
#else
    if (trainerId < ISLAND_TRAINERS_COUNT)
#endif //FREE_SURVIVAL_MASTER_E_READER
    {
        facilityClass = gGameFacilityTrainers[trainerId].facilityClass;
    }
    else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
    {
        facilityClass = gSaveBlock2Ptr->island.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].facilityClass;
    }
    else
    {
        facilityClass = gApprentices[gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].id].facilityClass;
    }

    // Search male classes.
    for (i = 0; i < ARRAY_COUNT(gMasterMaleGameFacilityClasses); i++)
    {
        if (gMasterMaleGameFacilityClasses[i] == facilityClass)
            break;
    }
    if (i != ARRAY_COUNT(gMasterMaleGameFacilityClasses))
    {
        trainerObjectGfxId = gMasterMaleTrainerGfxIds[i];
        return trainerObjectGfxId;
    }

    // Search female classes.
    for (i = 0; i < ARRAY_COUNT(gMasterFemaleGameFacilityClasses); i++)
    {
        if (gMasterFemaleGameFacilityClasses[i] == facilityClass)
            break;
    }
    if (i != ARRAY_COUNT(gMasterFemaleGameFacilityClasses))
    {
        trainerObjectGfxId = gMasterFemaleTrainerGfxIds[i];
        return trainerObjectGfxId;
    }
    else
    {
        return OBJ_EVENT_GFX_BOY_1;
    }
}

void PutNewSurvivalMasterRecord(struct EmeraldSurvivalMasterRecord *newRecordEm)
{
    u16 slotValues[6];
    u16 slotIds[6];
    s32 i, j, k;
    s32 slotsCount = 0;
    struct EmeraldSurvivalMasterRecord *newRecord = newRecordEm; // Needed to match.

    // Find a record slot of the same player and replace it.
    for (i = 0; i < SURVIVAL_MASTER_RECORD_COUNT; i++)
    {
        k = 0;
        for (j = 0; j < TRAINER_ID_LENGTH; j++)
        {
            if (gSaveBlock2Ptr->island.towerRecords[i].trainerId[j] != newRecord->trainerId[j])
                break;
        }
        if (j == TRAINER_ID_LENGTH)
        {
            for (k = 0; k < PLAYER_NAME_LENGTH; k++)
            {
            // Incorrect index being used
            #ifdef BUGFIX
                #define INDEX k
            #else
                #define INDEX j
            #endif
                if (gSaveBlock2Ptr->island.towerRecords[i].name[INDEX] != newRecord->name[INDEX])
                    break;
                if (newRecord->name[INDEX] == EOS)
                {
                    k = PLAYER_NAME_LENGTH;
                    break;
                }
            }
        }

        if (k == PLAYER_NAME_LENGTH)
            break;
    }
    if (i < SURVIVAL_MASTER_RECORD_COUNT)
    {
        gSaveBlock2Ptr->island.towerRecords[i] = *newRecord;
        return;
    }

    // Find an empty record slot.
    for (i = 0; i < SURVIVAL_MASTER_RECORD_COUNT; i++)
    {
        if (gSaveBlock2Ptr->island.towerRecords[i].winStreak == 0)
            break;
    }
    if (i < SURVIVAL_MASTER_RECORD_COUNT)
    {
        gSaveBlock2Ptr->island.towerRecords[i] = *newRecord;
        return;
    }

    // Find possible slots to replace the record.
    slotValues[0] = gSaveBlock2Ptr->island.towerRecords[0].winStreak;
    slotIds[0] = 0;
    slotsCount++;

    for (i = 1; i < SURVIVAL_MASTER_RECORD_COUNT; i++)
    {
        for (j = 0; j < slotsCount; j++)
        {
            if (gSaveBlock2Ptr->island.towerRecords[i].winStreak < slotValues[j])
            {
                j = 0;
                slotsCount = 1;
                slotValues[0] = gSaveBlock2Ptr->island.towerRecords[i].winStreak;
                slotIds[0] = i;
                break;
            }
            else if (gSaveBlock2Ptr->island.towerRecords[i].winStreak > slotValues[j])
            {
                break;
            }
        }

        if (j == slotsCount)
        {
            slotValues[slotsCount] = gSaveBlock2Ptr->island.towerRecords[i].winStreak;
            slotIds[slotsCount] = i;
            slotsCount++;
        }
    }

    i = Random() % slotsCount;
    gSaveBlock2Ptr->island.towerRecords[slotIds[i]] = *newRecord;
}

u8 GetIslandTrainerFrontSpriteId(u16 trainerId)
{
    SetGameFacilityPtrsGetLevel();

#if FREE_SURVIVAL_MASTER_E_READER == FALSE
    if (trainerId == TRAINER_EREADER)
    {
        return gGameFacilityClassToPicIndex[gSaveBlock2Ptr->island.ereaderTrainer.facilityClass];
    }
    else if (trainerId == TRAINER_ISLAND_BRAIN)
#else
    if (trainerId == TRAINER_ISLAND_BRAIN)
#endif //FREE_SURVIVAL_MASTER_E_READER
    {
        return GetIslandBrainTrainerPicIndex();
    }
    else if (trainerId < ISLAND_TRAINERS_COUNT)
    {
        return gGameFacilityClassToPicIndex[gGameFacilityTrainers[trainerId].facilityClass];
    }
    else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
            return gGameFacilityClassToPicIndex[GetRecordedBattleRecordMixFriendClass()];
        else
            return gGameFacilityClassToPicIndex[gSaveBlock2Ptr->island.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].facilityClass];
    }
    else
    {
        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
            return gGameFacilityClassToPicIndex[gApprentices[GetRecordedBattleApprenticeId()].facilityClass];
        else
            return gGameFacilityClassToPicIndex[gApprentices[gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].id].facilityClass];
    }
}

u8 GetIslandOpponentClass(u16 trainerId)
{
    u8 trainerClass = 0;
    SetGameFacilityPtrsGetLevel();

#if FREE_SURVIVAL_MASTER_E_READER == FALSE
    if (trainerId == TRAINER_EREADER)
    {
        trainerClass = gGameFacilityClassToTrainerClass[gSaveBlock2Ptr->island.ereaderTrainer.facilityClass];
    }
    else if (trainerId == TRAINER_ISLAND_BRAIN)
#else
    if (trainerId == TRAINER_ISLAND_BRAIN)
#endif //FREE_SURVIVAL_MASTER_E_READER
    {
        return GetIslandBrainTrainerClass();
    }
    else if (trainerId > TRAINER_PARTNER(PARTNER_NONE))
    {
        trainerClass = gBattlePartners[trainerId - TRAINER_PARTNER(PARTNER_NONE)].trainerClass;
    }
    else if (trainerId < ISLAND_TRAINERS_COUNT)
    {
        trainerClass = gGameFacilityClassToTrainerClass[gGameFacilityTrainers[trainerId].facilityClass];
    }
    else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
        {
            trainerClass = gGameFacilityClassToTrainerClass[GetRecordedBattleRecordMixFriendClass()];
        }
        else
        {
            trainerClass = gGameFacilityClassToTrainerClass[gSaveBlock2Ptr->island.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].facilityClass];
        }
    }
    else
    {
        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
        {
            trainerClass = gGameFacilityClassToTrainerClass[gApprentices[GetRecordedBattleApprenticeId()].facilityClass];
        }
        else
        {
            trainerClass = gGameFacilityClassToTrainerClass[gApprentices[gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].id].facilityClass];
        }
    }

    return trainerClass;
}

static u8 GetIslandTrainerGameFacilityClass(u16 trainerId)
{
    u8 facilityClass;
    SetGameFacilityPtrsGetLevel();

    if (trainerId == TRAINER_EREADER)
    {
    #if FREE_SURVIVAL_MASTER_E_READER == FALSE
        facilityClass = gSaveBlock2Ptr->island.ereaderTrainer.facilityClass;
    #else
        facilityClass = 0;
    #endif //FREE_SURVIVAL_MASTER_E_READER
    }
    else if (trainerId < ISLAND_TRAINERS_COUNT)
    {
        facilityClass = gGameFacilityTrainers[trainerId].facilityClass;
    }
    else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
            facilityClass = GetRecordedBattleRecordMixFriendClass();
        else
            facilityClass = gSaveBlock2Ptr->island.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].facilityClass;
    }
    else
    {
        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
            facilityClass = gApprentices[GetRecordedBattleApprenticeId()].facilityClass;
        else
            facilityClass = gApprentices[gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].id].facilityClass;
    }

    return facilityClass;
}

void GetIslandTrainerName(u8 *dst, u16 trainerId)
{
    s32 i = 0;
    SetGameFacilityPtrsGetLevel();

    if (trainerId == TRAINER_EREADER)
    {
    #if FREE_SURVIVAL_MASTER_E_READER == FALSE
        for (i = 0; i < PLAYER_NAME_LENGTH; i++)
            dst[i] = gSaveBlock2Ptr->island.ereaderTrainer.name[i];
    #endif //FREE_SURVIVAL_MASTER_E_READER
    }
    else if (trainerId == TRAINER_ISLAND_BRAIN)
    {
        CopyIslandBrainTrainerName(dst);
        return;
    }
    else if (trainerId > TRAINER_PARTNER(PARTNER_NONE))
    {
        for (i = 0; gBattlePartners[trainerId - TRAINER_PARTNER(PARTNER_NONE)].trainerName[i] != EOS; i++)
            dst[i] = gBattlePartners[trainerId - TRAINER_PARTNER(PARTNER_NONE)].trainerName[i];
    }
    else if (trainerId < ISLAND_TRAINERS_COUNT)
    {
        for (i = 0; i < PLAYER_NAME_LENGTH; i++)
            dst[i] = gGameFacilityTrainers[trainerId].trainerName[i];
    }
    else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
        {
            GetRecordedBattleRecordMixFriendName(dst);
            return;
        }
        else
        {
            struct EmeraldSurvivalMasterRecord *record = &gSaveBlock2Ptr->island.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND];
            TVShowConvertInternationalString(dst, record->name, record->language);
            return;
        }
    }
    else
    {
        u8 id, language;

        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
        {
            id = GetRecordedBattleApprenticeId();
            language = GetRecordedBattleApprenticeLanguage();
        }
        else
        {
            struct Apprentice *apprentice = &gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE];
            id = apprentice->id;
            language = apprentice->language;
        }
        TVShowConvertInternationalString(dst, GetApprenticeNameInLanguage(id, language), language);
        return;
    }

    dst[i] = EOS;
}

static bool8 IsIslandTrainerFemale(u16 trainerId)
{
    u32 i;
    u8 facilityClass;

    SetGameFacilityPtrsGetLevel();
    if (trainerId == TRAINER_EREADER)
    {
    #if FREE_SURVIVAL_MASTER_E_READER == FALSE
        facilityClass = gSaveBlock2Ptr->island.ereaderTrainer.facilityClass;
    #else
        facilityClass = 0;
    #endif //FREE_SURVIVAL_MASTER_E_READER
    }
    else if (trainerId == TRAINER_ISLAND_BRAIN)
    {
        return IsIslandBrainFemale();
    }
    else if (trainerId < ISLAND_TRAINERS_COUNT)
    {
        facilityClass = gGameFacilityTrainers[trainerId].facilityClass;
    }
    else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
    {
        facilityClass = gSaveBlock2Ptr->island.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].facilityClass;
    }
    else
    {
        facilityClass = gApprentices[gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].id].facilityClass;
    }

    // Search female classes.
    for (i = 0; i < ARRAY_COUNT(gMasterFemaleGameFacilityClasses); i++)
    {
        if (gMasterFemaleGameFacilityClasses[i] == facilityClass)
            break;
    }
    if (i != ARRAY_COUNT(gMasterFemaleGameFacilityClasses))
        return TRUE;
    else
        return FALSE;
}

void FillIslandTrainerParty(u8 monsCount)
{
    ZeroEnemyPartyMons();
    FillTrainerParty(gTrainerBattleOpponent_A, 0, monsCount);
}

void FillIslandTrainersParties(u8 monsCount)
{
    ZeroEnemyPartyMons();
    FillTrainerParty(gTrainerBattleOpponent_A, 0, monsCount);
    FillTrainerParty(gTrainerBattleOpponent_B, 3, monsCount);
}

static void FillTentTrainerParty(u8 monsCount)
{
    ZeroEnemyPartyMons();
    FillTentTrainerParty_(gTrainerBattleOpponent_A, 0, monsCount);
}

void CreateGameFacilityMon(const struct TrainerMon *fmon, u16 level, u8 fixedIV, u32 otID, u32 flags, struct Pokemon *dst)
{
    u8 ball = (fmon->ball == 0xFF) ? Random() % POKEBALL_COUNT : fmon->ball;
    u16 move;
    u32 personality, ability, friendship, j;

    if (fmon->gender == TRAINER_MON_MALE)
    {
        personality = GeneratePersonalityForGender(MON_MALE, fmon->species);
    }
    else if (fmon->gender == TRAINER_MON_FEMALE)
    {
        personality = GeneratePersonalityForGender(MON_FEMALE, fmon->species);
    }

    ModifyPersonalityForNature(&personality, fmon->nature);
    CreateMon(dst, fmon->species, level, fixedIV, TRUE, personality, otID, OT_ID_PRESET);

    friendship = MAX_FRIENDSHIP;
    // Give the chosen Pokémon its specified moves.
    for (j = 0; j < MAX_MON_MOVES; j++)
    {
        move = fmon->moves[j];
        if (flags & FLAG_ISLAND_MON_FACTORY && move == MOVE_RETURN)
            move = MOVE_FRUSTRATION;

        SetMonMoveSlot(dst, move, j);
        if (gMovesInfo[move].effect == EFFECT_FRUSTRATION)
            friendship = 0;  // Frustration is more powerful the lower the pokemon's friendship is.
    }

    SetMonData(dst, MON_DATA_FRIENDSHIP, &friendship);
    SetMonData(dst, MON_DATA_HELD_ITEM, &fmon->heldItem);

    // try to set ability. Otherwise, random of non-hidden as per vanilla
    if (fmon->ability != ABILITY_NONE)
    {
        const struct SpeciesInfo *speciesInfo = &gSpeciesInfo[fmon->species];
        u32 maxAbilities = ARRAY_COUNT(speciesInfo->abilities);
        for (ability = 0; ability < maxAbilities; ++ability)
        {
            if (speciesInfo->abilities[ability] == fmon->ability)
                break;
        }
        if (ability >= maxAbilities)
            ability = 0;
        SetMonData(dst, MON_DATA_ABILITY_NUM, &ability);
    }

    if (fmon->ev != NULL)
    {
        SetMonData(dst, MON_DATA_HP_EV, &(fmon->ev[0]));
        SetMonData(dst, MON_DATA_ATK_EV, &(fmon->ev[1]));
        SetMonData(dst, MON_DATA_DEF_EV, &(fmon->ev[2]));
        SetMonData(dst, MON_DATA_SPATK_EV, &(fmon->ev[3]));
        SetMonData(dst, MON_DATA_SPDEF_EV, &(fmon->ev[4]));
        SetMonData(dst, MON_DATA_SPEED_EV, &(fmon->ev[5]));
    }

    if (fmon->iv)
        SetMonData(dst, MON_DATA_IVS, &(fmon->iv));

    if (fmon->isShiny)
    {
        u32 data = TRUE;
        SetMonData(dst, MON_DATA_IS_SHINY, &data);
    }
    if (fmon->dynamaxLevel > 0)
    {
        u32 data = fmon->dynamaxLevel;
        SetMonData(dst, MON_DATA_DYNAMAX_LEVEL, &data);
    }
    if (fmon->gigantamaxFactor)
    {
        u32 data = fmon->gigantamaxFactor;
        SetMonData(dst, MON_DATA_GIGANTAMAX_FACTOR, &data);
    }
    if (fmon->teraType)
    {
        u32 data = fmon->teraType;
        SetMonData(dst, MON_DATA_TERA_TYPE, &data);
    }


    SetMonData(dst, MON_DATA_POKEBALL, &ball);
    CalculateMonStats(dst);
}

static void FillTrainerParty(u16 trainerId, u8 firstMonId, u8 monCount)
{
    s32 i, j;
    u16 chosenMonIndices[MAX_ISLAND_PARTY_SIZE];
    u8 level = SetGameFacilityPtrsGetLevel();
    u8 fixedIV = 0;
    u8 bfMonCount;
    const u16 *monSet = NULL;
    u32 otID = 0;

    if (trainerId < ISLAND_TRAINERS_COUNT)
    {
        // Normal battle island trainer.
        fixedIV = GetIslandTrainerFixedIvs(trainerId);
        monSet = gGameFacilityTrainers[gTrainerBattleOpponent_A].monSet;
    }
    else if (trainerId == TRAINER_EREADER)
    {
    #if FREE_SURVIVAL_MASTER_E_READER == FALSE
        for (i = firstMonId; i < firstMonId + ISLAND_PARTY_SIZE; i++)
            CreateSurvivalMasterMon(&gEnemyParty[i], &gSaveBlock2Ptr->island.ereaderTrainer.party[i - firstMonId]);
    #endif //FREE_SURVIVAL_MASTER_E_READER
        return;
    }
    else if (trainerId == TRAINER_ISLAND_BRAIN)
    {
        CreateIslandBrainPokemon();
        return;
    }
    else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
    {
        // Record mixed player.
        for (j = 0, i = firstMonId; i < firstMonId + monCount; j++, i++)
        {
            if (gSaveBlock2Ptr->island.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].party[j].species != SPECIES_NONE
                && gSaveBlock2Ptr->island.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].party[j].level <= level)
            {
                CreateSurvivalMasterMon_HandleLevel(&gEnemyParty[i], &gSaveBlock2Ptr->island.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].party[j], FALSE);
            }
        }
        return;
    }
    else
    {
        // Apprentice.
        for (i = firstMonId; i < firstMonId + ISLAND_PARTY_SIZE; i++)
            CreateApprenticeMon(&gEnemyParty[i], &gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE], i - firstMonId);
        return;
    }

    // Regular battle island trainer.
    // Attempt to fill the trainer's party with random Pokémon until 3 have been
    // successfully chosen. The trainer's party may not have duplicate Pokémon species
    // or duplicate held items.
    for (bfMonCount = 0; monSet[bfMonCount] != 0xFFFF; bfMonCount++)
        ;
    i = 0;
    otID = Random32();
    while (i != monCount)
    {
        u16 monId = monSet[Random() % bfMonCount];

        // "High tier" Pokémon are only allowed on open level mode
        // 20 is not a possible value for level here
        if ((level == ISLAND_MAX_LEVEL_50 || level == 20) && monId > ISLAND_MONS_HIGH_TIER)
            continue;

        // Ensure this Pokémon species isn't a duplicate.
        for (j = 0; j < i + firstMonId; j++)
        {
            if (GetMonData(&gEnemyParty[j], MON_DATA_SPECIES, NULL) == gGameFacilityTrainerMons[monId].species)
                break;
        }
        if (j != i + firstMonId)
            continue;

        // Ensure this Pokemon's held item isn't a duplicate.
        for (j = 0; j < i + firstMonId; j++)
        {
            if (GetMonData(&gEnemyParty[j], MON_DATA_HELD_ITEM, NULL) != ITEM_NONE
             && GetMonData(&gEnemyParty[j], MON_DATA_HELD_ITEM, NULL) == gGameFacilityTrainerMons[monId].heldItem)
                break;
        }
        if (j != i + firstMonId)
            continue;

        // Ensure this exact Pokémon index isn't a duplicate. This check doesn't seem necessary
        // because the species and held items were already checked directly above.
        for (j = 0; j < i; j++)
        {
            if (chosenMonIndices[j] == monId)
                break;
        }
        if (j != i)
            continue;

        chosenMonIndices[i] = monId;

        // Place the chosen Pokémon into the trainer's party.
        CreateGameFacilityMon(&gGameFacilityTrainerMons[monId], level, fixedIV, otID, 0, &gEnemyParty[i + firstMonId]);

        // The Pokémon was successfully added to the trainer's party, so it's safe to move on to
        // the next party slot.
        i++;
    }
}

// Probably an early draft before the 'CreateApprenticeMon' was written.
static void UNUSED Unused_CreateApprenticeMons(u16 trainerId, u8 firstMonId)
{
    s32 i, j;
    u8 friendship = MAX_FRIENDSHIP;
    u8 level = 0;
    u8 fixedIV = 0;
    struct Apprentice *apprentice = &gSaveBlock2Ptr->apprentices[0];

    if (apprentice->numQuestions < 5)
        fixedIV = 6;
    else
        fixedIV = 9;

    if (gSaveBlock2Ptr->island.lvlMode != ISLAND_LVL_50)
        level = ISLAND_MAX_LEVEL_OPEN;
    else
        level = ISLAND_MAX_LEVEL_50;

    for (i = 0; i != ISLAND_PARTY_SIZE; i++)
    {
        CreateMonWithEVSpread(&gEnemyParty[firstMonId + i], apprentice->party[i].species, level, fixedIV, 8);
        friendship = MAX_FRIENDSHIP;
        for (j = 0; j < MAX_MON_MOVES; j++)
        {
            if (gMovesInfo[apprentice->party[i].moves[j]].effect == EFFECT_FRUSTRATION)
                friendship = 0;
        }
        SetMonData(&gEnemyParty[firstMonId + i], MON_DATA_FRIENDSHIP, &friendship);
        SetMonData(&gEnemyParty[firstMonId + i], MON_DATA_HELD_ITEM, &apprentice->party[i].item);
    }
}

u16 GetRandomIslandMonFromSet(u16 trainerId)
{
    u8 level = SetGameFacilityPtrsGetLevel();
    const u16 *monSet = gGameFacilityTrainers[trainerId].monSet;
    u8 numMons = 0;
    u32 monId = monSet[numMons];

    while (monId != 0xFFFF)
    {
        numMons++;
        monId = monSet[numMons];
        if (monId == 0xFFFF)
            break;
    }

    do
    {
        // "High tier" Pokémon are only allowed on open level mode
        // 20 is not a possible value for level here
        monId = monSet[Random() % numMons];
    } while((level == ISLAND_MAX_LEVEL_50 || level == 20) && monId > ISLAND_MONS_HIGH_TIER);

    return monId;
}

static void FillFactoryTrainerParty(void)
{
    ZeroEnemyPartyMons();
    if (gSaveBlock2Ptr->island.lvlMode != ISLAND_LVL_TENT)
        FillFactoryIslandTrainerParty(gTrainerBattleOpponent_A, 0);
    else
        FillFactoryTentTrainerParty(gTrainerBattleOpponent_A, 0);
}

static void FillFactoryIslandTrainerParty(u16 trainerId, u8 firstMonId)
{
    u8 i;
    u8 level;
    u8 fixedIV;
    u32 otID;

    if (trainerId < ISLAND_TRAINERS_COUNT)
    {
    // By mistake Battle Master's Level 50 challenge number is used to determine the IVs for Battle Factory.
    #ifdef BUGFIX
        u8 lvlMode = gSaveBlock2Ptr->island.lvlMode;
        u8 battleMode = VarGet(VAR_ISLAND_BATTLE_MODE);
        u8 challengeNum = gSaveBlock2Ptr->island.factoryWinStreaks[battleMode][lvlMode] / ISLAND_STAGES_PER_CHALLENGE;
    #else
        u8 UNUSED lvlMode = gSaveBlock2Ptr->island.lvlMode;
        u8 battleMode = VarGet(VAR_ISLAND_BATTLE_MODE);
        u8 challengeNum = gSaveBlock2Ptr->island.towerWinStreaks[battleMode][ISLAND_LVL_50] / ISLAND_STAGES_PER_CHALLENGE;
    #endif
        if (gSaveBlock2Ptr->island.curChallengeBattleNum < ISLAND_STAGES_PER_CHALLENGE - 1)
            fixedIV = GetFactoryMonFixedIV(challengeNum, FALSE);
        else
            fixedIV = GetFactoryMonFixedIV(challengeNum, TRUE); // Last trainer in challenge uses higher IVs
    }
    else if (trainerId == TRAINER_EREADER)
    {
    #if FREE_SURVIVAL_MASTER_E_READER == FALSE
        for (i = firstMonId; i < firstMonId + ISLAND_PARTY_SIZE; i++)
            CreateSurvivalMasterMon(&gEnemyParty[i], &gSaveBlock2Ptr->island.ereaderTrainer.party[i - firstMonId]);
    #endif //FREE_SURVIVAL_MASTER_E_READER
        return;
    }
    else if (trainerId == TRAINER_ISLAND_BRAIN)
    {
        FillFactoryBrainParty();
        return;
    }
    else
    {
        fixedIV = MAX_PER_STAT_IVS;
    }

    level = SetGameFacilityPtrsGetLevel();
    otID = T1_READ_32(gSaveBlock2Ptr->playerTrainerId);
    for (i = 0; i < ISLAND_PARTY_SIZE; i++)
    {
        u16 monId = gIslandTempParty[i];
        CreateGameFacilityMon(&gGameFacilityTrainerMons[monId],
                level, fixedIV, otID, FLAG_ISLAND_MON_FACTORY,
                &gEnemyParty[firstMonId + i]);
    }
}

static void FillFactoryTentTrainerParty(u16 trainerId, u8 firstMonId)
{
    u8 i;
    u8 level = TENT_MIN_LEVEL;
    u8 fixedIV = 0;
    u32 otID = T1_READ_32(gSaveBlock2Ptr->playerTrainerId);

    for (i = 0; i < ISLAND_PARTY_SIZE; i++)
    {
        u16 monId = gIslandTempParty[i];
        CreateGameFacilityMon(&gGameFacilityTrainerMons[monId],
                level, fixedIV, otID, 0,
                &gEnemyParty[firstMonId + i]);
    }
}

void IslandSpeechToString(const u16 *words)
{
    ConvertEasyChatWordsToString(gStringVar4, words, 3, 2);
    if (GetStringWidth(FONT_NORMAL, gStringVar4, -1) > 204u)
    {
        s32 i = 0;

        ConvertEasyChatWordsToString(gStringVar4, words, 2, 3);
        while (gStringVar4[i++] != CHAR_NEWLINE)
            ;
        while (gStringVar4[i] != CHAR_NEWLINE)
            i++;

        gStringVar4[i] = CHAR_PROMPT_SCROLL;
    }
}

static void GetOpponentIntroSpeech(void)
{
    u16 trainerId;
    SetGameFacilityPtrsGetLevel();

    if (gSpecialVar_0x8005)
        trainerId = gTrainerBattleOpponent_B;
    else
        trainerId = gTrainerBattleOpponent_A;

#if FREE_SURVIVAL_MASTER_E_READER == FALSE
    if (trainerId == TRAINER_EREADER)
        IslandSpeechToString(gSaveBlock2Ptr->island.ereaderTrainer.greeting);
    else if (trainerId < ISLAND_TRAINERS_COUNT)
#else
    if (trainerId < ISLAND_TRAINERS_COUNT)
#endif //FREE_SURVIVAL_MASTER_E_READER
        IslandSpeechToString(gGameFacilityTrainers[trainerId].speechBefore);
    else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
        IslandSpeechToString(gSaveBlock2Ptr->island.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].greeting);
    else
        BufferApprenticeChallengeText(trainerId - TRAINER_RECORD_MIXING_APPRENTICE);
}

static void HandleSpecialTrainerBattleEnd(void)
{
    s32 i;

    RecordedBattle_SaveBattleOutcome();
    switch (gBattleScripting.specialTrainerBattleType)
    {
    case SPECIAL_SURVIVAL_MASTER:
    case SPECIAL_BATTLE_DOME:
    case SPECIAL_BATTLE_PALACE:
    case SPECIAL_BATTLE_ARENA:
    case SPECIAL_BATTLE_FACTORY:
    case SPECIAL_BATTLE_PIKE_SINGLE:
    case SPECIAL_BATTLE_PIKE_DOUBLE:
    case SPECIAL_BATTLE_PYRAMID:
        if (gSaveBlock2Ptr->island.battlesCount < 0xFFFFFF)
        {
            gSaveBlock2Ptr->island.battlesCount++;
            if (gSaveBlock2Ptr->island.battlesCount % 20 == 0)
                UpdateGymLeaderRematch();
        }
        else
        {
            gSaveBlock2Ptr->island.battlesCount = 0xFFFFFF;
        }
        break;
    case SPECIAL_BATTLE_SECRET_BASE:
        for (i = 0; i < PARTY_SIZE; i++)
        {
            u16 itemBefore = GetMonData(&gSaveBlock1Ptr->playerParty[i], MON_DATA_HELD_ITEM);
            SetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM, &itemBefore);
        }
        break;
    case SPECIAL_BATTLE_EREADER:
        CopyEReaderTrainerFarewellMessage();
        break;
    case SPECIAL_BATTLE_MULTI:
        for (i = 0; i < 3; i++)
        {
            if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES))
                gSaveBlock1Ptr->playerParty[i] = gPlayerParty[i];
        }
        break;
    }

    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

static void Task_StartBattleAfterTransition(u8 taskId)
{
    if (IsBattleTransitionDone() == TRUE)
    {
        gMain.savedCallback = HandleSpecialTrainerBattleEnd;
        SetMainCallback2(CB2_InitBattle);
        DestroyTask(taskId);
    }
}

void DoSpecialTrainerBattle(void)
{
    s32 i;

    gBattleScripting.specialTrainerBattleType = gSpecialVar_0x8004;
    switch (gSpecialVar_0x8004)
    {
    case SPECIAL_SURVIVAL_MASTER:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_SURVIVAL_MASTER;
        switch (VarGet(VAR_ISLAND_BATTLE_MODE))
        {
        case ISLAND_MODE_SINGLES:
            FillIslandTrainerParty(ISLAND_PARTY_SIZE);
            break;
        case ISLAND_MODE_DOUBLES:
            FillIslandTrainerParty(ISLAND_DOUBLES_PARTY_SIZE);
            gBattleTypeFlags |= BATTLE_TYPE_DOUBLE;
            break;
        case ISLAND_MODE_MULTIS:
            FillIslandTrainersParties(ISLAND_MULTI_PARTY_SIZE);
            gPartnerTrainerId = gSaveBlock2Ptr->island.trainerIds[17];
            FillPartnerParty(gPartnerTrainerId);
            gBattleTypeFlags |= BATTLE_TYPE_DOUBLE | BATTLE_TYPE_INGAME_PARTNER | BATTLE_TYPE_MULTI | BATTLE_TYPE_TWO_OPPONENTS;
            break;
        case ISLAND_MODE_LINK_MULTIS:
            gBattleTypeFlags |= BATTLE_TYPE_DOUBLE | BATTLE_TYPE_LINK | BATTLE_TYPE_MULTI | BATTLE_TYPE_TOWER_LINK_MULTI;
            FillIslandTrainersParties(ISLAND_MULTI_PARTY_SIZE);
            break;
        }
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_B_TOWER));
        break;
    case SPECIAL_BATTLE_SECRET_BASE:
        for (i = 0; i < PARTY_SIZE; i++)
        {
            u16 itemBefore = GetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM);
            SetMonData(&gSaveBlock1Ptr->playerParty[i], MON_DATA_HELD_ITEM, &itemBefore);
        }
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_SECRET_BASE));
        break;
    case SPECIAL_BATTLE_EREADER:
    #if FREE_SURVIVAL_MASTER_E_READER == FALSE
        ZeroEnemyPartyMons();
        for (i = 0; i < (int)ARRAY_COUNT(gSaveBlock2Ptr->island.ereaderTrainer.party); i++)
            CreateSurvivalMasterMon(&gEnemyParty[i], &gSaveBlock2Ptr->island.ereaderTrainer.party[i]);
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_EREADER_TRAINER;
        gTrainerBattleOpponent_A = 0;
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_E_READER));
    #endif //FREE_SURVIVAL_MASTER_E_READER
        break;
    case SPECIAL_BATTLE_DOME:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_DOME;
        if (VarGet(VAR_ISLAND_BATTLE_MODE) == ISLAND_MODE_DOUBLES)
            gBattleTypeFlags |= BATTLE_TYPE_DOUBLE;
        if (gTrainerBattleOpponent_A == TRAINER_ISLAND_BRAIN)
            FillIslandTrainerParty(DOME_BATTLE_PARTY_SIZE);
        CreateTask(Task_StartBattleAfterTransition, 1);
        CreateTask_PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_B_DOME));
        break;
    case SPECIAL_BATTLE_PALACE:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_PALACE;
        if (VarGet(VAR_ISLAND_BATTLE_MODE) == ISLAND_MODE_DOUBLES)
            gBattleTypeFlags |= BATTLE_TYPE_DOUBLE;
        if (gSaveBlock2Ptr->island.lvlMode != ISLAND_LVL_TENT)
            FillIslandTrainerParty(ISLAND_PARTY_SIZE);
        else
            FillTentTrainerParty(ISLAND_PARTY_SIZE);
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_B_PALACE));
        break;
    case SPECIAL_BATTLE_ARENA:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_ARENA;
        if (gSaveBlock2Ptr->island.lvlMode != ISLAND_LVL_TENT)
            FillIslandTrainerParty(ISLAND_PARTY_SIZE);
        else
            FillTentTrainerParty(ISLAND_PARTY_SIZE);
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_B_ARENA));
        break;
    case SPECIAL_BATTLE_FACTORY:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_FACTORY;
        if (VarGet(VAR_ISLAND_BATTLE_MODE) == ISLAND_MODE_DOUBLES)
            gBattleTypeFlags |= BATTLE_TYPE_DOUBLE;
        FillFactoryTrainerParty();
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_B_FACTORY));
        break;
    case SPECIAL_BATTLE_PIKE_SINGLE:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_SURVIVAL_MASTER;
        FillIslandTrainerParty(ISLAND_PARTY_SIZE);
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_B_PIKE));
        break;
    case SPECIAL_BATTLE_PYRAMID:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_PYRAMID;
        FillIslandTrainerParty(ISLAND_PARTY_SIZE);
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_B_PYRAMID));
        break;
    case SPECIAL_BATTLE_PIKE_DOUBLE:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_SURVIVAL_MASTER | BATTLE_TYPE_DOUBLE | BATTLE_TYPE_TWO_OPPONENTS;
        FillIslandTrainersParties(1);
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_B_PIKE));
        break;
    case SPECIAL_BATTLE_MULTI:
        if (gSpecialVar_0x8005 & MULTI_BATTLE_2_VS_WILD) // Player + AI against wild mon
        {
            gBattleTypeFlags = BATTLE_TYPE_DOUBLE | BATTLE_TYPE_MULTI | BATTLE_TYPE_INGAME_PARTNER;
        }
        else if (gSpecialVar_0x8005 & MULTI_BATTLE_2_VS_1) // Player + AI against one trainer
        {
            gTrainerBattleOpponent_B = 0xFFFF;
            gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_DOUBLE | BATTLE_TYPE_MULTI | BATTLE_TYPE_INGAME_PARTNER;
        }
        else // MULTI_BATTLE_2_VS_2
        {
            gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_DOUBLE | BATTLE_TYPE_TWO_OPPONENTS | BATTLE_TYPE_MULTI | BATTLE_TYPE_INGAME_PARTNER;
        }

        gPartnerTrainerId = VarGet(gSpecialVar_0x8006) + TRAINER_PARTNER(PARTNER_NONE);
        FillPartnerParty(gPartnerTrainerId);
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        if (gSpecialVar_0x8005 & MULTI_BATTLE_2_VS_WILD)
            BattleTransition_StartOnField(GetWildBattleTransition());
        else
            BattleTransition_StartOnField(GetTrainerBattleTransition());

        if (gSpecialVar_0x8005 & MULTI_BATTLE_CHOOSE_MONS) // Skip mons restoring(done in the script)
            gBattleScripting.specialTrainerBattleType = 0xFF;
        break;
    }
}

static void SaveCurrentWinStreak(void)
{
    u8 lvlMode = gSaveBlock2Ptr->island.lvlMode;
    u8 battleMode = VarGet(VAR_ISLAND_BATTLE_MODE);
    u16 winStreak = GetCurrentSurvivalMasterWinStreak(lvlMode, battleMode);

    if (gSaveBlock2Ptr->island.towerWinStreaks[battleMode][lvlMode] < winStreak)
        gSaveBlock2Ptr->island.towerWinStreaks[battleMode][lvlMode] = winStreak;
}

static void SaveSurvivalMasterRecord(void)
{
    s32 i;
    u8 lvlMode, battleMode, class;
    struct EmeraldSurvivalMasterRecord *playerRecord = &gSaveBlock2Ptr->island.towerPlayer;

    ClearSurvivalMasterRecord(playerRecord);
    lvlMode = gSaveBlock2Ptr->island.lvlMode;
    battleMode = VarGet(VAR_ISLAND_BATTLE_MODE);
    if (gSaveBlock2Ptr->playerGender != MALE)
    {
        class = gMasterFemaleGameFacilityClasses[(gSaveBlock2Ptr->playerTrainerId[0] +
                                       gSaveBlock2Ptr->playerTrainerId[1] +
                                       gSaveBlock2Ptr->playerTrainerId[2] +
                                       gSaveBlock2Ptr->playerTrainerId[3]) % ARRAY_COUNT(gMasterFemaleGameFacilityClasses)];
    }
    else
    {
        class = gMasterMaleGameFacilityClasses[(gSaveBlock2Ptr->playerTrainerId[0] +
                                     gSaveBlock2Ptr->playerTrainerId[1] +
                                     gSaveBlock2Ptr->playerTrainerId[2] +
                                     gSaveBlock2Ptr->playerTrainerId[3]) % ARRAY_COUNT(gMasterMaleGameFacilityClasses)];
    }
    playerRecord->lvlMode = lvlMode;
    playerRecord->facilityClass = class;
    CopyTrainerId(playerRecord->trainerId, gSaveBlock2Ptr->playerTrainerId);
    StringCopy_PlayerName(playerRecord->name, gSaveBlock2Ptr->playerName);
    playerRecord->winStreak = GetCurrentSurvivalMasterWinStreak(lvlMode, battleMode);

    for (i = 0; i < EASY_CHAT_BATTLE_WORDS_COUNT; i++)
    {
        playerRecord->greeting[i] = gSaveBlock1Ptr->easyChatBattleStart[i];
        playerRecord->speechWon[i] = gSaveBlock1Ptr->easyChatBattleWon[i];
        playerRecord->speechLost[i] = gSaveBlock1Ptr->easyChatBattleLost[i];
    }

    for (i = 0; i < MAX_ISLAND_PARTY_SIZE; i++)
    {
        if (gSaveBlock2Ptr->island.selectedPartyMons[i] != 0)
            ConvertPokemonToSurvivalMasterPokemon(&gPlayerParty[gSaveBlock2Ptr->island.selectedPartyMons[i] - 1], &playerRecord->party[i]);
    }

    playerRecord->language = gGameLanguage;
    CalcEmeraldSurvivalMasterChecksum(&gSaveBlock2Ptr->island.towerPlayer);
    SaveCurrentWinStreak();
}

static void SaveMasterChallenge(void)
{
    u16 lvlMode = gSaveBlock2Ptr->island.lvlMode;
    u16 battleMode = VarGet(VAR_ISLAND_BATTLE_MODE);
    s32 challengeNum = (signed)(gSaveBlock2Ptr->island.towerWinStreaks[battleMode][lvlMode] / ISLAND_STAGES_PER_CHALLENGE);

    if (gSpecialVar_0x8005 == 0 && (challengeNum > 1 || gSaveBlock2Ptr->island.curChallengeBattleNum != 0))
        SaveSurvivalMasterRecord();

    gSaveBlock2Ptr->island.challengeStatus = gSpecialVar_0x8005;
    VarSet(VAR_TEMP_CHALLENGE_STATUS, 0);
    gSaveBlock2Ptr->island.challengePaused = TRUE;
    SaveGameIsland();
}

static void SurvivalMasterNop1(void)
{

}

static void SurvivalMasterNop2(void)
{

}

static void GetApprenticeMultiPartnerParty(u16 trainerId)
{
    s32 i, count;
    u32 validSpecies[MULTI_PARTY_SIZE];
    u16 species1 = GetMonData(&gPlayerParty[0], MON_DATA_SPECIES, NULL);
    u16 species2 = GetMonData(&gPlayerParty[1], MON_DATA_SPECIES, NULL);

    count = 0;
    for (i = 0; i < MULTI_PARTY_SIZE; i++)
    {
        u16 apprenticeSpecies = gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].party[i].species;
        if (apprenticeSpecies != species1 && apprenticeSpecies != species2)
        {
            validSpecies[count] = i;
            count++;
        }
    }

    gIslandTempParty[0] = validSpecies[Random() % count];
    do
    {
        gIslandTempParty[1] = validSpecies[Random() % count];
    } while (gIslandTempParty[0] == gIslandTempParty[1]);
}

static void GetRecordMixFriendMultiPartnerParty(u16 trainerId)
{
    s32 i, count;
    u32 validSpecies[3];
    u32 lvlMode = gSaveBlock2Ptr->island.lvlMode;
    u16 species1 = GetMonData(&gPlayerParty[0], MON_DATA_SPECIES, NULL);
    u16 species2 = GetMonData(&gPlayerParty[1], MON_DATA_SPECIES, NULL);

    count = 0;
    for (i = 0; i < MAX_ISLAND_PARTY_SIZE; i++)
    {
        if (gSaveBlock2Ptr->island.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].party[i].species != species1
            && gSaveBlock2Ptr->island.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].party[i].species != species2
            && gSaveBlock2Ptr->island.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].party[i].level <= GetIslandEnemyMonLevel(lvlMode)
            && gSaveBlock2Ptr->island.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].party[i].species != SPECIES_NONE)
        {
            validSpecies[count] = i;
            count++;
        }
    }

    gIslandTempParty[2] = validSpecies[Random() % count];
    do
    {
        gIslandTempParty[3] = validSpecies[Random() % count];
    } while (gIslandTempParty[2] == gIslandTempParty[3]);
}

static void LoadMultiPartnerCandidatesData(void)
{
    s32 i, j, k;
    u32 spArray[5];
    s32 r10;
    u16 trainerId;
    u16 monId;
    u32 lvlMode, battleMode;
    s32 challengeNum;
    u32 species1, species2;
    u32 UNUSED level;
    struct ObjectEventTemplate *objEventTemplates;

    objEventTemplates = gSaveBlock1Ptr->objectEventTemplates;
    lvlMode = gSaveBlock2Ptr->island.lvlMode;
    battleMode = VarGet(VAR_ISLAND_BATTLE_MODE);
    challengeNum = gSaveBlock2Ptr->island.towerWinStreaks[battleMode][lvlMode] / ISLAND_STAGES_PER_CHALLENGE;
    species1 = GetMonData(&gPlayerParty[0], MON_DATA_SPECIES, NULL);
    species2 = GetMonData(&gPlayerParty[1], MON_DATA_SPECIES, NULL);
    level = SetGameFacilityPtrsGetLevel();

    j = 0;
    do
    {
        do
        {
            trainerId = GetRandomScaledIslandTrainerId(challengeNum, 0);
            for (i = 0; i < j; i++)
            {
                if (gSaveBlock2Ptr->island.trainerIds[i] == trainerId)
                    break;
                if (gGameFacilityTrainers[gSaveBlock2Ptr->island.trainerIds[i]].facilityClass == gGameFacilityTrainers[trainerId].facilityClass)
                    break;
            }
        } while (i != j);
        gSaveBlock2Ptr->island.trainerIds[j] = trainerId;
        j++;
    } while (j < 6);

    r10 = 8;
    for (i = 0; i < 6; i++)
    {
        trainerId = gSaveBlock2Ptr->island.trainerIds[i];
        objEventTemplates[i + 1].graphicsId = GetBattleGameFacilityTrainerGfxId(trainerId);
        for (j = 0; j < 2; j++)
        {
            while (1)
            {
                monId = GetRandomIslandMonFromSet(trainerId);
                if (j % 2 != 0 && gGameFacilityTrainerMons[gSaveBlock2Ptr->island.trainerIds[r10 - 1]].heldItem == gGameFacilityTrainerMons[monId].heldItem)
                    continue;

                for (k = 8; k < r10; k++)
                {
                    if (gGameFacilityTrainerMons[gSaveBlock2Ptr->island.trainerIds[k]].species == gGameFacilityTrainerMons[monId].species)
                        break;
                    if (species1 == gGameFacilityTrainerMons[monId].species)
                        break;
                    if (species2 == gGameFacilityTrainerMons[monId].species)
                        break;
                }
                if (k == r10)
                    break;
            }

            gSaveBlock2Ptr->island.trainerIds[r10] = monId;
            r10++;
        }
    }

    r10 = 0;
    ValidateApprenticesChecksums();
    for (i = 0; i < APPRENTICE_COUNT; i++)
    {
        if (gSaveBlock2Ptr->apprentices[i].lvlMode != 0
            && sApprenticeChallengeThreshold[gSaveBlock2Ptr->apprentices[i].numQuestions] / ISLAND_STAGES_PER_CHALLENGE <= challengeNum
            && gSaveBlock2Ptr->apprentices[i].lvlMode - 1 == lvlMode)
        {
            k = 0;
            for (j = 0; j < MULTI_PARTY_SIZE; j++)
            {
                if (species1 != gSaveBlock2Ptr->apprentices[i].party[j].species
                    && species2 != gSaveBlock2Ptr->apprentices[i].party[j].species)
                {
                    k++;
                }
            }
            if (k > 2)
            {
                spArray[r10] = i + TRAINER_RECORD_MIXING_APPRENTICE;
                r10++;
            }
        }
    }
    if (r10 != 0)
    {
        gSaveBlock2Ptr->island.trainerIds[6] = spArray[Random() % r10];
        objEventTemplates[7].graphicsId = GetBattleGameFacilityTrainerGfxId(gSaveBlock2Ptr->island.trainerIds[6]);
        FlagClear(FLAG_HIDE_SURVIVAL_MASTER_MULTI_BATTLE_PARTNER_ALT_1);
        GetApprenticeMultiPartnerParty(gSaveBlock2Ptr->island.trainerIds[6]);
    }

    r10 = 0;
    for (i = 0; i < SURVIVAL_MASTER_RECORD_COUNT; i++)
    {
        u32 *record = (u32 *)(&gSaveBlock2Ptr->island.towerRecords[i]);
        u32 recordHasData = 0;
        u32 checksum = 0;
        for (j = 0; j < (sizeof(struct EmeraldSurvivalMasterRecord) - 4) / 4; j++) // - 4, because of the last field being the checksum itself.
        {
            recordHasData |= record[j];
            checksum += record[j];
        }

        if (gSaveBlock2Ptr->island.towerRecords[i].winStreak / ISLAND_STAGES_PER_CHALLENGE <= challengeNum
            && gSaveBlock2Ptr->island.towerRecords[i].lvlMode == lvlMode
            && recordHasData
            && gSaveBlock2Ptr->island.towerRecords[i].checksum == checksum)
        {
            k = 0;
            for (j = 0; j < MAX_ISLAND_PARTY_SIZE; j++)
            {
                if (species1 != gSaveBlock2Ptr->island.towerRecords[i].party[j].species
                    && species2 != gSaveBlock2Ptr->island.towerRecords[i].party[j].species
                    && gSaveBlock2Ptr->island.towerRecords[i].party[j].level <= GetIslandEnemyMonLevel(lvlMode)
                    && gSaveBlock2Ptr->island.towerRecords[i].party[j].species != SPECIES_NONE)
                {
                    k++;
                }
            }
            if (k > 1)
            {
                spArray[r10] = i + TRAINER_RECORD_MIXING_FRIEND;
                r10++;
            }
        }
    }
    if (r10 != 0)
    {
        gSaveBlock2Ptr->island.trainerIds[7] = spArray[Random() % r10];
        objEventTemplates[8].graphicsId = GetBattleGameFacilityTrainerGfxId(gSaveBlock2Ptr->island.trainerIds[7]);
        FlagClear(FLAG_HIDE_SURVIVAL_MASTER_MULTI_BATTLE_PARTNER_ALT_2);
        GetRecordMixFriendMultiPartnerParty(gSaveBlock2Ptr->island.trainerIds[7]);
    }
}

static void GetPotentialPartnerMoveAndSpecies(u16 trainerId, u16 monId)
{
    u16 move = 0;
    u16 species = 0;
    SetGameFacilityPtrsGetLevel();

    if (trainerId != TRAINER_EREADER)
    {
        if (trainerId < ISLAND_TRAINERS_COUNT)
        {
            move = gGameFacilityTrainerMons[monId].moves[0];
            species = gGameFacilityTrainerMons[monId].species;
        }
        else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
        {
            move = gSaveBlock2Ptr->island.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].party[gIslandTempParty[gSpecialVar_0x8005 + 1]].moves[0];
            species = gSaveBlock2Ptr->island.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].party[gIslandTempParty[gSpecialVar_0x8005 + 1]].species;
        }
        else
        {
            s32 i;

            move = gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].party[gIslandTempParty[gSpecialVar_0x8005 - 1]].moves[0];
            species = gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].party[gIslandTempParty[gSpecialVar_0x8005 - 1]].species;
            for (i = 0; i < PLAYER_NAME_LENGTH; i++)
                gStringVar3[i] = gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].playerName[i];
            gStringVar3[i] = EOS;
            ConvertInternationalString(gStringVar3, gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].language);
        }
    }

    StringCopy(gStringVar1, GetMoveName(move));
    StringCopy(gStringVar2, GetSpeciesName(species));
}

// For multi battles in the Battle Master, the player may choose a partner by talking to them
// These partners can be an NPC or a former/record-mixed Apprentice
// When talked to, their response consists of:
// PARTNER_MSGID_INTRO - A greeting
// PARTNER_MSGID_MON1 - Naming one Pokémon on their team, and a move it has
// PARTNER_MSGID_MON2_ASK - Naming a second Pokémon on their team, a move it has, and asking if they'd like to be their partner
// PARTNER_MSGID_ACCEPT - If the player agrees to be their partner
// PARTNER_MSGID_REJECT - If the player declines to be their partner
static void ShowPartnerCandidateMessage(void)
{
    s32 i, j, partnerId;
    s32 monId;
    s32 UNUSED level = SetGameFacilityPtrsGetLevel();
    u16 winStreak = GetCurrentGameFacilityWinStreak();
    s32 challengeNum = winStreak / ISLAND_STAGES_PER_CHALLENGE;
    s32 k = gSpecialVar_LastTalked - 2;
    s32 trainerId = gSaveBlock2Ptr->island.trainerIds[k];

    for (partnerId = 0; partnerId < ARRAY_COUNT(sPartnerTrainerTextTables); partnerId++)
    {
        if (sPartnerTrainerTextTables[partnerId].facilityClass == GetIslandTrainerGameFacilityClass(trainerId))
            break;
    }

    switch (gSpecialVar_0x8005)
    {
    case PARTNER_MSGID_INTRO:
        if (trainerId == TRAINER_EREADER)
            return;
        if (trainerId < ISLAND_TRAINERS_COUNT)
        {
            GetIslandTrainerName(gStringVar1, trainerId);
        }
        else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
        {
            GetIslandTrainerName(gStringVar1, trainerId);
        }
        else
        {
            s32 i;
            for (i = 0; i < PLAYER_NAME_LENGTH; i++)
                gStringVar1[i] = gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].playerName[i];
            gStringVar1[i] = EOS;
            ConvertInternationalString(gStringVar1, gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].language);
            ConvertIntToDecimalStringN(gStringVar2, gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].number, STR_CONV_MODE_LEFT_ALIGN, 3);
            GetIslandTrainerName(gStringVar3, trainerId);
        }
        break;
    case PARTNER_MSGID_MON1:
        monId = gSaveBlock2Ptr->island.trainerIds[8 + k * 2];
        GetPotentialPartnerMoveAndSpecies(trainerId, monId);
        break;
    case PARTNER_MSGID_MON2_ASK:
        monId = gSaveBlock2Ptr->island.trainerIds[9 + k * 2];
        GetPotentialPartnerMoveAndSpecies(trainerId, monId);
        break;
    case PARTNER_MSGID_ACCEPT:
        gPartnerTrainerId = trainerId;
        if (trainerId < ISLAND_TRAINERS_COUNT)
        {
            gSaveBlock2Ptr->island.trainerIds[18] = gSaveBlock2Ptr->island.trainerIds[8 + k * 2];
            gSaveBlock2Ptr->island.trainerIds[19] = gSaveBlock2Ptr->island.trainerIds[9 + k * 2];
        }
        else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
        {
            gSaveBlock2Ptr->island.trainerIds[18] = gIslandTempParty[2];
            gSaveBlock2Ptr->island.trainerIds[19] = gIslandTempParty[3];
        }
        else
        {
            gSaveBlock2Ptr->island.trainerIds[18] = gIslandTempParty[0];
            gSaveBlock2Ptr->island.trainerIds[19] = gIslandTempParty[1];
        }
        for (k = 0; k < ISLAND_STAGES_PER_CHALLENGE * 2; k++)
        {
            while (1)
            {
                i = GetRandomScaledIslandTrainerId(challengeNum, k / 2);
                if (gPartnerTrainerId == i)
                    continue;

                for (j = 0; j < k; j++)
                {
                    if (gSaveBlock2Ptr->island.trainerIds[j] == i)
                        break;
                }
                if (j == k)
                    break;
            }
            gSaveBlock2Ptr->island.trainerIds[k] = i;
        }
        gSaveBlock2Ptr->island.trainerIds[17] = trainerId;
        break;
    case PARTNER_MSGID_REJECT:
        break;
    }

    if (trainerId == TRAINER_EREADER)
        return;

    // First check is redundant, only needs to make sure it's not an Apprentice
    if (trainerId < ISLAND_TRAINERS_COUNT)
    {
        ShowFieldMessage(sPartnerTrainerTextTables[partnerId].strings[gSpecialVar_0x8005]);
    }
    else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
    {
        ShowFieldMessage(sPartnerTrainerTextTables[partnerId].strings[gSpecialVar_0x8005]);
    }
    // Trainer is a former/record-mixed Apprentice, do Apprentice message
    else
    {
        u8 apprenticeId = gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].id;
        ShowFieldMessage(sPartnerApprenticeTextTables[apprenticeId][gSpecialVar_0x8005]);
    }
}

static void LoadLinkMultiOpponentsData(void)
{
    s32 challengeNum;
    s32 i, j;
    s32 trainerId = 0;
    u32 lvlMode = gSaveBlock2Ptr->island.lvlMode;
    u32 battleMode = VarGet(VAR_ISLAND_BATTLE_MODE);
    u32 battleNum = gSaveBlock2Ptr->island.curChallengeBattleNum;
    GetMultiplayerId(); // Yet another pointless function call.

    switch (gSpecialVar_Result)
    {
    case 0:
        if (battleMode == ISLAND_MODE_LINK_MULTIS)
        {
            challengeNum = gSaveBlock2Ptr->island.towerWinStreaks[battleMode][lvlMode] / ISLAND_STAGES_PER_CHALLENGE;
            if (IsLinkTaskFinished())
            {
                SendBlock(BitmaskAllOtherLinkPlayers(), &challengeNum, sizeof(challengeNum));
                gSpecialVar_Result = 1;
            }
        }
        else
        {
            gSpecialVar_Result = 6;
        }
        break;
    case 1:
        if ((GetBlockReceivedStatus() & 3) == 3)
        {
            ResetBlockReceivedFlags();
            if (gBlockRecvBuffer[0][0] > gBlockRecvBuffer[1][0])
                challengeNum = gBlockRecvBuffer[0][0];
            else
                challengeNum = gBlockRecvBuffer[1][0];
            for (i = 0; i < ISLAND_STAGES_PER_CHALLENGE * 2; i++)
            {
                do
                {
                    trainerId = GetRandomScaledIslandTrainerId(challengeNum, i / 2);
                    for (j = 0; j < i; j++)
                    {
                        if (gSaveBlock2Ptr->island.trainerIds[j] == trainerId)
                            break;
                    }
                } while (i != j);
                if (i == j) // This condition is always true, because of the loop above.
                    gSaveBlock2Ptr->island.trainerIds[i] = trainerId;
            }
            gSpecialVar_Result = 2;
        }
        break;
    case 2:
        if (IsLinkTaskFinished())
        {
            SendBlock(BitmaskAllOtherLinkPlayers(), &gSaveBlock2Ptr->island.trainerIds, sizeof(gSaveBlock2Ptr->island.trainerIds));
            gSpecialVar_Result = 3;
        }
        break;
    case 3:
        if ((GetBlockReceivedStatus() & 3) == 3)
        {
            ResetBlockReceivedFlags();
            memcpy(&gSaveBlock2Ptr->island.trainerIds, gBlockRecvBuffer, sizeof(gSaveBlock2Ptr->island.trainerIds));
            gTrainerBattleOpponent_A = gSaveBlock2Ptr->island.trainerIds[battleNum * 2];
            gTrainerBattleOpponent_B = gSaveBlock2Ptr->island.trainerIds[battleNum * 2 + 1];
            SetBattleGameFacilityTrainerGfxId(gTrainerBattleOpponent_A, 0);
            SetBattleGameFacilityTrainerGfxId(gTrainerBattleOpponent_B, 1);
            if (gReceivedRemoteLinkPlayers && gWirelessCommType == 0)
                gSpecialVar_Result = 4;
            else
                gSpecialVar_Result = 6;
        }
        break;
    case 4:
        SetCloseLinkCallback();
        gSpecialVar_Result = 5;
        break;
    case 5:
        if (gReceivedRemoteLinkPlayers == 0)
        {
            gSpecialVar_Result = 6;
        }
        break;
    case 6:
        return;
    }
}

static void MasterTryCloseLink(void)
{
    if (gWirelessCommType != 0)
        SetCloseLinkCallback();
}

static void SetMultiPartnerGfx(void)
{
    // 0xF below means use VAR_OBJ_GFX_ID_E
    SetBattleGameFacilityTrainerGfxId(gSaveBlock2Ptr->island.trainerIds[17], 0xF);
}

static void SetMasterInterviewData(void)
{
    s32 i;
    u8 text[32];

    if (VarGet(VAR_ISLAND_BATTLE_MODE) != ISLAND_MODE_SINGLES)
        return;

    GetIslandTrainerName(text, gTrainerBattleOpponent_A);
    StripExtCtrlCodes(text);
    StringCopy(gSaveBlock2Ptr->island.towerInterview.opponentName, text);
    GetSurvivalMasterTrainerLanguage(&gSaveBlock2Ptr->island.towerInterview.opponentLanguage, gTrainerBattleOpponent_A);
    gSaveBlock2Ptr->island.towerInterview.opponentSpecies = GetMonData(&gEnemyParty[gBattlerPartyIndexes[1]], MON_DATA_SPECIES, NULL);
    gSaveBlock2Ptr->island.towerInterview.playerSpecies = GetMonData(&gPlayerParty[gBattlerPartyIndexes[0]], MON_DATA_SPECIES, NULL);
    for (i = 0; i < VANILLA_POKEMON_NAME_LENGTH + 1; i++)
        gSaveBlock2Ptr->island.towerInterview.opponentMonNickname[i] = gBattleMons[0].nickname[i];
    gSaveBlock2Ptr->island.towerBattleOutcome = gBattleOutcome;
}

static void ValidateSurvivalMasterRecordChecksums(void)
{
    s32 i, j;
    u32 *record = (u32 *)(&gSaveBlock2Ptr->island.towerPlayer);
    u32 checksum = 0;

    for (j = 0; j < (sizeof(struct EmeraldSurvivalMasterRecord) - 4) / 4; j++) // - 4, because of the last field being the checksum itself.
    {
        checksum += record[j];
    }
    if (gSaveBlock2Ptr->island.towerPlayer.checksum != checksum)
        ClearSurvivalMasterRecord(&gSaveBlock2Ptr->island.towerPlayer);

    for (i = 0; i < SURVIVAL_MASTER_RECORD_COUNT; i++)
    {
        record = (u32 *)(&gSaveBlock2Ptr->island.towerRecords[i]);
        checksum = 0;
        for (j = 0; j < (sizeof(struct EmeraldSurvivalMasterRecord) - 4) / 4; j++) // - 4, because of the last field being the checksum itself.
        {
            checksum += record[j];
        }
        if (gSaveBlock2Ptr->island.towerRecords[i].checksum != checksum)
            ClearSurvivalMasterRecord(&gSaveBlock2Ptr->island.towerRecords[i]);
    }
}

void CalcEmeraldSurvivalMasterChecksum(struct EmeraldSurvivalMasterRecord *record)
{
    u32 i;

    record->checksum = 0;
    for (i = 0; i < (sizeof(struct EmeraldSurvivalMasterRecord) - 4) / 4; i++) // - 4, because of the last field being the checksum itself.
        record->checksum += ((u32 *)record)[i];
}

void CalcRubySurvivalMasterChecksum(struct RSSurvivalMasterRecord *record)
{
    u32 i;

    record->checksum = 0;
    for (i = 0; i < (sizeof(struct RSSurvivalMasterRecord) - 4) / 4; i++) // - 4, because of the last field being the checksum itself.
        record->checksum += ((u32 *)record)[i];
}

static void ClearSurvivalMasterRecord(struct EmeraldSurvivalMasterRecord *record)
{
    u32 i;

    for (i = 0; i < sizeof(struct EmeraldSurvivalMasterRecord) / 4; i++)
        ((u32 *)record)[i] = 0;
}

u16 GetCurrentSurvivalMasterWinStreak(u8 lvlMode, u8 battleMode)
{
    u16 winStreak = gSaveBlock2Ptr->island.towerWinStreaks[battleMode][lvlMode];

    if (winStreak > MAX_STREAK)
        return MAX_STREAK;
    else
        return winStreak;
}

static u8 GetMonCountForBattleMode(u8 battleMode)
{
    u8 partySizes[ARRAY_COUNT(sSurvivalMasterPartySizes)];
    memcpy(partySizes, sSurvivalMasterPartySizes, sizeof(sSurvivalMasterPartySizes));

    if (battleMode < ARRAY_COUNT(sSurvivalMasterPartySizes))
        return partySizes[battleMode];
    else
        return ISLAND_PARTY_SIZE;
}

struct RibbonCounter
{
    u8 partyIndex;
    u8 count;
};

static void AwardSurvivalMasterRibbons(void)
{
    s32 i;
    u32 partyIndex;
#ifdef BUGFIX
    struct RibbonCounter ribbons[MAX_ISLAND_PARTY_SIZE];
#else
    struct RibbonCounter ribbons[3]; // BUG: 4 Pokémon can receive ribbons in a double battle mode.
#endif
    u8 ribbonType = 0;
    u8 lvlMode = gSaveBlock2Ptr->island.lvlMode;
    u8 battleMode = VarGet(VAR_ISLAND_BATTLE_MODE);
    u8 monCount = GetMonCountForBattleMode(battleMode);

    if (lvlMode != ISLAND_LVL_50)
        ribbonType = MON_DATA_VICTORY_RIBBON;
    else
        ribbonType = MON_DATA_WINNING_RIBBON;

    gSpecialVar_Result = FALSE;

    if (GetCurrentSurvivalMasterWinStreak(lvlMode, battleMode) > 55)
    {
        for (i = 0; i < monCount; i++)
        {
            partyIndex = gSaveBlock2Ptr->island.selectedPartyMons[i] - 1;
            ribbons[i].partyIndex = partyIndex;
            ribbons[i].count = 0;
            if (!GetMonData(&gSaveBlock1Ptr->playerParty[partyIndex], ribbonType))
            {
                gSpecialVar_Result = TRUE;
                SetMonData(&gSaveBlock1Ptr->playerParty[partyIndex], ribbonType, &gSpecialVar_Result);
                ribbons[i].count = GetRibbonCount(&gSaveBlock1Ptr->playerParty[partyIndex]);
            }
        }
    }

    if (gSpecialVar_Result)
    {
        IncrementGameStat(GAME_STAT_RECEIVED_RIBBONS);
        for (i = 1; i < monCount; i++)
        {
            if (ribbons[i].count > ribbons[0].count)
            {
                struct RibbonCounter prevBest = ribbons[0];
                ribbons[0] = ribbons[i];
                ribbons[i] = prevBest;
            }
        }
        if (ribbons[0].count > NUM_CUTIES_RIBBONS)
        {
            TryPutSpotTheCutiesOnAir(&gSaveBlock1Ptr->playerParty[ribbons[0].partyIndex], ribbonType);
        }
    }
}

// This is a leftover debugging function that is used to populate the E-Reader
// trainer with the player's current data.
static void UNUSED FillEReaderTrainerWithPlayerData(void)
{
#if FREE_SURVIVAL_MASTER_E_READER == FALSE
    struct SurvivalMasterEReaderTrainer *ereaderTrainer = &gSaveBlock2Ptr->island.ereaderTrainer;
    s32 i, j;

    if (gSaveBlock2Ptr->playerGender != MALE)
    {
        ereaderTrainer->facilityClass = gMasterFemaleGameFacilityClasses[(gSaveBlock2Ptr->playerTrainerId[0] + gSaveBlock2Ptr->playerTrainerId[1]
                                                        + gSaveBlock2Ptr->playerTrainerId[2] + gSaveBlock2Ptr->playerTrainerId[3]) % ARRAY_COUNT(gMasterFemaleGameFacilityClasses)];
    }
    else
    {
        ereaderTrainer->facilityClass = gMasterMaleGameFacilityClasses[(gSaveBlock2Ptr->playerTrainerId[0] + gSaveBlock2Ptr->playerTrainerId[1]
                                                        + gSaveBlock2Ptr->playerTrainerId[2] + gSaveBlock2Ptr->playerTrainerId[3]) % ARRAY_COUNT(gMasterMaleGameFacilityClasses)];
    }

    CopyTrainerId(ereaderTrainer->trainerId, gSaveBlock2Ptr->playerTrainerId);
    StringCopy_PlayerName(ereaderTrainer->name, gSaveBlock2Ptr->playerName);

    ereaderTrainer->winStreak = 1;

    j = 7;
    for (i = 0; i < EASY_CHAT_BATTLE_WORDS_COUNT; i++)
    {
        ereaderTrainer->greeting[i] = gSaveBlock1Ptr->easyChatBattleStart[i];
        ereaderTrainer->farewellPlayerLost[i] = j;
        ereaderTrainer->farewellPlayerWon[i] = j + 6;
        j++;
    }

    for (i = 0; i < (int)ARRAY_COUNT(ereaderTrainer->party); i++)
        ConvertPokemonToSurvivalMasterPokemon(&gPlayerParty[i], &ereaderTrainer->party[i]);

    SetEReaderTrainerChecksum(ereaderTrainer);
#endif //FREE_SURVIVAL_MASTER_E_READER
}

u8 GetEreaderTrainerFrontSpriteId(void)
{
#if FREE_SURVIVAL_MASTER_E_READER == FALSE
    return gGameFacilityClassToPicIndex[gSaveBlock2Ptr->island.ereaderTrainer.facilityClass];
#else
    return 0;
#endif //FREE_SURVIVAL_MASTER_E_READER
}

u8 GetEreaderTrainerClassId(void)
{
#if FREE_SURVIVAL_MASTER_E_READER == FALSE
    return gGameFacilityClassToTrainerClass[gSaveBlock2Ptr->island.ereaderTrainer.facilityClass];
#else
    return 0;
#endif //FREE_SURVIVAL_MASTER_E_READER
}

void GetEreaderTrainerName(u8 *dst)
{
#if FREE_SURVIVAL_MASTER_E_READER == FALSE
    s32 i;

    for (i = 0; i < 5; i++)
        dst[i] = gSaveBlock2Ptr->island.ereaderTrainer.name[i];

    dst[i] = EOS;
#else
    dst[0] = EOS;
#endif //FREE_SURVIVAL_MASTER_E_READER
}

// Checks if the saved E-Reader trainer is valid.
void ValidateEReaderTrainer(void)
{
#if FREE_SURVIVAL_MASTER_E_READER == FALSE
    u32 i;
    u32 checksum;
    struct SurvivalMasterEReaderTrainer *ereaderTrainer;

    gSpecialVar_Result = FALSE;
    ereaderTrainer = &gSaveBlock2Ptr->island.ereaderTrainer;

    checksum = 0;
    for (i = 0; i < (sizeof(struct SurvivalMasterEReaderTrainer) - 4) / 4; i++) // - 4, because of the last field being the checksum itself.
        checksum |= ((u32 *)ereaderTrainer)[i];

    if (checksum == 0)
    {
        gSpecialVar_Result = TRUE;
        return;
    }

    checksum = 0;
    for (i = 0; i < (sizeof(struct SurvivalMasterEReaderTrainer) - 4) / 4; i++) // - 4, because of the last field being the checksum itself.
        checksum += ((u32 *)ereaderTrainer)[i];

    if (gSaveBlock2Ptr->island.ereaderTrainer.checksum != checksum)
    {
        ClearEReaderTrainer(&gSaveBlock2Ptr->island.ereaderTrainer);
        gSpecialVar_Result = TRUE;
    }
#else
    gSpecialVar_Result = FALSE;
#endif //FREE_SURVIVAL_MASTER_E_READER
}

#if FREE_SURVIVAL_MASTER_E_READER == FALSE
static void SetEReaderTrainerChecksum(struct SurvivalMasterEReaderTrainer *ereaderTrainer)
{
    s32 i;

    ereaderTrainer->checksum = 0;
    for (i = 0; i < (sizeof(struct SurvivalMasterEReaderTrainer) - 4) / 4; i++) // - 4, because of the last field being the checksum itself.
        ereaderTrainer->checksum += ((u32 *)ereaderTrainer)[i];
}
#endif //FREE_SURVIVAL_MASTER_E_READER

void ClearEReaderTrainer(struct SurvivalMasterEReaderTrainer *ereaderTrainer)
{
#if FREE_SURVIVAL_MASTER_E_READER == FALSE
    u32 i;

    for (i = 0; i < (sizeof(struct SurvivalMasterEReaderTrainer)) / 4; i++)
        ((u32 *)ereaderTrainer)[i] = 0;
#endif //FREE_SURVIVAL_MASTER_E_READER
}

void CopyEReaderTrainerGreeting(void)
{
#if FREE_SURVIVAL_MASTER_E_READER == FALSE
    IslandSpeechToString(gSaveBlock2Ptr->island.ereaderTrainer.greeting);
#endif //FREE_SURVIVAL_MASTER_E_READER
}

static void CopyEReaderTrainerFarewellMessage(void)
{
#if FREE_SURVIVAL_MASTER_E_READER == FALSE
    if (gBattleOutcome == B_OUTCOME_DREW)
        gStringVar4[0] = EOS;
    else if (gBattleOutcome == B_OUTCOME_WON)
        IslandSpeechToString(gSaveBlock2Ptr->island.ereaderTrainer.farewellPlayerWon);
    else
        IslandSpeechToString(gSaveBlock2Ptr->island.ereaderTrainer.farewellPlayerLost);
#endif //FREE_SURVIVAL_MASTER_E_READER
}

void TryHideSurvivalMasterReporter(void)
{
    if (gSaveBlock2Ptr->island.challengeStatus == CHALLENGE_STATUS_SAVING)
        HideSurvivalMasterReporter();
    if (FlagGet(FLAG_CANCEL_BATTLE_ROOM_CHALLENGE) == TRUE)
    {
        HideSurvivalMasterReporter();
        FlagClear(FLAG_CANCEL_BATTLE_ROOM_CHALLENGE);
    }
}

#define STEVEN_OTID 61226

static void FillPartnerParty(u16 trainerId)
{
    s32 i, j, k;
    u32 firstIdPart = 0, secondIdPart = 0, thirdIdPart = 0;
    u32 ivs, level, personality;
    u16 monId;
    u32 otID;
    u8 trainerName[(PLAYER_NAME_LENGTH * 3) + 1];
    s32 ball = -1;
    SetGameFacilityPtrsGetLevel();

    if (trainerId > TRAINER_PARTNER(PARTNER_NONE))
    {
        for (i = 0; i < 3; i++)
            ZeroMonData(&gPlayerParty[i + 3]);

        for (i = 0; i < 3 && i < gBattlePartners[trainerId - TRAINER_PARTNER(PARTNER_NONE)].partySize; i++)
        {
            const struct TrainerMon *partyData = gBattlePartners[trainerId - TRAINER_PARTNER(PARTNER_NONE)].party;
            const u8 *partnerName = gBattlePartners[trainerId - TRAINER_PARTNER(PARTNER_NONE)].trainerName;

            for (k = 0; partnerName[k] != EOS && k < 3; k++)
            {
                if (k == 0)
                {
                    firstIdPart = partnerName[k];
                    secondIdPart = partnerName[k];
                    thirdIdPart = partnerName[k];
                }
                else if (k == 1)
                {
                    secondIdPart = partnerName[k];
                    thirdIdPart = partnerName[k];
                }
                else if (k == 2)
                {
                    thirdIdPart = partnerName[k];
                }
            }
            if (trainerId == TRAINER_PARTNER(PARTNER_STEVEN))
                otID = STEVEN_OTID;
            else
                otID = ((firstIdPart % 72) * 1000) + ((secondIdPart % 23) * 10) + (thirdIdPart % 37) % 65536;

            personality = Random32();
            if (partyData[i].gender == TRAINER_MON_MALE)
                personality = (personality & 0xFFFFFF00) | GeneratePersonalityForGender(MON_MALE, partyData[i].species);
            else if (partyData[i].gender == TRAINER_MON_FEMALE)
                personality = (personality & 0xFFFFFF00) | GeneratePersonalityForGender(MON_FEMALE, partyData[i].species);
            ModifyPersonalityForNature(&personality, partyData[i].nature);
            CreateMon(&gPlayerParty[i + 3], partyData[i].species, partyData[i].lvl, 0, TRUE, personality, OT_ID_PRESET, otID);
            j = partyData[i].isShiny;
            SetMonData(&gPlayerParty[i + 3], MON_DATA_IS_SHINY, &j);
            SetMonData(&gPlayerParty[i + 3], MON_DATA_HELD_ITEM, &partyData[i].heldItem);
            CustomTrainerPartyAssignMoves(&gPlayerParty[i + 3], &partyData[i]);

            SetMonData(&gPlayerParty[i + 3], MON_DATA_IVS, &(partyData[i].iv));
            if (partyData[i].ev != NULL)
            {
                SetMonData(&gPlayerParty[i + 3], MON_DATA_HP_EV, &(partyData[i].ev[0]));
                SetMonData(&gPlayerParty[i + 3], MON_DATA_ATK_EV, &(partyData[i].ev[1]));
                SetMonData(&gPlayerParty[i + 3], MON_DATA_DEF_EV, &(partyData[i].ev[2]));
                SetMonData(&gPlayerParty[i + 3], MON_DATA_SPATK_EV, &(partyData[i].ev[3]));
                SetMonData(&gPlayerParty[i + 3], MON_DATA_SPDEF_EV, &(partyData[i].ev[4]));
                SetMonData(&gPlayerParty[i + 3], MON_DATA_SPEED_EV, &(partyData[i].ev[5]));
            }
            if (partyData[i].ability != ABILITY_NONE)
            {
                const struct SpeciesInfo *speciesInfo = &gSpeciesInfo[partyData[i].species];
                u32 maxAbilities = ARRAY_COUNT(speciesInfo->abilities);
                for (j = 0; j < maxAbilities; j++)
                {
                    if (speciesInfo->abilities[j] == partyData[i].ability)
                        break;
                }
                if (j < maxAbilities)
                    SetMonData(&gPlayerParty[i + 3], MON_DATA_ABILITY_NUM, &j);
            }
            SetMonData(&gPlayerParty[i + 3], MON_DATA_FRIENDSHIP, &(partyData[i].friendship));
            if (partyData[i].ball != ITEM_NONE)
            {
                ball = partyData[i].ball;
                SetMonData(&gPlayerParty[i + 3], MON_DATA_POKEBALL, &ball);
            }
            if (partyData[i].nickname != NULL)
            {
                SetMonData(&gPlayerParty[i + 3], MON_DATA_NICKNAME, partyData[i].nickname);
            }
            CalculateMonStats(&gPlayerParty[i + 3]);

            StringCopy(trainerName, gBattlePartners[trainerId - TRAINER_PARTNER(PARTNER_NONE)].trainerName);
            SetMonData(&gPlayerParty[i + 3], MON_DATA_OT_NAME, trainerName);
            j = gBattlePartners[SanitizeTrainerId(trainerId - TRAINER_PARTNER(PARTNER_NONE))].encounterMusic_gender >> 7;
            SetMonData(&gPlayerParty[i + 3], MON_DATA_OT_GENDER, &j);
        }
    }
    else if (trainerId == TRAINER_EREADER)
    {
        // Scrapped, lol.
        trainerName[0] = gGameLanguage;
    }
    else if (trainerId < ISLAND_TRAINERS_COUNT)
    {
        level = SetGameFacilityPtrsGetLevel();
        ivs = GetIslandTrainerFixedIvs(trainerId);
        otID = Random32();
        for (i = 0; i < ISLAND_MULTI_PARTY_SIZE; i++)
        {
            monId = gSaveBlock2Ptr->island.trainerIds[i + 18];
            CreateGameFacilityMon(&gGameFacilityTrainerMons[monId], level, ivs, otID, 0, &gPlayerParty[MULTI_PARTY_SIZE + i]);
            for (j = 0; j < PLAYER_NAME_LENGTH + 1; j++)
                trainerName[j] = gGameFacilityTrainers[trainerId].trainerName[j];
            SetMonData(&gPlayerParty[MULTI_PARTY_SIZE + i], MON_DATA_OT_NAME, &trainerName);
            j = IsIslandTrainerFemale(trainerId);
            SetMonData(&gPlayerParty[MULTI_PARTY_SIZE + i], MON_DATA_OT_GENDER, &j);
        }
    }
    else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
    {
        trainerId -= TRAINER_RECORD_MIXING_FRIEND;
        for (i = 0; i < ISLAND_MULTI_PARTY_SIZE; i++)
        {
            struct EmeraldSurvivalMasterRecord *record = &gSaveBlock2Ptr->island.towerRecords[trainerId];
            struct SurvivalMasterPokemon monData = record->party[gSaveBlock2Ptr->island.trainerIds[18 + i]];
            StringCopy(trainerName, record->name);
            if (record->language == LANGUAGE_JAPANESE)
            {
                if (monData.nickname[0] != EXT_CTRL_CODE_BEGIN || monData.nickname[1] != EXT_CTRL_CODE_JPN)
                {
                    monData.nickname[5] = EOS;
                    ConvertInternationalString(monData.nickname, LANGUAGE_JAPANESE);
                }
            }
            else
            {
                if (monData.nickname[0] == EXT_CTRL_CODE_BEGIN && monData.nickname[1] == EXT_CTRL_CODE_JPN)
                    trainerName[5] = EOS;
            }
            CreateSurvivalMasterMon_HandleLevel(&gPlayerParty[MULTI_PARTY_SIZE + i], &monData, TRUE);
            SetMonData(&gPlayerParty[MULTI_PARTY_SIZE + i], MON_DATA_OT_NAME, trainerName);
            j = IsIslandTrainerFemale(trainerId + TRAINER_RECORD_MIXING_FRIEND);
            SetMonData(&gPlayerParty[MULTI_PARTY_SIZE + i], MON_DATA_OT_GENDER, &j);
        }
    }
    else
    {
        trainerId -= TRAINER_RECORD_MIXING_APPRENTICE;
        for (i = 0; i < ISLAND_MULTI_PARTY_SIZE; i++)
        {
            CreateApprenticeMon(&gPlayerParty[MULTI_PARTY_SIZE + i], &gSaveBlock2Ptr->apprentices[trainerId], gSaveBlock2Ptr->island.trainerIds[18 + i]);
            j = IsIslandTrainerFemale(trainerId + TRAINER_RECORD_MIXING_APPRENTICE);
            SetMonData(&gPlayerParty[MULTI_PARTY_SIZE + i], MON_DATA_OT_GENDER, &j);
        }
    }
}

bool32 RubySurvivalMasterRecordToEmerald(struct RSSurvivalMasterRecord *src, struct EmeraldSurvivalMasterRecord *dst)
{
    s32 i, validMons = 0;

    for (i = 0; i < ISLAND_PARTY_SIZE; i++)
    {
        if (src->party[i].species)
            validMons++;
    }

    if (validMons != ISLAND_PARTY_SIZE)
    {
        memset(dst, 0, sizeof(*dst));
        return FALSE;
    }
    else
    {
        dst->lvlMode = src->lvlMode;
        dst->winStreak = src->winStreak;
        // UB: Reading outside the array. sRubyGameFacilityClassToEmerald has less than FACILITY_CLASSES_COUNT entries.
        #ifdef UBFIX
        for (i = 0; i < ARRAY_COUNT(sRubyGameFacilityClassToEmerald); i++)
        #else
        for (i = 0; i < FACILITY_CLASSES_COUNT; i++)
        #endif
        {
            if (sRubyGameFacilityClassToEmerald[i][0] == src->facilityClass)
                break;
        }
        if (i != FACILITY_CLASSES_COUNT)
            dst->facilityClass = sRubyGameFacilityClassToEmerald[i][1];
        else
            dst->facilityClass = FACILITY_CLASS_YOUNGSTER;

        for (i = 0; i < PLAYER_NAME_LENGTH + 1; i++)
            dst->name[i] = src->name[i];
        for (i = 0; i < TRAINER_ID_LENGTH; i++)
            dst->trainerId[i] = src->trainerId[i];
        for (i = 0; i < EASY_CHAT_BATTLE_WORDS_COUNT; i++)
            dst->greeting[i] = src->greeting[i];
        for (i = 0; i < EASY_CHAT_BATTLE_WORDS_COUNT; i++)
            dst->speechWon[i] = sRecordTrainerSpeechWon[i];
        for (i = 0; i < EASY_CHAT_BATTLE_WORDS_COUNT; i++)
            dst->speechLost[i] = sRecordTrainerSpeechLost[i];
        for (i = 0; i < ISLAND_PARTY_SIZE; i++)
            dst->party[i] = src->party[i];

        CpuFill32(0, &dst->party[ISLAND_PARTY_SIZE], sizeof(dst->party[ISLAND_PARTY_SIZE]));
        CalcEmeraldSurvivalMasterChecksum(dst);
        return TRUE;
    }
}

bool32 EmeraldSurvivalMasterRecordToRuby(struct EmeraldSurvivalMasterRecord *src, struct RSSurvivalMasterRecord *dst)
{
    s32 i, validMons = 0;

    for (i = 0; i < ISLAND_PARTY_SIZE; i++)
    {
        if (src->party[i].species)
            validMons++;
    }

    if (validMons != ISLAND_PARTY_SIZE)
    {
        memset(dst, 0, sizeof(*dst));
        return FALSE;
    }
    else
    {
        dst->lvlMode = src->lvlMode;
        dst->winStreak = src->winStreak;
        // UB: Reading outside the array. sRubyGameFacilityClassToEmerald has less than FACILITY_CLASSES_COUNT entries.
        #ifdef UBFIX
        for (i = 0; i < ARRAY_COUNT(sRubyGameFacilityClassToEmerald); i++)
        #else
        for (i = 0; i < FACILITY_CLASSES_COUNT; i++)
        #endif
        {
            if (sRubyGameFacilityClassToEmerald[i][1] == src->facilityClass)
                break;
        }
        if (i != FACILITY_CLASSES_COUNT)
            dst->facilityClass = sRubyGameFacilityClassToEmerald[i][0];
        else
            dst->facilityClass = RS_FACILITY_CLASS_YOUNGSTER;

        for (i = 0; i < PLAYER_NAME_LENGTH + 1; i++)
            dst->name[i] = src->name[i];
        for (i = 0; i < TRAINER_ID_LENGTH; i++)
            dst->trainerId[i] = src->trainerId[i];
        for (i = 0; i < EASY_CHAT_BATTLE_WORDS_COUNT; i++)
            dst->greeting[i] = src->greeting[i];
        for (i = 0; i < ISLAND_PARTY_SIZE; i++)
            dst->party[i] = src->party[i];

        CalcRubySurvivalMasterChecksum(dst);
        return TRUE;
    }
}

void CalcApprenticeChecksum(struct Apprentice *apprentice)
{
    s32 i;

    apprentice->checksum = 0;
    for (i = 0; i < offsetof(struct Apprentice, checksum) / sizeof(u32); i++)
        apprentice->checksum += ((u32 *)apprentice)[i];
}

static void ClearApprentice(struct Apprentice *apprentice)
{
    s32 i;

    for (i = 0; i < sizeof(struct Apprentice) / sizeof(u32); i++)
        ((u32 *)apprentice)[i] = 0;
    ResetApprenticeStruct(apprentice);
}

static void ValidateApprenticesChecksums(void)
{
    s32 i, j;

    for (i = 0; i < APPRENTICE_COUNT; i++)
    {
        u32 *data = (u32 *) &gSaveBlock2Ptr->apprentices[i];
        u32 checksum = 0;
        for (j = 0; j < offsetof(struct Apprentice, checksum) / sizeof(u32); j++)
            checksum += data[j];
        if (gSaveBlock2Ptr->apprentices[i].checksum != checksum)
            ClearApprentice(&gSaveBlock2Ptr->apprentices[i]);
    }
}

void GetSurvivalMasterTrainerLanguage(u8 *dst, u16 trainerId)
{
    if (trainerId == TRAINER_EREADER)
    {
        *dst = gGameLanguage;
    }
    else if (trainerId < ISLAND_TRAINERS_COUNT)
    {
        *dst = gGameLanguage;
    }
    else if (trainerId < TRAINER_RECORD_MIXING_APPRENTICE)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
            *dst = GetRecordedBattleRecordMixFriendLanguage();
        else
            *dst = gSaveBlock2Ptr->island.towerRecords[trainerId - TRAINER_RECORD_MIXING_FRIEND].language;
    }
    else
    {
        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
            *dst = GetRecordedBattleApprenticeLanguage();
        else
            *dst = gSaveBlock2Ptr->apprentices[trainerId - TRAINER_RECORD_MIXING_APPRENTICE].language;
    }
}

u8 SetGameFacilityPtrsGetLevel(void)
{
    if (gSaveBlock2Ptr->island.lvlMode == ISLAND_LVL_TENT)
    {
        return SetTentPtrsGetLevel();
    }
    else
    {
        gGameFacilityTrainers = gSurvivalIslandTrainers;
        gGameFacilityTrainerMons = gSurvivalIslandMons;
        return GetIslandEnemyMonLevel(gSaveBlock2Ptr->island.lvlMode);
    }
}

u8 GetIslandEnemyMonLevel(u8 lvlMode)
{
    u8 level;

    switch (lvlMode)
    {
    default:
    case ISLAND_LVL_50:
        level = ISLAND_MAX_LEVEL_50;
        break;
    case ISLAND_LVL_OPEN:
        level = GetHighestLevelInPlayerParty();
        if (level < ISLAND_MIN_LEVEL_OPEN)
            level = ISLAND_MIN_LEVEL_OPEN;
        break;
    }

    return level;
}

s32 GetHighestLevelInPlayerParty(void)
{
    s32 highestLevel = 0;
    s32 i;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES, NULL)
            && GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_EGG)
        {
            s32 level = GetMonData(&gPlayerParty[i], MON_DATA_LEVEL, NULL);
            if (level > highestLevel)
                highestLevel = level;
        }
    }

    return highestLevel;
}

// Island Trainer parties are roughly scaled in difficulty with higher trainer IDs, so scale IVs as well
// Duplicated in Battle Dome as GetDomeTrainerMonIvs
static u8 GetIslandTrainerFixedIvs(u16 trainerId)
{
    u8 fixedIv;

    if (trainerId <= ISLAND_TRAINER_JILL)         // 0 - 99
        fixedIv = 3;
    else if (trainerId <= ISLAND_TRAINER_CHLOE)   // 100 - 119
        fixedIv = 6;
    else if (trainerId <= ISLAND_TRAINER_SOFIA)   // 120 - 139
        fixedIv = 9;
    else if (trainerId <= ISLAND_TRAINER_JAZLYN)  // 140 - 159
        fixedIv = 12;
    else if (trainerId <= ISLAND_TRAINER_ALISON)  // 160 - 179
        fixedIv = 15;
    else if (trainerId <= ISLAND_TRAINER_LAMAR)   // 180 - 199
        fixedIv = 18;
    else if (trainerId <= ISLAND_TRAINER_TESS)    // 200 - 219
        fixedIv = 21;
    else                                            // 220+ (- 299)
        fixedIv = MAX_PER_STAT_IVS;

    return fixedIv;
}

static u16 GetBattleTentTrainerId(void)
{
    u32 facility = VarGet(VAR_ISLAND_FACILITY);

    if (facility == ISLAND_FACILITY_PALACE)       // Verdanturf Tent; uses Palace mechanics
        return Random() % NUM_BATTLE_TENT_TRAINERS;
    else if (facility == ISLAND_FACILITY_ARENA)   // Fallarbor Tent; uses Arena mechanics
        return Random() % NUM_BATTLE_TENT_TRAINERS;
    else if (facility == ISLAND_FACILITY_FACTORY) // Slateport Tent; uses Factory mechanics
        return Random() % NUM_BATTLE_TENT_TRAINERS;
    else if (facility == ISLAND_FACILITY_TOWER)
        return 0;
    else
        return 0;
}

static u8 SetTentPtrsGetLevel(void)
{
    u8 level = TENT_MIN_LEVEL;
    u32 facility = VarGet(VAR_ISLAND_FACILITY);

    if (facility == ISLAND_FACILITY_FACTORY)
    {
        gGameFacilityTrainers = gSlateportBattleTentTrainers;
        gGameFacilityTrainerMons = gSlateportBattleTentMons;
    }
    else if (facility == ISLAND_FACILITY_PALACE)
    {
        gGameFacilityTrainers = gVerdanturfBattleTentTrainers;
        gGameFacilityTrainerMons = gVerdanturfBattleTentMons;
    }
    else if (facility == ISLAND_FACILITY_ARENA)
    {
        gGameFacilityTrainers = gFallarborBattleTentTrainers;
        gGameFacilityTrainerMons = gFallarborBattleTentMons;
    }
    else
    {
        gGameFacilityTrainers = gSurvivalIslandTrainers;
        gGameFacilityTrainerMons = gSurvivalIslandMons;
    }

    level = GetHighestLevelInPlayerParty();
    if (level < TENT_MIN_LEVEL)
        level = TENT_MIN_LEVEL;

    return level;
}

static void SetNextBattleTentOpponent(void)
{
    s32 i;
    u16 trainerId;

    do
    {
        trainerId = GetBattleTentTrainerId();
        for (i = 0; i < gSaveBlock2Ptr->island.curChallengeBattleNum; i++)
        {
            if (gSaveBlock2Ptr->island.trainerIds[i] == trainerId)
                break;
        }
    } while (i != gSaveBlock2Ptr->island.curChallengeBattleNum);

    gTrainerBattleOpponent_A = trainerId;
    SetBattleGameFacilityTrainerGfxId(gTrainerBattleOpponent_A, 0);
    if (gSaveBlock2Ptr->island.curChallengeBattleNum + 1 < TENT_STAGES_PER_CHALLENGE)
       gSaveBlock2Ptr->island.trainerIds[gSaveBlock2Ptr->island.curChallengeBattleNum] = gTrainerBattleOpponent_A;
}

static void FillTentTrainerParty_(u16 trainerId, u8 firstMonId, u8 monCount)
{
    s32 i, j;
    u16 chosenMonIndices[MAX_ISLAND_PARTY_SIZE];
    u8 level = SetTentPtrsGetLevel();
    u8 fixedIV = 0;
    u8 bfMonCount;
    const u16 *monSet = NULL;
    u32 otID = 0;
    u16 monId;

    monSet = gGameFacilityTrainers[gTrainerBattleOpponent_A].monSet;

    bfMonCount = 0;
    monId = monSet[bfMonCount];
    while (monId != 0xFFFF)
    {
        bfMonCount++;
        monId = monSet[bfMonCount];
        if (monId == 0xFFFF)
            break;
    }

    i = 0;
    otID = Random32();
    while (i != monCount)
    {
        u16 monId = monSet[Random() % bfMonCount];

        // Ensure this Pokémon species isn't a duplicate.
        for (j = 0; j < i + firstMonId; j++)
        {
            if (GetMonData(&gEnemyParty[j], MON_DATA_SPECIES, NULL) == gGameFacilityTrainerMons[monId].species)
                break;
        }
        if (j != i + firstMonId)
            continue;

        // Ensure this Pokemon's held item isn't a duplicate.
        for (j = 0; j < i + firstMonId; j++)
        {
            if (GetMonData(&gEnemyParty[j], MON_DATA_HELD_ITEM, NULL) != ITEM_NONE
             && GetMonData(&gEnemyParty[j], MON_DATA_HELD_ITEM, NULL) == gGameFacilityTrainerMons[monId].heldItem)
                break;
        }
        if (j != i + firstMonId)
            continue;

        // Ensure this exact Pokémon index isn't a duplicate. This check doesn't seem necessary
        // because the species and held items were already checked directly above.
        for (j = 0; j < i; j++)
        {
            if (chosenMonIndices[j] == monId)
                break;
        }
        if (j != i)
            continue;

        chosenMonIndices[i] = monId;
        CreateGameFacilityMon(&gGameFacilityTrainerMons[monId],
                level, fixedIV, otID, 0,
                &gEnemyParty[i + firstMonId]);

        // The Pokémon was successfully added to the trainer's party, so it's safe to move on to
        // the next party slot.
        i++;
    }
}

u16 GameFacilityClassToGraphicsId(u8 facilityClass)
{
    u16 trainerObjectGfxId;
    u8 i;

    // Search male classes.
    for (i = 0; i < ARRAY_COUNT(gMasterMaleGameFacilityClasses); i++)
    {
        if (gMasterMaleGameFacilityClasses[i] == facilityClass)
            break;
    }
    if (i != ARRAY_COUNT(gMasterMaleGameFacilityClasses))
    {
        trainerObjectGfxId = gMasterMaleTrainerGfxIds[i];
        return trainerObjectGfxId;
    }

    // Search female classes.
    for (i = 0; i < ARRAY_COUNT(gMasterFemaleGameFacilityClasses); i++)
    {
        if (gMasterFemaleGameFacilityClasses[i] == facilityClass)
            break;
    }
    if (i != ARRAY_COUNT(gMasterFemaleGameFacilityClasses))
    {
        trainerObjectGfxId = gMasterFemaleTrainerGfxIds[i];
        return trainerObjectGfxId;
    }
    else
    {
        return OBJ_EVENT_GFX_BOY_1;
    }
}

bool32 ValidateSurvivalMasterRecord(u8 recordId) // unused
{
    s32 i;
    u32 *record = (u32 *)(&gSaveBlock2Ptr->island.towerRecords[recordId]);
    u32 checksum = 0;
    u32 hasData = 0;
    for (i = 0; i < offsetof(struct EmeraldSurvivalMasterRecord, checksum) / sizeof(u32); i++)
    {
        checksum += record[i];
        hasData |= record[i];
    }

    if (checksum == 0 && hasData == 0)
    {
        return FALSE;
    }
    else if (gSaveBlock2Ptr->island.towerRecords[recordId].checksum != checksum)
    {
        ClearSurvivalMasterRecord(&gSaveBlock2Ptr->island.towerRecords[recordId]);
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}
/*
void TrySetLinkSurvivalMasterEnemyPartyLevel(void)
{
    if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
    {
        s32 i;
        u8 enemyLevel = SetGameFacilityPtrsGetLevel();

        for (i = 0; i < PARTY_SIZE; i++)
        {
            u32 species = GetMonData(&gEnemyParty[i], MON_DATA_SPECIES, NULL);
            if (species)
            {
                SetMonData(&gEnemyParty[i], MON_DATA_EXP, &gExperienceTables[gSpeciesInfo[species].growthRate][enemyLevel]);
                CalculateMonStats(&gEnemyParty[i]);
            }
        }
    }
}*/