
.set LOCALID_GUARD_1, 2
.set LOCALID_GUARD_2, 3


Area1_Boss_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Area1_Boss_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Area1_Boss_OnLoad
	.byte 0

Area1_Boss_OnLoad:
	goto_if_set FLAG_AREA1_BOSS_GUARDS_MOVED, SurvivalIsland_Area1_Boss_End
	call_if_defeated ISLAND_BOSS_SETH_EASY, SurvivalIsland_Area1_Boss_MoveGuards
	call_if_defeated ISLAND_BOSS_SETH_NORMAL, SurvivalIsland_Area1_Boss_MoveGuards
	call_if_defeated ISLAND_BOSS_SETH_HARD, SurvivalIsland_Area1_Boss_MoveGuards
	call_if_defeated ISLAND_BOSS_SETH_ULTIMATE, SurvivalIsland_Area1_Boss_MoveGuards
	end

Area1_Boss_OnTransition:
	goto_if_not_defeated ISLAND_BOSS_SETH_ULTIMATE, Area1_Boss_EventScript_GuardCheck2
	end

Area1_Boss_EventScript_GuardCheck2:
	goto_if_not_defeated ISLAND_BOSS_SETH_HARD, Area1_Boss_EventScript_GuardCheck3
	end

Area1_Boss_EventScript_GuardCheck3:
	goto_if_not_defeated ISLAND_BOSS_SETH_NORMAL, Area1_Boss_EventScript_GuardCheck4
	end

Area1_Boss_EventScript_GuardCheck4:
	goto_if_not_defeated ISLAND_BOSS_SETH_EASY, Area1_Boss_EventScript_GuardsBlockDoor
	end

SurvivalIsland_Area1_Boss_End::
	end

Area1_Boss_EventScript_GuardsBlockDoor::
	setobjectxyperm LOCALID_GUARD_1, 8, 9
	setobjectxyperm LOCALID_GUARD_2, 9, 9
	return

SurvivalIsland_Area1_Boss_MoveGuards::
	applymovement LOCALID_GUARD_1, SurvivalIsland_Area1_Boss_Movement_LeftGuardOutOfWay
	applymovement LOCALID_GUARD_2, SurvivalIsland_Area1_Boss_Movement_RightGuardOutOfWay
	waitmovement 0
	delay 10
	copyobjectxytoperm LOCALID_GUARD_1
	copyobjectxytoperm LOCALID_GUARD_2
	setflag FLAG_AREA1_BOSS_GUARDS_MOVED
	return

SurvivalIsland_Area1_Boss_Man_In_Suit_Seth::
	call_if_eq VAR_GAME_DIFFICULTY, DIFFICULTY_EASY, SurvivalIsland_Area1_Boss_Seth_Battle_Easy
	call_if_eq VAR_GAME_DIFFICULTY, DIFFICULTY_NORMAL, SurvivalIsland_Area1_Boss_Seth_Battle_Normal
	call_if_eq VAR_GAME_DIFFICULTY, DIFFICULTY_HARD, SurvivalIsland_Area1_Boss_Seth_Battle_Hard
	call_if_eq VAR_GAME_DIFFICULTY, DIFFICULTY_ULTIMATE, SurvivalIsland_Area1_Boss_Seth_Battle_Ultimate
	msgbox Area1_Boss_Text_SethPostBattle, MSGBOX_DEFAULT
	release
	end

SurvivalIsland_Area1_Boss_Seth_Battle_Easy:
	trainerbattle_double ISLAND_BOSS_SETH_EASY, Area1_Boss_Text_SethIntro, Area1_Boss_Text_SethDefeat, Area1_Boss_Text_SethNotEnoughMons
	return

SurvivalIsland_Area1_Boss_Seth_Battle_Normal:
	trainerbattle_double ISLAND_BOSS_SETH_NORMAL, Area1_Boss_Text_SethIntro, Area1_Boss_Text_SethDefeat, Area1_Boss_Text_SethNotEnoughMons
	return

SurvivalIsland_Area1_Boss_Seth_Battle_Hard:
	trainerbattle_double ISLAND_BOSS_SETH_HARD, Area1_Boss_Text_SethIntro, Area1_Boss_Text_SethDefeat, Area1_Boss_Text_SethNotEnoughMons
	return

SurvivalIsland_Area1_Boss_Seth_Battle_Ultimate:
	trainerbattle_double ISLAND_BOSS_SETH_ULTIMATE, Area1_Boss_Text_SethIntro, Area1_Boss_Text_SethDefeat, Area1_Boss_Text_SethNotEnoughMons
	return


SurvivalIsland_Area1_Boss_ForestGuard::
	lockall
	goto_if_set FLAG_AREA1_BOSS_GUARDS_MOVED, SurvivalIsland_Area1_Boss_ForestGuard_Proceed
	message SurvivalIsland_Area1_Boss_Text_YouMustDefeatTheAreaBoss
	waitmessage
	delay 120
	releaseall
	end

SurvivalIsland_Area1_Boss_ForestGuard_Proceed::
	msgbox SurvivalIsland_Area1_Boss_ForestGuard_Text_Proceed, MSGBOX_DEFAULT
	releaseall
	end


SurvivalIsland_Area1_Boss_Movement_LeftGuardOutOfWay:
	walk_left
	walk_in_place_faster_down
	step_end

SurvivalIsland_Area1_Boss_Movement_RightGuardOutOfWay:
	walk_right
	walk_in_place_faster_down
	step_end


SurvivalIsland_Area1_Boss_EventScript_Sign::
	msgbox SurvivalIsland_Area1_Boss_Text_GymSign, MSGBOX_SIGN
	end

SurvivalIsland_Area1_Boss_Text_GymSign:
	.string "AREA1 BOSS$"

SurvivalIsland_Area1_Boss_Text_YouMustDefeatTheAreaBoss:
	.string "You must defeat the Area Boss in\n"
	.string "order to proceed.$"

SurvivalIsland_Area1_Boss_ForestGuard_Text_Proceed:
	.string "Proceed onward to the next Area!$"

Area1_Boss_Text_SethIntro:
	.string "You... challenge me? Don't make me\n"
	.string "laugh! You won't even lay a finger\l"
	.string "on me!\p"
	.string "I hold the record for the most\n"
	.string "elusive POKéMON in the country!\p"
	.string "Not a single soul dares to challenge\l"
	.string "me!\p"
	.string "Try as you like! Wiggle! Struggle!\n"
	.string "Squirm! There ain't no way you can\l"
	.string "touch me!$"

Area1_Boss_Text_SethDefeat:
	.string "Me? Defeated?! Impossible!\p$"
	.string "I won't accept it! I NEVER lose!$" 

Area1_Boss_Text_SethNotEnoughMons:
	.string "You don't have enough mons...!\p"
	.string "What...?! Is this some sort of joke?!\n"
	.string "Come back when you have at least 2\l"
	.string "POKéMON. Or better yet... don't come\l"
	.string "back at all!$"

Area1_Boss_Text_SethPostBattle:
	.string "Get lost, scum!$"
