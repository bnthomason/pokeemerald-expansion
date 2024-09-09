.set LOCALID_GUARD_1, 2
.set LOCALID_GUARD_2, 3

HomeBase_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SurvivalIsland_HomeBase_OnTransition
	.byte 0

SurvivalIsland_HomeBase_OnTransition:
	setrespawn HEAL_LOCATION_SURVIVAL_ISLAND_HOMEBASE
	call_if_unset FLAG_FIRST_VISIT, SurvivalIsland_HomeBase_SailorFirstVisit
	call_if_set FLAG_FIRST_VISIT, SurvivalIsland_HomeBase_SailorHide
	call_if_unset FLAG_STARTED_CHALLENGE, SurvivalIsland_HomeBase_EventScript_GuardsBlockDoor
	end

SurvivalIsland_HomeBase_SailorHide::
	setflag FLAG_HIDE_SURVIVALISLAND_SAILOR
	setflag FLAG_HIDE_SURVIVALISLAND_BOAT
	return

SurvivalIsland_HomeBase_EventScript_GuardsBlockDoor::
	setobjectxyperm LOCALID_GUARD_1, 17, 14
	setobjectxyperm LOCALID_GUARD_2, 18, 14
	return

SurvivalIsland_HomeBase_Pokebag::
	lock
	faceplayer
	setflag FLAG_PICKED_STARTER_POKEMON
	fadescreen FADE_TO_BLACK
	special ChooseStarters
	waitstate
	special HealPlayerParty
	setflag FLAG_HIDE_HOMEBASE_STARTERS_BAG
	waitstate
	release
	end

SurvivalIsland_HomeBase_ItemBall::
	setflag FLAG_SYS_POKEDEX_GET
	special SetUnlockedPokedexFlags
	end

SurvivalIsland_HomeBase_SailorFirstVisit::
	msgbox SurvivalIsland_HomeBase_Text_Sailor1 MSGBOX_DEFAULT
	return

SurvivalIsland_HomeBase_SailorAdvice::
	msgbox SurvivalIsland_HomeBase_Text_SailorHint MSGBOX_DEFAULT
	end


SurvivalIsland_HomeBase_ForestGuard::
	lockall
	goto_if_set FLAG_STARTED_CHALLENGE, SurvivalIsland_HomeBase_EventScript_GoForth
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_ge VAR_TEMP_0, 19, SurvivalIsland_HomeBase_ForestGuard_EventScript_PlayerMoveToFrontFromRight
	call_if_le VAR_TEMP_0, 16, SurvivalIsland_HomeBase_ForestGuard_EventScript_PlayerMoveToFrontFromLeft
	message SurvivalIsland_HomeBase_Text_MustHaveSixStarterPokemon
	waitmessage
	delay 120
	goto_if_unset FLAG_PICKED_STARTER_POKEMON, SurvivalIsland_HomeBase_EventScript_DontHaveSixPokemon
	closemessage
	applymovement LOCALID_GUARD_1, SurvivalIsland_HomeBase_Movement_LeftGuardOutOfWay
	applymovement LOCALID_GUARD_2, SurvivalIsland_HomeBase_Movement_RightGuardOutOfWay
	waitmovement 0
	delay 10
	message SurvivalIsland_HomeBase_Text_GoForth
	waitmessage
	closemessage
	copyobjectxytoperm LOCALID_GUARD_1
	copyobjectxytoperm LOCALID_GUARD_2
	setflag FLAG_STARTED_CHALLENGE
	releaseall
	end

SurvivalIsland_HomeBase_ForestGuard_EventScript_PlayerMoveToFrontFromRight::
	applymovement OBJ_EVENT_ID_PLAYER, SurvivalIsland_HomeBase_Movement_MoveToFrontFromRight
	waitmovement 0
	return

SurvivalIsland_HomeBase_ForestGuard_EventScript_PlayerMoveToFrontFromLeft::
	applymovement OBJ_EVENT_ID_PLAYER, SurvivalIsland_HomeBase_Movement_MoveToFrontFromLeft
	waitmovement 0
	return

SurvivalIsland_HomeBase_EventScript_DontHaveSixPokemon::
	playse SE_FAILURE
	msgbox SurvivalIsland_HomeBase_Text_DontHaveSixPokemon, MSGBOX_DEFAULT
	releaseall
	end

SurvivalIsland_HomeBase_EventScript_GoForth::
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox EverGrandeCity_PokemonLeague_1F_Text_GoForth, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

SurvivalIsland_HomeBase_Movement_MoveToFrontFromRight:
	walk_down
	walk_left
	walk_in_place_faster_up
	step_end

SurvivalIsland_HomeBase_Movement_MoveToFrontFromLeft:
	walk_down
	walk_right
	walk_in_place_faster_up
	step_end

SurvivalIsland_HomeBase_Movement_LeftGuardOutOfWay:
	walk_left
	walk_in_place_faster_down
	step_end

SurvivalIsland_HomeBase_Movement_RightGuardOutOfWay:
	walk_right
	walk_in_place_faster_down
	step_end

SurvivalIsland_HomeBase_Text_Sailor1:
	.string "Ahoy, matey! We have landed!\p"
	.string "I assume you're off to take the\n"
	.string "challenge now?$"

SurvivalIsland_HomeBase_Text_SailorHint:
	.string "Weren't you going to take the\n"
	.string "challenge? I assume you've already\l"
	.string "picked your six starting POKéMON.\p"
	.string "If not, look for the bag, should be\n"
	.string "over there.$"

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
