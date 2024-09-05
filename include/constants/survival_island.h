#ifndef GUARD_CONSTANTS_SURVIVAL_ISLAND_H
#define GUARD_CONSTANTS_SURVIVAL_ISLAND_H

#include "constants/pokemon.h"

#define ISLAND_CHALLENGE(facility, mode) ((facility << 8) + mode)

// Battle ISLAND facility ids.
#define ISLAND_GAME_FACILITY_SURVIVAL 0
#define NUM_ISLAND_GAME_FACILITIES    1
// VAR_ISLAND_GAME_FACILITY is re-used for the below facilities as well
/*
#define GAME_FACILITY_LINK_CONTEST      7
#define GAME_FACILITY_UNION_ROOM        8
#define GAME_FACILITY_MULTI_OR_EREADER  9  // Direct Corner multi battles, multi battle with Steven, and e-Reader battles
*/

// Battle ISLAND battle modes.
#define ISLAND_MODE_SINGLES      0
#define ISLAND_MODE_DOUBLES      1
#define ISLAND_MODE_MULTIS       2
#define ISLAND_MODE_TRIPLES      3 //Unimplemented as of yet.
#define ISLAND_MODE_COUNT        4

// Challenge Statuses
#define CHALLENGE_STATUS_SAVING   1
#define CHALLENGE_STATUS_PAUSED   2
#define CHALLENGE_STATUS_WON      3
#define CHALLENGE_STATUS_LOST     4

// Special trainer battles.
#define SPECIAL_BATTLE_CHALLENGE 0

#define MAX_BATTLE_ISLAND_POINTS 9999
#define MAX_STREAK 9999

#define ISLAND_MIN_LEVEL 5
#define ISLAND_MAX_LEVEL_OPEN MAX_LEVEL

// This is the default number of battles (or floors, in Challenge Mode) per challenge.
#define ISLAND_STAGES_PER_CHALLENGE 5

// These sets of facility ids would be redundant if the order was consistent
// The order is important for this set so that all the non-link records can be continuous.
/*
#define RANKING_HALL_CHALLENGE 0

#define ISLAND_MANIAC_CHALLENGE 0

#define ISLAND_MANIAC_MESSAGE_COUNT 3

// ISLAND TV Show
#define ISLAND_SHOW_CHALLENGE 0

// ISLAND Gambler
#define ISLAND_GAMBLER_WAITING     0
#define ISLAND_GAMBLER_PLACED_BET  1
#define ISLAND_GAMBLER_WON         2
#define ISLAND_GAMBLER_LOST        3

#define ISLAND_GAMBLER_BET_5      0
#define ISLAND_GAMBLER_BET_10     1
#define ISLAND_GAMBLER_BET_15     2
#define ISLAND_GAMBLER_BET_CANCEL 3

#define ISLAND_GAMBLER_CHALLENGE_COUNT 12
*/
/*
#define EXCHANGE_CORNER_DECOR1_CLERK     0
#define EXCHANGE_CORNER_DECOR2_CLERK     1
#define EXCHANGE_CORNER_VITAMIN_CLERK    2
#define EXCHANGE_CORNER_HOLD_ITEM_CLERK  3
*/
// unused
/*
#define F_EV_SPREAD_HP         (1 << 0)
#define F_EV_SPREAD_ATTACK     (1 << 1)
#define F_EV_SPREAD_DEFENSE    (1 << 2)
#define F_EV_SPREAD_SPEED      (1 << 3)
#define F_EV_SPREAD_SP_ATTACK  (1 << 4)
#define F_EV_SPREAD_SP_DEFENSE (1 << 5)
*/

// CreateFacilityMonFlags
//#define FLAG_ISLAND_MON_FACTORY       (1 << 0)

#endif // GUARD_CONSTANTS_BATTLE_ISLAND_H
