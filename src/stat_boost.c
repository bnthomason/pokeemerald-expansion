#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_controllers.h"
#include "battle_interface.h"
#include "battle_scripts.h"
#include "battle_script_commands.h"
#include "battle_gimmick.h"
#include "data.h"
#include "event_data.h"
#include "graphics.h"
#include "item.h"
#include "pokemon.h"
#include "random.h"
#include "sprite.h"
#include "string_util.h"
#include "util.h"
#include "constants/abilities.h"
#include "constants/battle_move_effects.h"
#include "constants/battle_string_ids.h"
#include "constants/flags.h"
#include "constants/hold_effects.h"
#include "constants/items.h"
#include "constants/moves.h"

// Applies the HP Multiplier for Dynamaxed Pokemon and Raid Bosses.
void ApplyStatMultiplier(u32 battler, struct Pokemon* mon)
{
    if (gBattleMons[battler].ability == ABILITY_LIGHTWING)
        {
            u32 speed = (GetMonData(mon, MON_DATA_SPEED) * 2);
            SetMonData(mon, MON_DATA_SPEED, &speed);
            gBattleMons[battler].isStatBoosted = TRUE;
        }
    if (gBattleMons[battler].ability == ABILITY_LONGEVITY)
    {
        if (GetMonData(mon, MON_DATA_SPECIES) == SPECIES_SHEDINJA)
            return;
        else
        {
            u32 hp = (GetMonData(mon, MON_DATA_HP) * 2);
            u32 maxHP = (GetMonData(mon, MON_DATA_MAX_HP) * 2);
            SetMonData(mon, MON_DATA_HP, &hp);
            SetMonData(mon, MON_DATA_MAX_HP, &maxHP);
            gBattleMons[battler].isStatBoosted = TRUE;
        }
    }
}



// Updates stats like HP multipliers and healthboxes.
void BS_UpdateStats(void)
{
    NATIVE_ARGS();
    u32 battler = gBattleScripting.battler;
    struct Pokemon *mon = &GetSideParty(GetBattlerSide(battler))[gBattlerPartyIndexes[battler]];

//    if (!IsStatBuffed(battler)) // RecalcBattlerStats wil get called immediately.
    RecalcBattlerStats(battler, mon);

    UpdateHealthboxAttribute(gHealthboxSpriteIds[battler], mon, HEALTHBOX_ALL);
    gBattlescriptCurrInstr = cmd->nextInstr;
}

// Returns whether a battler is transformed into a Gigantamax form.
bool32 IsStatBoosted(u32 battler)
{
//    struct Pokemon *mon = &GetSideParty(GetBattlerSide(battler))[gBattlerPartyIndexes[battler]];

    if ((gBattleMons[battler].isStatBoosted))
        return TRUE;
    return FALSE;
}

// Unsets the flags used for Special Abilities and reverts stats.
void UndoStatBoost(u32 battler)
{
    u8 side = GetBattlerSide(battler);
    u8 monId = gBattlerPartyIndexes[battler];

    // Revert stats
    if (IsStatBoosted(battler))
    {
        struct Pokemon *mon = (side == B_SIDE_PLAYER) ? &gPlayerParty[monId] : &gEnemyParty[monId];
        u16 mult = UQ_4_12(1.0/2.0); // placeholder
            if (GetMonAbility(mon) == ABILITY_LIGHTWING)
                {
                    gBattleMons[battler].speed = UQ_4_12_TO_INT((GetMonData(mon, MON_DATA_SPEED) * mult + 1) + UQ_4_12_ROUND); // round up
                    SetMonData(mon, MON_DATA_HP, &gBattleMons[battler].speed);
                    CalculateMonStats(mon);
                }
            if (GetMonAbility(mon) == ABILITY_LONGEVITY)
                {
                    gBattleMons[battler].hp = UQ_4_12_TO_INT((GetMonData(mon, MON_DATA_HP) * mult + 1) + UQ_4_12_ROUND); // round up
                    SetMonData(mon, MON_DATA_HP, &gBattleMons[battler].hp);
                    CalculateMonStats(mon);
                }
    }
    gBattleMons[battler].isStatBoosted = FALSE;
}