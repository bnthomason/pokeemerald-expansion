#ifdef __INTELLISENSE__
const struct SpeciesInfo gSpeciesInfoGenX[] =
{
#endif

#if P_FAMILY_DRACOCEROS_HERO
    [SPECIES_DRACOCEROS_HOLY_CHILD]
    {
        .baseHP        = 30,
        .baseAttack    = 30,
        .baseDefense   = 15,
        .baseSpeed     = 120,
        .baseSpAttack  = 45,
        .baseSpDefense = 60,
            .types = MON_TYPES(TYPE_LIGHT, TYPE_FLYING),
        .catchRate = 60,
        .expYield = 318,
        .evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_DRAGON),
        .abilities = { ABILITY_LIGHTWING, ABILITY_NONE, ABILITY_LIGHTWING },
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("Dracoceros"),
        .cryId = CRY_MILOTIC,
        .natDexNum = NATIONAL_DEX_DRACOCEROS_CHILD,
        .categoryName = _("Dragon Hero"),
        .height = 62,
        .weight = 1620,
        .description = COMPOUND_STRING(
            "The young are playful, naive, and\n"
            "innocent. They are quick to trust\n"
            "strangers and will frolick around\n"
            "them as a sign of friendship."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_DracocerosHolyChild,
        .frontPicFemale = gMonFrontPic_DracocerosHolyChildF,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicSizeFemale = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 2,
        .frontAnimFrames = sAnims_DracocerosHolyChild,
        .frontAnimId = ANIM_CIRCULAR_STRETCH_TWICE,
        .frontAnimDelay = 45,
        .backPic = gMonBackPic_DracocerosHolyChild,
        .backPicFemale = gMonBackPic_DracocerosHolyChildF,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicSizeFemale = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_CONVEX_DOUBLE_ARC,
        .palette = gMonPalette_DracocerosHolyChild,
        .shinyPalette = gMonShinyPalette_DracocerosHolyChild,
        .iconSprite = gMonIcon_DracocerosHolyChild,
        .iconPalIndex = 2,
        FOOTPRINT(DracocerosHolyChild)
        OVERWORLD(
            sPicTable_DracocerosHolyChild,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            gOverworldPalette_DracocerosHolyChild,
            gShinyOverworldPalette_DracocerosHolyChild
        )
        .levelUpLearnset = sDracocerosHolyChildLevelUpLearnset,
        .teachableLearnset = sDracocerosHolyChildTeachableLearnset,
        .eggMoveLearnset = sDracocerosHolyChildEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 25, SPECIES_DRACOCEROS_HOLY_JUVENILE}),
    },

    [SPECIES_DRACOCEROS_HOLY_JUVENILE]
    {
        .baseHP        = 45,
        .baseAttack    = 45,
        .baseDefense   = 20,
        .baseSpeed     = 180,
        .baseSpAttack  = 70,
        .baseSpDefense = 90,
        .types = MON_TYPES(TYPE_LIGHT, TYPE_FLYING),
        .catchRate = 60,
        .expYield = 318,
        .evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_DRAGON),
        .abilities = { ABILITY_LIGHTWING, ABILITY_NONE, ABILITY_LIGHTWING },
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("Dracoceros"),
        .cryId = CRY_MILOTIC,
        .natDexNum = NATIONAL_DEX_DRACOCEROS_JUVENILE,
        .categoryName = _("Dragon Hero"),
        .height = 62,
        .weight = 1620,
        .description = COMPOUND_STRING(
            "The young are playful, naive, and\n"
            "innocent. They are quick to trust\n"
            "strangers and will frolick around\n"
            "them as a sign of friendship."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_DracocerosHolyChild,
        .frontPicFemale = gMonFrontPic_DracocerosHolyChildF,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicSizeFemale = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 2,
        .frontAnimFrames = sAnims_DracocerosHolyChild,
        .frontAnimId = ANIM_CIRCULAR_STRETCH_TWICE,
        .frontAnimDelay = 45,
        .backPic = gMonBackPic_DracocerosHolyChild,
        .backPicFemale = gMonBackPic_DracocerosHolyChildF,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicSizeFemale = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_CONVEX_DOUBLE_ARC,
        .palette = gMonPalette_DracocerosHolyChild,
        .shinyPalette = gMonShinyPalette_DracocerosHolyChild,
        .iconSprite = gMonIcon_DracocerosHolyChild,
        .iconPalIndex = 2,
        FOOTPRINT(DracocerosHolyChild)
        OVERWORLD(
            sPicTable_DracocerosHolyChild,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            gOverworldPalette_DracocerosHolyChild,
            gShinyOverworldPalette_DracocerosHolyChild
        )
        .levelUpLearnset = sDracocerosHolyChildLevelUpLearnset,
        .teachableLearnset = sDracocerosHolyChildTeachableLearnset,
        .eggMoveLearnset = sDracocerosHolyChildEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 25, SPECIES_DRACOCEROS_HOLY_JUVENILE}),
},


    [SPECIES_DRACOCEROS_HOLY_ADULT]
    {
            .baseHP        = 30,
            .baseAttack    = 30,
            .baseDefense   = 15,
            .baseSpeed     = 120,
            .baseSpAttack  = 45,
            .baseSpDefense = 60,
                .types = MON_TYPES(TYPE_LIGHT, TYPE_FLYING),
            .catchRate = 60,
            .expYield = 318,
            .evYield_Speed = 2,
            .genderRatio = PERCENT_FEMALE(50),
            .eggCycles = 20,
            .friendship = STANDARD_FRIENDSHIP,
            .growthRate = GROWTH_SLOW,
            .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_DRAGON),
            .abilities = { ABILITY_LIGHTWING, ABILITY_NONE, ABILITY_LIGHTWING },
            .bodyColor = BODY_COLOR_WHITE,
            .speciesName = _("Dracoceros"),
            .cryId = CRY_MILOTIC,
            .natDexNum = NATIONAL_DEX_DRACOCEROS_JUVENILE,
            .categoryName = _("Dragon Hero"),
            .height = 62,
            .weight = 1620,
            .description = COMPOUND_STRING(
                "The young are playful, naive, and\n"
                "innocent. They are quick to trust\n"
                "strangers and will frolick around\n"
                "them as a sign of friendship."),
            .pokemonScale = 356,
            .pokemonOffset = 17,
            .trainerScale = 256,
            .trainerOffset = 0,
            .frontPic = gMonFrontPic_DracocerosHolyChild,
            .frontPicFemale = gMonFrontPic_DracocerosHolyChildF,
            .frontPicSize = MON_COORDS_SIZE(64, 64),
            .frontPicSizeFemale = MON_COORDS_SIZE(64, 64),
            .frontPicYOffset = 2,
            .frontAnimFrames = sAnims_DracocerosHolyChild,
            .frontAnimId = ANIM_CIRCULAR_STRETCH_TWICE,
            .frontAnimDelay = 45,
            .backPic = gMonBackPic_DracocerosHolyChild,
            .backPicFemale = gMonBackPic_DracocerosHolyChildF,
            .backPicSize = MON_COORDS_SIZE(64, 64),
            .backPicSizeFemale = MON_COORDS_SIZE(64, 64),
            .backPicYOffset = 0,
            .backAnimId = BACK_ANIM_CONVEX_DOUBLE_ARC,
            .palette = gMonPalette_DracocerosHolyChild,
            .shinyPalette = gMonShinyPalette_DracocerosHolyChild,
            .iconSprite = gMonIcon_DracocerosHolyChild,
            .iconPalIndex = 2,
            FOOTPRINT(DracocerosHolyChild)
            OVERWORLD(
                sPicTable_DracocerosHolyChild,
                SIZE_32x32,
                SHADOW_SIZE_M,
                TRACKS_FOOT,
                gOverworldPalette_DracocerosHolyChild,
                gShinyOverworldPalette_DracocerosHolyChild
            )
            .levelUpLearnset = sDracocerosHolyChildLevelUpLearnset,
            .teachableLearnset = sDracocerosHolyChildTeachableLearnset,
            .eggMoveLearnset = sDracocerosHolyChildEggMoveLearnset,
            .evolutions = EVOLUTION({EVO_LEVEL, 25, SPECIES_DRACOCEROS_HOLY_JUVENILE}),
    },
},