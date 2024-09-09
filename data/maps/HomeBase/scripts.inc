.set LOCALID_GUARD_1, 2
.set LOCALID_GUARD_2, 3

HomeBase_MapScripts::
	.byte 0

SurvivalIsland_HomeBase_Pokebag::
	lock
	faceplayer
	setflag FLAG_SYS_PICKED_SIX_POKEMON
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_ZIGZAGOON
	setobjectxy OBJ_EVENT_ID_PLAYER, 6, 13
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	special ChooseStarter
	waitstate
	applymovement LOCALID_BIRCH, Route101_Movement_BirchApproachPlayer
	waitmovement 0
	msgbox Route101_Text_YouSavedMe, MSGBOX_DEFAULT
	special HealPlayerParty
	setflag FLAG_HIDE_ROUTE_101_BIRCH_ZIGZAGOON_BATTLE
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	setflag FLAG_HIDE_ROUTE_101_BIRCH_STARTERS_BAG
	setvar VAR_BIRCH_LAB_STATE, 2
	setvar VAR_ROUTE101_STATE, 3
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	checkplayergender
	call_if_eq VAR_RESULT, MALE, Route101_EventScript_HideMayInBedroom
	call_if_eq VAR_RESULT, FEMALE, Route101_EventScript_HideBrendanInBedroom
	warp MAP_LITTLEROOT_TOWN_PROFESSOR_BIRCHS_LAB, 6, 5
	waitstate
	release
	end

SurvivalIsland_HomeBase_ItemBall::

SurvivalIsland_HomeBase_Sailor::

SurvivalIsland_HomeBase_ForestGuard::
	lockall
	goto_if_set FLAG_STARTED_CHALLENGE, EverGrandeCity_PokemonLeague_1F_EventScript_GoForth
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_ge VAR_TEMP_0, 11, SurvivalIsland_HomeBase_ForestGuard_EventScript_PlayerMoveToFrontFromRight
	call_if_le VAR_TEMP_0, 8, SurvivalIsland_HomeBase_ForestGuard_EventScript_PlayerMoveToFrontFromLeft
	message SurvivalIsland_HomeBase_Text_MustHaveSixStarterPokemon
	waitmessage
	delay 120
	goto_if_unset FLAG_PICKED_SIX_POKEMON, SurvivalIsland_HomeBase_Text_DontHaveSixPokemon
	closemessage
	applymovement LOCALID_GUARD_1, SurvivalIsland_HomeBase_Movement_LeftGuardOutOfWay
	applymovement LOCALID_GUARD_2, SurvivalIsland_HomeBase_Movement_RightGuardOutOfWay
	waitmovement 0
	delay 10
	playfanfare MUS_OBTAIN_BADGE
	message SurvivalIsland_HomeBase_Text_GoForth
	waitmessage
	waitfanfare
	closemessage
	copyobjectxytoperm LOCALID_GUARD_1
	copyobjectxytoperm LOCALID_GUARD_2
	setflag FLAG_STARTED_CHALLENGE
	releaseall
	end

SurvivalIsland_HomeBase_Movement_LeftGuardOutOfWay::
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromRight
	waitmovement 0
	return

SurvivalIsland_HomeBase_Movement_RightGuardOutOfWay::
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromLeft
	waitmovement 0
	return

EverGrandeCity_PokemonLeague_1F_EventScript_NotAllBadges::
	playse SE_FAILURE
	msgbox EverGrandeCity_PokemonLeague_1F_Text_HaventObtainedAllBadges, MSGBOX_DEFAULT
	releaseall
	end

EverGrandeCity_PokemonLeague_1F_EventScript_GoForth::
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox EverGrandeCity_PokemonLeague_1F_Text_GoForth, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromRight:
	walk_down
	walk_left
	walk_in_place_faster_up
	step_end

EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromLeft:
	walk_down
	walk_right
	walk_in_place_faster_up
	step_end

EverGrandeCity_PokemonLeague_1F_Movement_LeftGuardOutOfWay:
	walk_left
	walk_in_place_faster_down
	step_end

EverGrandeCity_PokemonLeague_1F_Movement_RightGuardOutOfWay:
	walk_right
	walk_in_place_faster_down
	step_end

SurvivalIsland_HomeBase_Text_MustHaveSixStarterPokemon:
	.string "Beyond this point lies dangerous POKéMON\n"
	.string "and tough trainers in thier wake.\p"
	.string "It is required to have six POKéMON\n"
	.string "and a POKéDEX with you. Let us check\l"
	.string "to see if you have them.$"

SurvivalIsland_HomeBase_Text_DontHaveSixPokemon:
	.string "You haven't obtained six POKéMON.\p"
	.string "Look for the bag on this island to\n"
	.string "be able to proceed.$"

SurvivalIsland_HomeBase_Text_GoForth:
	.string "TRAINER! Believe in yourself and your\n"
	.string "POKéMON, and go forth!$"

