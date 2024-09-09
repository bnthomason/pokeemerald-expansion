#include "global.h"
#include "battle.h"
#include "battle_factory.h"
#include "battle_factory_screen.h"
#include "event_data.h"
#include "battle_setup.h"
#include "overworld.h"
#include "frontier_util.h"
#include "battle_tower.h"
#include "random.h"
#include "constants/battle_ai.h"
#include "constants/battle_factory.h"
#include "constants/battle_frontier.h"
#include "constants/battle_frontier_mons.h"
#include "constants/battle_tent.h"
#include "constants/frontier_util.h"
#include "constants/layouts.h"
#include "constants/trainers.h"
#include "constants/moves.h"
#include "constants/items.h"


static const u8 sFixedIVTable2[] =
{
    8,
    15,
    24,
    31,
};


u8 GetSurvivalIslandMonFixedIV(void)
{

    /*
    u8 ivSet;
    bool8 useHigherIV = isLastBattle ? TRUE : FALSE;
    */

   u8 difficulty = DIFFICULTY;

// The Factory has an out-of-bounds access when generating the rental draft for round 9 (challengeNum==8),
// or the "elevated" rentals from round 8 (challengeNum+1==8)
// This happens to land on a number higher than 31, which is interpreted as "random IVs"
/*#ifdef BUGFIX
    if (challengeNum >= ARRAY_COUNT(sFixedIVTable))
#else
    if (challengeNum > ARRAY_COUNT(sFixedIVTable))
#endif
        ivSet = ARRAY_COUNT(sFixedIVTable) - 1;
    else
        ivSet = challengeNum;*/
    
    if (difficulty == DIFFICULTY_EASY)
        return sFixedIVTable2[0];
    else if (difficulty == DIFFICULTY_NORMAL)
        return sFixedIVTable2[1];
    if (difficulty == DIFFICULTY_HARD)
        return sFixedIVTable2[2];
    else
        return sFixedIVTable2[3];
}

/*
static void GenerateStarterMons(void)
{
    s32 i, j;
    u8 firstMonId;
    u16 monSetId;
    u16 currSpecies;
    u16 species[PARTY_SIZE];
    u16 monIds[PARTY_SIZE];
    u16 heldItems[PARTY_SIZE];

    firstMonId = 0;
    gFacilityTrainers = gSlateportBattleTentTrainers;
    for (i = 0; i < PARTY_SIZE; i++)
    {
        species[i] = 0;
        monIds[i] = 0;
        heldItems[i] = 0;
    }
    gFacilityTrainerMons = gSlateportBattleTentMons;
    currSpecies = SPECIES_NONE;
    i = 0;
    while (i != PARTY_SIZE)
    {
        // Cannot have two Pokémon of the same species.
        monSetId = Random() % NUM_SLATEPORT_TENT_MONS;
        for (j = firstMonId; j < firstMonId + i; j++)
        {
            if (monIds[j] == monSetId)
                break;
            if (species[j] == gFacilityTrainerMons[monSetId].species)
            {
                if (currSpecies == SPECIES_NONE)
                    currSpecies = gFacilityTrainerMons[monSetId].species;
                else
                    break;
            }
        }
        if (j != i + firstMonId)
            continue;

        // Cannot have two same held items.
        for (j = firstMonId; j < i + firstMonId; j++)
        {
            if (heldItems[j] != 0 && heldItems[j] == gFacilityTrainerMons[monSetId].heldItem)
            {
                if (gFacilityTrainerMons[monSetId].species == currSpecies)
                    currSpecies = SPECIES_NONE;
                break;
            }
        }
        if (j != i + firstMonId)
            continue;

        gSaveBlock2Ptr->frontier.rentalMons[i].monId = monSetId;
        species[i] = gFacilityTrainerMons[monSetId].species;
        heldItems[i] = gFacilityTrainerMons[monSetId].heldItem;
        monIds[i] = monSetId;
        i++;
    }
}
*/