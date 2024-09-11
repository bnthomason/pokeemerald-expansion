.set LOCALID_GUARD_1, 2
.set LOCALID_GUARD_2, 3
.set LOCALID_ITEMBALL, 4
.set LOCALID_POKEBAG_1, 6
.set LOCALID_POKEBAG_2, 7
.set LOCALID_POKEBAG_3, 8
.set LOCALID_POKEBAG_4, 9
.set LOCALID_POKEBAG_5, 10
.set LOCALID_POKEBAG_6, 11
.set LOCALID_POKEBAG_7, 12
.set LOCALID_POKEBAG_8, 13
.set LOCALID_POKEBAG_9, 14

HomeBase_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SurvivalIsland_HomeBase_OnTransition
	.byte 0

SurvivalIsland_HomeBase_OnTransition:
	setrespawn HEAL_LOCATION_SURVIVAL_ISLAND_HOMEBASE
@	call_if_unset FLAG_FIRST_VISIT, SurvivalIsland_HomeBase_SailorFirstVisit
@	call_if_set FLAG_FIRST_VISIT, SurvivalIsland_HomeBase_SailorHide
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

SurvivalIsland_HomeBase_Pokebag_1::
	lock
	faceplayer
	setflag FLAG_SYS_POKEMON_GET
	fadescreen FADE_TO_BLACK
	setvar VAR_BAG_SELECTED, 1
	special ChooseStarter
	waitstate
	special HealPlayerParty
	setflag FLAG_HIDE_HOMEBASE_STARTERS_BAG_1
	removeobject LOCALID_POKEBAG_1
	addobject LOCALID_POKEBAG_2
	clearflag FLAG_HIDE_HOMEBASE_STARTERS_BAG_2
	release
	end

SurvivalIsland_HomeBase_Pokebag_2::
	lock
	faceplayer
	fadescreen FADE_TO_BLACK
	setvar VAR_BAG_SELECTED, 2
	special ChooseStarter
	waitstate
	special HealPlayerParty
	setflag FLAG_HIDE_HOMEBASE_STARTERS_BAG_2
	removeobject LOCALID_POKEBAG_2
	addobject LOCALID_POKEBAG_3
	clearflag FLAG_HIDE_HOMEBASE_STARTERS_BAG_3
	release
	end

SurvivalIsland_HomeBase_Pokebag_3::
	lock
	faceplayer
	fadescreen FADE_TO_BLACK
	setvar VAR_BAG_SELECTED, 3
	special ChooseStarter
	waitstate
	special HealPlayerParty
	setflag FLAG_HIDE_HOMEBASE_STARTERS_BAG_3
	removeobject LOCALID_POKEBAG_3
	addobject LOCALID_POKEBAG_4
	clearflag FLAG_HIDE_HOMEBASE_STARTERS_BAG_4
	release
	end

SurvivalIsland_HomeBase_Pokebag_4::
	lock
	faceplayer
	fadescreen FADE_TO_BLACK
	setvar VAR_BAG_SELECTED, 4
	special ChooseStarter
	waitstate
	special HealPlayerParty
	setflag FLAG_HIDE_HOMEBASE_STARTERS_BAG_4
	removeobject LOCALID_POKEBAG_4
	addobject LOCALID_POKEBAG_5
	addobject LOCALID_POKEBAG_6
	clearflag FLAG_HIDE_HOMEBASE_STARTERS_BAG_5
	clearflag FLAG_HIDE_HOMEBASE_STARTERS_BAG_6
	release
	end

SurvivalIsland_HomeBase_End:
	closemessage
	releaseall
	end

SurvivalIsland_HomeBase_Pokebag_5::
	lock
	faceplayer
	msgbox SurvivalIsland_HomeBase_Text_Pokebag_5, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, SurvivalIsland_HomeBase_End
	case YES, SurvivalIsland_HomeBase_Pokebag_5_Warning
	case MULTI_B_PRESSED, SurvivalIsland_HomeBase_End

SurvivalIsland_HomeBase_Pokebag_5_Warning:
	msgbox SurvivalIsland_HomeBase_Text_Bag_Proceed_Warning, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, SurvivalIsland_HomeBase_End
	case YES, SurvivalIsland_HomeBase_Pokebag_5_Continue
	case MULTI_B_PRESSED, SurvivalIsland_HomeBase_End	

SurvivalIsland_HomeBase_Pokebag_5_Continue::
	fadescreen FADE_TO_BLACK
	setvar VAR_BAG_SELECTED, 5
	special ChooseStarter
	waitstate
	special HealPlayerParty
	setflag FLAG_HIDE_HOMEBASE_STARTERS_BAG_5
	setflag FLAG_HIDE_HOMEBASE_STARTERS_BAG_6
	removeobject LOCALID_POKEBAG_5
	removeobject LOCALID_POKEBAG_6
	addobject LOCALID_POKEBAG_7
	addobject LOCALID_POKEBAG_8
	addobject LOCALID_POKEBAG_9
	clearflag FLAG_HIDE_HOMEBASE_STARTERS_BAG_7
	clearflag FLAG_HIDE_HOMEBASE_STARTERS_BAG_8
	clearflag FLAG_HIDE_HOMEBASE_STARTERS_BAG_9
	release
	end


SurvivalIsland_HomeBase_Pokebag_6::
	lock
	faceplayer
	msgbox SurvivalIsland_HomeBase_Text_Pokebag_6, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, SurvivalIsland_HomeBase_End
	case YES, SurvivalIsland_HomeBase_Pokebag_6_Warning
	case MULTI_B_PRESSED, SurvivalIsland_HomeBase_End

SurvivalIsland_HomeBase_Pokebag_6_Warning:
	msgbox SurvivalIsland_HomeBase_Text_Bag_Proceed_Warning, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, SurvivalIsland_HomeBase_End
	case YES, SurvivalIsland_HomeBase_Pokebag_6_Continue
	case MULTI_B_PRESSED, SurvivalIsland_HomeBase_End	


SurvivalIsland_HomeBase_Pokebag_6_Continue::
	fadescreen FADE_TO_BLACK
	setvar VAR_BAG_SELECTED, 6
	special ChooseStarter
	waitstate
	special HealPlayerParty
	setflag FLAG_HIDE_HOMEBASE_STARTERS_BAG_5
	setflag FLAG_HIDE_HOMEBASE_STARTERS_BAG_6
	removeobject LOCALID_POKEBAG_5
	removeobject LOCALID_POKEBAG_6
	addobject LOCALID_POKEBAG_7
	addobject LOCALID_POKEBAG_8
	addobject LOCALID_POKEBAG_9
	clearflag FLAG_HIDE_HOMEBASE_STARTERS_BAG_7
	clearflag FLAG_HIDE_HOMEBASE_STARTERS_BAG_8
	clearflag FLAG_HIDE_HOMEBASE_STARTERS_BAG_9
	release
	end

SurvivalIsland_HomeBase_Pokebag_7::
	lock
	faceplayer
	msgbox SurvivalIsland_HomeBase_Text_Pokebag_7, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, SurvivalIsland_HomeBase_End
	case YES, SurvivalIsland_HomeBase_Pokebag_7_Warning
	case MULTI_B_PRESSED, SurvivalIsland_HomeBase_End

SurvivalIsland_HomeBase_Pokebag_7_Warning:
	msgbox SurvivalIsland_HomeBase_Text_Bag_Proceed_Warning, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, SurvivalIsland_HomeBase_End
	case YES, SurvivalIsland_HomeBase_Pokebag_7_Continue
	case MULTI_B_PRESSED, SurvivalIsland_HomeBase_End	

SurvivalIsland_HomeBase_Pokebag_7_Continue::
	setflag FLAG_PICKED_STARTER_POKEMON
	fadescreen FADE_TO_BLACK
	setvar VAR_BAG_SELECTED, 7
	special ChooseStarter
	waitstate
	special HealPlayerParty
	setflag FLAG_HIDE_HOMEBASE_STARTERS_BAG_7
	setflag FLAG_HIDE_HOMEBASE_STARTERS_BAG_8
	setflag FLAG_HIDE_HOMEBASE_STARTERS_BAG_9
	removeobject LOCALID_POKEBAG_7
	removeobject LOCALID_POKEBAG_8
	removeobject LOCALID_POKEBAG_9
	release
	end


SurvivalIsland_HomeBase_Pokebag_8::
	lock
	faceplayer
	msgbox SurvivalIsland_HomeBase_Text_Pokebag_8, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, SurvivalIsland_HomeBase_End
	case YES, SurvivalIsland_HomeBase_Pokebag_8_Warning
	case MULTI_B_PRESSED, SurvivalIsland_HomeBase_End

SurvivalIsland_HomeBase_Pokebag_8_Warning:
	msgbox SurvivalIsland_HomeBase_Text_Bag_Proceed_Warning, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, SurvivalIsland_HomeBase_End
	case YES, SurvivalIsland_HomeBase_Pokebag_8_Continue
	case MULTI_B_PRESSED, SurvivalIsland_HomeBase_End	

SurvivalIsland_HomeBase_Pokebag_8_Continue::
	setflag FLAG_PICKED_STARTER_POKEMON
	fadescreen FADE_TO_BLACK
	setvar VAR_BAG_SELECTED, 8
	special ChooseStarter
	waitstate
	special HealPlayerParty
	setflag FLAG_HIDE_HOMEBASE_STARTERS_BAG_7
	setflag FLAG_HIDE_HOMEBASE_STARTERS_BAG_8
	setflag FLAG_HIDE_HOMEBASE_STARTERS_BAG_9
	removeobject LOCALID_POKEBAG_7
	removeobject LOCALID_POKEBAG_8
	removeobject LOCALID_POKEBAG_9
	release
	end


SurvivalIsland_HomeBase_Pokebag_9::
	lock
	faceplayer
	msgbox SurvivalIsland_HomeBase_Text_Pokebag_9, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, SurvivalIsland_HomeBase_End
	case YES, SurvivalIsland_HomeBase_Pokebag_9_Warning
	case MULTI_B_PRESSED, SurvivalIsland_HomeBase_End

SurvivalIsland_HomeBase_Pokebag_9_Warning:
	msgbox SurvivalIsland_HomeBase_Text_Bag_Proceed_Warning, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, SurvivalIsland_HomeBase_End
	case YES, SurvivalIsland_HomeBase_Pokebag_9_Continue
	case MULTI_B_PRESSED, SurvivalIsland_HomeBase_End	

SurvivalIsland_HomeBase_Pokebag_9_Continue::
	setflag FLAG_PICKED_STARTER_POKEMON
	fadescreen FADE_TO_BLACK
	setvar VAR_BAG_SELECTED, 9
	special ChooseStarter
	waitstate
	special HealPlayerParty
	setflag FLAG_HIDE_HOMEBASE_STARTERS_BAG_7
	setflag FLAG_HIDE_HOMEBASE_STARTERS_BAG_8
	setflag FLAG_HIDE_HOMEBASE_STARTERS_BAG_9
	removeobject LOCALID_POKEBAG_7
	removeobject LOCALID_POKEBAG_8
	removeobject LOCALID_POKEBAG_9
	release
	end

SurvivalIsland_HomeBase_ItemBall::
	setflag FLAG_SYS_POKEDEX_GET
	special SetUnlockedPokedexFlags
	message SurvivalIsland_HomeBase_Text_ReceivedPokedex
	playfanfare MUS_OBTAIN_ITEM
	closemessage
	message LittlerootTown_ProfessorBirchsLab_Text_PokedexUpgradedToNational
	waitmessage
	waitfanfare
	closemessage
	setflag FLAG_SYS_NATIONAL_DEX
	special EnableNationalPokedex
	removeobject LOCALID_ITEMBALL
	end

SurvivalIsland_HomeBase_SailorFirstVisit::
	delay 10
	message SurvivalIsland_HomeBase_Text_Sailor1
	closemessage
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
	closemessage
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

SurvivalIsland_HomeBase_Text_Bag_Proceed_Warning:
	.string "Warning! Proceeding with this\n"
	.string "selection is irreversable and\l"
	.string "you will not be able to choose\l"
	.string "a POKéMON from another available\l"
	.string "bag.\p"
	.string "The other bag(s) and its contents\n"
	.string "will be lost to space and time and\l"
	.string "you will not be able to retrieve\l"
	.string "it's contents. Really Proceed?$"

SurvivalIsland_HomeBase_Text_Pokebag_5:
	.string "This bag contains the Unova\n"
	.string "Starters: Snivy, Tepig, and\l"
	.string "Oshawott. Continue with\l"
	.string "selection?$"

SurvivalIsland_HomeBase_Text_Pokebag_6:
	.string "This bag contains the Kalos\n"
	.string "Starters: Chespin, Fennekin,\l"
	.string "and Froakie. Continue with\l"
	.string "selection?$"

SurvivalIsland_HomeBase_Text_Pokebag_7:
	.string "This bag contains the Alola\n"
	.string "Starters: Rowlet, Litten,\l"
	.string "and Popplio. Continue with\l"
	.string "selection?$"

SurvivalIsland_HomeBase_Text_Pokebag_8:
	.string "This bag contains the Galar\n"
	.string "Starters: Grookey, Scorbunny,\l"
	.string "and Sobble. Continue with\l"
	.string "selection?$"

SurvivalIsland_HomeBase_Text_Pokebag_9:
	.string "This bag contains the Paldea\n"
	.string "Starters: Sprigatito, Fuecoco,\l"
	.string "and Quaxly. Continue with\l"
	.string "selection?$"

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

SurvivalIsland_HomeBase_Text_ReceivedPokedex:
	.string "{PLAYER} received the POKéDEX!$"
