const struct TrainerMon gSurvivalIslandMons[NUM_FRONTIER_MONS] =
{
    [ISLAND_MON_BULBASAUR] = {
        .species = SPECIES_BULBASAUR,
        .moves = {MOVE_GROWL, MOVE_TACKLE, MOVE_VINE_WHIP, MOVE_INGRAIN},
        .heldItem = ITEM_NONE,
        .ev = TRAINER_PARTY_EVS(6, 189, 189, 0, 63, 63),
        .nature = NATURE_DOCILE
    },
    [ISLAND_MON_CHARMANDER] = {
        .species = SPECIES_CHARMANDER,
        .moves = {MOVE_GROWL, MOVE_SCRATCH, MOVE_EMBER, MOVE_COUNTER},
        .heldItem = ITEM_NONE,
        .ev = TRAINER_PARTY_EVS(0, 252, 6, 0, 252, 0),
        .nature = NATURE_NAUGHTY
    },
    [ISLAND_MON_SQUIRTLE] = {
        .species = SPECIES_SQUIRTLE,
        .moves = {MOVE_TACKLE, MOVE_TAIL_WHIP, MOVE_WATER_GUN, MOVE_MIRROR_COAT},
        .heldItem = ITEM_NONE,
        .ev = TRAINER_PARTY_EVS(0, 6, 252, 0, 0, 252),
        .nature = NATURE_IMPISH
    },
    [ISLAND_MON_CHIKORITA] = {
        .species = SPECIES_CHIKORITA,
        .moves = {MOVE_RAZOR_LEAF, MOVE_ANCIENT_POWER, MOVE_INGRAIN, MOVE_HEAL_PULSE},
        .heldItem = ITEM_NONE,
        .ev = TRAINER_PARTY_EVS(6, 0, 252, 0, 0, 252),
        .nature = NATURE_CALM
    },
    [ISLAND_MON_CYNDAQUIL] = {
        .species = SPECIES_CYNDAQUIL,
        .moves = {MOVE_EMBER, MOVE_ANCIENT_POWER, MOVE_REVERSAL, MOVE_EXTRASENSORY},
        .heldItem = ITEM_NONE,
        .ev = TRAINER_PARTY_EVS(0, 252, 0, 0, 252, 6),
        .nature = NATURE_MILD
    },
    [ISLAND_MON_TOTODILE] = {
        .species = SPECIES_TOTODILE,
        .moves = {MOVE_WATER_GUN, MOVE_ANCIENT_POWER, MOVE_COUNTER, MOVE_FLATTER},
        .heldItem = ITEM_NONE,
        .ev = TRAINER_PARTY_EVS(6, 64, 64, 0, 189, 189),
        .nature = NATURE_HARDY
    },
    [ISLAND_MON_TREECKO] = {
        .species = SPECIES_TREECKO,
        .moves = {MOVE_POUND, , MOVE_LEAFAGE, MOVE_DRAGON_BREATH, MOVE_SLASH},
        .heldItem = ITEM_NONE,
        .ev = TRAINER_PARTY_EVS(2, 189, 2, 126, 189, 2),
        .nature = NATURE_QUIRKY
    },
    [ISLAND_MON_TORCHIC] = {
        .species = SPECIES_TORCHIC,
        .moves = {MOVE_SCRATCH, MOVE_EMBER, MOVE_COUNTER, MOVE_NIGHT_SLASH},
        .heldItem = ITEM_NONE,
        .ev = TRAINER_PARTY_EVS(0, 252, 0, 0, 252, 6),
        .nature = NATURE_LONELY
    },
    [ISLAND_MON_MUDKIP] = {
        .species = SPECIES_MUDKIP,
        .moves = {MOVE_TACKLE, MOVE_WATER_GUN, MOVE_MIRROR_COAT, MOVE_SLUDGE},
        .heldItem = ITEM_NONE,
        .ev = TRAINER_PARTY_EVS(6, 0, 252, 0, 6, 252),
        .nature = NATURE_BOLD
    },
    [ISLAND_MON_TURTWIG] = {
        .species = SPECIES_TURTWIG,
        .moves = {MOVE_POUND, MOVE_LEAFAGE, MOVE_GROWTH, MOVE_WIDE_GUARD},
        .heldItem = ITEM_NONE,
        .ev = TRAINER_PARTY_EVS(6, 0, 252, 0, 0, 252),
        .nature = NATURE_DOCILE
    },
    [ISLAND_MON_CHIMCHAR] = {
        .species = SPECIES_CHIMCHAR,
        .moves = {MOVE_SCRATCH, MOVE_EMBER, MOVE_ENCORE, MOVE_FOCUS_ENERGY},
        .heldItem = ITEM_NONE,
        .ev = TRAINER_PARTY_EVS(0, 252, 0, 6, 252, 0),
        .nature = NATURE_SERIOUS
    },
    [ISLAND_MON_PINLUP] = {
        .species = SPECIES_PINLUP,
        .moves = {MOVE_POUND, MOVE_WATER_GUN, MOVE_ROOST, MOVE_AQUA_RING},
        .heldItem = ITEM_NONE,
        .ev = TRAINER_PARTY_EVS(3, 126, 126, 3, 126, 126),
        .nature = NATURE_HARDY
    },
    [ISLAND_MON_SNIVY] = {
        .species = SPECIES_SNIVY,
        .moves = {MOVE_VINE_WHIP, MOVE_IRON_TAIL, MOVE_TWISTER, MOVE_SYNTHESIS},
        .heldItem = ITEM_NONE,
        .ev = TRAINER_PARTY_EVS(6, 0, 252, 0, 0, 252),
        .nature = NATURE_SERIOUS
    },
    [ISLAND_MON_TEPIG] = {
        .species = SPECIES_TEPIG,
        .moves = {MOVE_EMBER, MOVE_SUPERPOWER, MOVE_THRASH, MOVE_SUCKER_PUNCH},
        .heldItem = ITEM_NONE,
        .ev = TRAINER_PARTY_EVS(0, 252, 0, 6, 252, 0),
        .nature = NATURE_HARDY
    },
    [ISLAND_MON_OSHAWOTT] = {
        .species = SPECIES_OSHAWOTT,
        .moves = {MOVE_WATER_GUN, MOVE_AIR_SLASH, NIGHT_SLASH, MOVE_SACRED_SWORD},
        .heldItem = ITEM_NONE,
        .ev = TRAINER_PARTY_EVS(6, 252, 252, 0, 0, 0),
        .nature = NATURE_SERIOUS
    },
    [ISLAND_MON_CHESPIN] = {
        .species = SPECIES_CHESPIN,
        .moves = {MOVE_TACKLE, MOVE_VINE_WHIP, MOVE_SYNTHESIS, MOVE_QUICK_GUARD},
        .heldItem = ITEM_NONE,
        .ev = TRAINER_PARTY_EVS(6, 0, 252, 0, 0, 252),
        .nature = NATURE_IMPISH
    },
    [ISLAND_MON_FENNEKIN] = {
        .species = SPECIES_FENNEKIN,
        .moves = {MOVE_SCRATCH, MOVE_EMBER, MOVE_WISH, MOVE_HYPNOSIS},
        .heldItem = ITEM_NONE,
        .ev = TRAINER_PARTY_EVS(0, 252, 0, 6, 252, 0),
        .nature = NATURE_MILD
    },
    [ISLAND_MON_FROAKIE] = {
        .species = SPECIES_FROAKIE,
        .moves = {MOVE_POUND, MOVE_WATER_GUN, MOVE_SPIKES, MOVE_TOXIC_SPIKES},
        .heldItem = ITEM_NONE,
        .ev = TRAINER_PARTY_EVS(0, 3, 3, 168, 168, 168),
        .nature = NATURE_SERIOUS
    },
    [ISLAND_MON_ROWLET] = {
        .species = SPECIES_ROWLET,
        .moves = {MOVE_TACKLE, MOVE_LEAFAGE, MOVE_ROOST, MOVE_DOUBLE_TEAM},
        .heldItem = ITEM_NONE,
        .ev = TRAINER_PARTY_EVS(3, 252, 0, 3, 252, 0),
        .nature = NATURE_QUIRKY
    },
    [ISLAND_MON_LITTLEN] = {
        .species = SPECIES_LITTEN,
        .moves = {MOVE_SCRATCH, MOVE_EMBER, MOVE_POWER_TRIP, MOVE_PARTING_SHOT},
        .heldItem = ITEM_NONE,
        .ev = TRAINER_PARTY_EVS(0, 252, 0, 6, 252, 0),
        .nature = NATURE_NAUGHTY
    },
    [ISLAND_MON_POPPLIO] = {
        .species = SPECIES_POPPLIO,
        .moves = {MOVE_POUND, MOVE_WATER_GUN, MOVE_LIFE_DEW, MOVE_AQUA_RING},
        .heldItem = ITEM_NONE,
        .ev = TRAINER_PARTY_EVS(6, 0, 252, 0, 0, 252),
        .nature = NATURE_CALM
    },
};
