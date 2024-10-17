.set LOCALID_RIVAL, 2

Route103_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, Route103_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, Route103_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Route103_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route103_OnFrame
	.byte 0

Route103_OnLoad:
	call_if_set FLAG_SYS_GAME_CLEAR, Route103_EventScript_OpenAlteringCave
	call_if_set FLAG_SYS_POKEDEX_GET, Route103_EventScript_OpenFossilCavePreCheck
	call_if_eq VAR_FOSSIL_CAVE_STATE, 1, Route103_EventScript_HideFossilCave
@	call_if_eq VAR_FOSSIL_CAVE_STATE, 1, Route103_EventScript_ShowTemporaryFossilCave
	end

Route103_EventScript_OpenAlteringCave::
	setmetatile 105, 11, METATILE_General_CaveEntrance_Top, TRUE
	setmetatile 105, 12, METATILE_General_CaveEntrance_Bottom, FALSE
	return

Route103_EventScript_OpenFossilCavePreCheck::
	call_if_eq VAR_FOSSIL_CAVE_STATE, 0, Route103_EventScript_OpenFossilCave
	return

Route103_EventScript_OpenFossilCave::
	setmetatile 15, 6, METATILE_General_CaveEntrance_Top, TRUE
	setmetatile 15, 7, METATILE_General_CaveEntrance_Bottom, FALSE
	return

Route103_EventScript_HideFossilCave:
	setflag FLAG_FORCE_FOSSIL_CAVE_NOT_VISIBLE
@	setmaplayoutindex LAYOUT_ROUTE103_NO_FOSSIL_CAVE
	return

Route103_EventScript_ShowTemporaryFossilCave::
	setmetatile 8, 1, 0x089, TRUE
	setmetatile 9, 1, 0x071, TRUE
	setmetatile 10, 1, 0x074, TRUE
	setmetatile 11, 1, 0x089, TRUE
	setmetatile 12, 1, 0x071, TRUE
	setmetatile 13, 1, 0x071, TRUE
	setmetatile 14, 1, 0x073, TRUE
	setmetatile 15, 1, 0x075, TRUE
	setmetatile 16, 1, 0x071, TRUE
	setmetatile 17, 1, 0x074, TRUE
	setmetatile 18, 1, 0x07C, TRUE
	setmetatile 19, 1, 0x07C, TRUE
	setmetatile 20, 1, 0x07C, TRUE
	setmetatile 21, 1, 0x07C, TRUE
	setmetatile 22, 1, 0x07C, TRUE
	setmetatile 23, 1, 0x07C, TRUE
	setmetatile 8, 2, 0x089, FALSE
	setmetatile 9, 2, 0x071, FALSE
	setmetatile 10, 2, 0x074, FALSE
	setmetatile 11, 2, 0x089, FALSE
	setmetatile 12, 2, 0x071, FALSE
	setmetatile 13, 2, 0x071, FALSE
	setmetatile 14, 2, 0x073, FALSE
	setmetatile 15, 2, 0x075, FALSE
	setmetatile 16, 2, 0x071, FALSE
	setmetatile 17, 2, 0x074, FALSE
	setmetatile 18, 2, 0x07C, FALSE
	setmetatile 19, 2, 0x07C, FALSE
	setmetatile 20, 2, 0x07C, FALSE
	setmetatile 21, 2, 0x07C, FALSE
	setmetatile 22, 2, 0x07C, FALSE
	setmetatile 23, 2, 0x07C, FALSE
	setmetatile 8, 3, 0x089, FALSE
	setmetatile 9, 3, 0x071, FALSE
	setmetatile 10, 3, 0x074, FALSE
	setmetatile 11, 3, 0x089, FALSE
	setmetatile 12, 3, 0x071, FALSE
	setmetatile 13, 3, 0x071, FALSE
	setmetatile 14, 3, 0x073, FALSE
	setmetatile 15, 3, 0x075, FALSE
	setmetatile 16, 3, 0x071, FALSE
	setmetatile 17, 3, 0x074, FALSE
	setmetatile 18, 3, 0x07C, FALSE
	setmetatile 19, 3, 0x07C, FALSE
	setmetatile 20, 3, 0x07C, FALSE
	setmetatile 21, 3, 0x07C, FALSE
	setmetatile 22, 3, 0x07C, FALSE
	setmetatile 23, 3, 0x07C, FALSE
	setmetatile 8, 4, 0x07B, FALSE
	setmetatile 9, 4, 0x09C, FALSE
	setmetatile 10, 4, 0x07D, FALSE
	setmetatile 11, 4, 0x07B, FALSE
	setmetatile 12, 4, 0x07C, FALSE
	setmetatile 13, 4, 0x089, FALSE
	setmetatile 14, 4, 0x07B, FALSE
	setmetatile 15, 4, 0x07D, FALSE
	setmetatile 16, 4, 0x074, FALSE
	setmetatile 17, 4, 0x07D, FALSE
	setmetatile 18, 4, 0x071, FALSE
	setmetatile 19, 4, 0x071, FALSE
	setmetatile 20, 4, 0x071, FALSE
	setmetatile 21, 4, 0x071, FALSE
	setmetatile 22, 4, 0x071, FALSE
	setmetatile 23, 4, 0x071, FALSE
	setmetatile 8, 5, 0x1F0, FALSE
	setmetatile 9, 5, 0x1F1, FALSE
	setmetatile 10, 5, 0x1F0, FALSE
	setmetatile 11, 5, 0x1F1, FALSE
	setmetatile 12, 5, 0x089, FALSE
	setmetatile 13, 5, 0x073, FALSE
	setmetatile 14, 5, 0x071, FALSE
	setmetatile 15, 5, 0x071, FALSE
	setmetatile 16, 5, 0x075, FALSE
	setmetatile 17, 5, 0x074, FALSE
	setmetatile 18, 5, 0x1F0, FALSE
	setmetatile 19, 5, 0x1F1, FALSE
	setmetatile 20, 5, 0x1F0, FALSE
	setmetatile 21, 5, 0x1F1, FALSE
	setmetatile 22, 5, 0x1F0, FALSE
	setmetatile 23, 5, 0x1F1, FALSE
	setmetatile 12, 6, 0x070, FALSE
	setmetatile 13, 6, 0x07B, FALSE
	setmetatile 14, 6, 0x09F, FALSE
	setmetatile 15, 6, 0x07C, FALSE
	setmetatile 16, 6, 0x07D, FALSE
	setmetatile 17, 6, 0x072, FALSE
	setmetatile 12, 7, 0x078, FALSE
	setmetatile 13, 7, 0x079, FALSE
	setmetatile 14, 7, 0x0A7, FALSE
	setmetatile 15, 7, 0x079, FALSE
	setmetatile 16, 7, 0x079, FALSE
	setmetatile 17, 7, 0x07A, FALSE
	return


Route103_OnTransition:
	special SetFossilCaveVisibility
	call Common_EventScript_SetupRivalGfxId
	call ProfBirch_EventScript_UpdateLocation
@	call_if_unset FLAG_FOSSIL_CAVE_VISIBLE, Route103_EventScript_SetLayoutNoFossilCave
	call_if_set FLAG_FORCE_FOSSIL_CAVE_NOT_VISIBLE Route103_EventScript_SetLayoutNoFossilCave @ Route103_EventScript_SetFossilCaveVisible
	call_if_eq VAR_FOSSIL_CAVE_STATE, 1, Route103_EventScript_SetFallingPlayerGfx
	call_if_eq VAR_FOSSIL_CAVE_STATE, 2, Route103_EventScript_SetFossilCaveGone
	end

Route103_EventScript_SetFallingPlayerGfx::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Route103_EventScript_SetFallingPlayerGfxMale
	goto_if_eq VAR_RESULT, FEMALE, Route103_EventScript_SetFallingPlayerGfxFemale
	return

Route103_EventScript_SetFallingPlayerGfxMale::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_RIVAL_BRENDAN_NORMAL
	return

Route103_EventScript_SetFallingPlayerGfxFemale::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_RIVAL_MAY_NORMAL
	return

Route103_EventScript_SetFossilCaveGone::
	setvar VAR_FOSSIL_CAVE_STATE, 3
	return

Route103_EventScript_SetFossilCaveVisible::
	setflag FLAG_FOSSIL_CAVE_VISIBLE
	return


Route103_EventScript_SetLayoutNoFossilCave::
	setmaplayoutindex LAYOUT_ROUTE103_NO_FOSSIL_CAVE
	return

Route103_OnWarp:
	map_script_2 VAR_FOSSIL_CAVE_STATE, 1, Route103_EventScript_HidePlayerForFossilCave
	.2byte 0

Route103_EventScript_HidePlayerForFossilCave::
	hideobjectat OBJ_EVENT_ID_PLAYER, MAP_LITTLEROOT_TOWN
	end

Route103_OnFrame:
	map_script_2 VAR_FOSSIL_CAVE_STATE, 1, Route103_EventScript_FossilCaveDisappear
	.2byte 0

Route103_EventScript_FossilCaveDisappear::
	lockall
@	special StartFossilCaveShake
@	waitstate
@	delay 24
	playse SE_FALL
	addobject LOCALID_ROUTE103_PLAYER_FALLING
	special StartPlayerDescendFossilCave
	waitstate
	showobjectat OBJ_EVENT_ID_PLAYER, MAP_LITTLEROOT_TOWN
	removeobject LOCALID_ROUTE103_PLAYER_FALLING
	delay 16
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	delay 16
@	special StartFossilCaveDisintegration
@	waitstate
	setvar VAR_FOSSIL_CAVE_STATE, 2
	msgbox Route103_Text_LostOtherFossils, MSGBOX_DEFAULT
	releaseall
	end

Route103_EventScript_Rival::
	lockall
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Route103_EventScript_RivalMay
	goto_if_eq VAR_RESULT, FEMALE, Route103_EventScript_RivalBrendan
	end

Route103_EventScript_RivalMay::
	msgbox Route103_Text_MayRoute103Pokemon, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_MAY, TRUE
	applymovement LOCALID_RIVAL, Common_Movement_FacePlayer
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	msgbox Route103_Text_MayLetsBattle, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, Route103_EventScript_StartMayBattleTreecko
	case 1, Route103_EventScript_StartMayBattleTorchic
	case 2, Route103_EventScript_StartMayBattleMudkip
	end

Route103_EventScript_RivalBrendan::
	msgbox Route103_Text_BrendanRoute103Pokemon, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	applymovement LOCALID_RIVAL, Common_Movement_FacePlayer
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	msgbox Route103_Text_BrendanLetsBattle, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, Route103_EventScript_StartBrendanBattleTreecko
	case 1, Route103_EventScript_StartBrendanBattleTorchic
	case 2, Route103_EventScript_StartBrendanBattleMudkip
	end

Route103_EventScript_StartMayBattleTreecko::
	trainerbattle_no_intro TRAINER_MAY_ROUTE_103_TREECKO, Route103_Text_MayDefeated
	goto Route103_EventScript_AfterMayBattle
	end

Route103_EventScript_StartMayBattleTorchic::
	trainerbattle_no_intro TRAINER_MAY_ROUTE_103_TORCHIC, Route103_Text_MayDefeated
	goto Route103_EventScript_AfterMayBattle
	end

Route103_EventScript_StartMayBattleMudkip::
	trainerbattle_no_intro TRAINER_MAY_ROUTE_103_MUDKIP, Route103_Text_MayDefeated
	goto Route103_EventScript_AfterMayBattle
	end

Route103_EventScript_StartBrendanBattleTreecko::
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_103_TREECKO, Route103_Text_BrendanDefeated
	goto Route103_EventScript_AfterBrendanBattle
	end

Route103_EventScript_StartBrendanBattleTorchic::
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_103_TORCHIC, Route103_Text_BrendanDefeated
	goto Route103_EventScript_AfterBrendanBattle
	end

Route103_EventScript_StartBrendanBattleMudkip::
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_103_MUDKIP, Route103_Text_BrendanDefeated
	goto Route103_EventScript_AfterBrendanBattle
	end

Route103_EventScript_AfterMayBattle::
	msgbox Route103_Text_MayTimeToHeadBack, MSGBOX_DEFAULT
	goto Route103_EventScript_RivalExit
	end

Route103_EventScript_AfterBrendanBattle::
	msgbox Route103_Text_BrendanTimeToHeadBack, MSGBOX_DEFAULT
	goto Route103_EventScript_RivalExit
	end

Route103_EventScript_RivalExit::
	closemessage
	switch VAR_FACING
	case DIR_SOUTH, Route103_EventScript_RivalExitFacingSouth
	case DIR_NORTH, Route103_EventScript_RivalExitFacingNorth
	case DIR_WEST, Route103_EventScript_RivalExitFacingEastOrWest
	case DIR_EAST, Route103_EventScript_RivalExitFacingEastOrWest
	end

Route103_EventScript_RivalExitFacingNorth::
	applymovement OBJ_EVENT_ID_PLAYER, Route103_Movement_WatchRivalExitFacingNorth
	applymovement LOCALID_RIVAL, Route103_Movement_RivalExitFacingNorth1
	waitmovement 0
	playse SE_LEDGE
	applymovement LOCALID_RIVAL, Route103_Movement_RivalExitFacingNorth2
	waitmovement 0
	goto Route103_EventScript_RivalEnd
	end

Route103_EventScript_RivalExitFacingEastOrWest::
	applymovement OBJ_EVENT_ID_PLAYER, Route103_Movement_WatchRivalExitFacingEastOrWest
	applymovement LOCALID_RIVAL, Route103_Movement_RivalExit1
	waitmovement 0
	playse SE_LEDGE
	applymovement LOCALID_RIVAL, Route103_Movement_RivalExit2
	waitmovement 0
	goto Route103_EventScript_RivalEnd
	end

Route103_EventScript_RivalExitFacingSouth::
	applymovement LOCALID_RIVAL, Route103_Movement_RivalExit1
	waitmovement 0
	playse SE_LEDGE
	applymovement LOCALID_RIVAL, Route103_Movement_RivalExit2
	waitmovement 0
	goto Route103_EventScript_RivalEnd
	end

Route103_EventScript_RivalEnd::
	removeobject LOCALID_RIVAL
	setvar VAR_BIRCH_LAB_STATE, 4
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_RIVAL
	setflag FLAG_DEFEATED_RIVAL_ROUTE103
	setvar VAR_OLDALE_RIVAL_STATE, 1
	clearflag FLAG_HIDE_OLDALE_TOWN_RIVAL
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

Route103_Movement_RivalExitFacingNorth1:
	walk_left
	walk_down
	step_end

Route103_Movement_RivalExitFacingNorth2:
	jump_2_down
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Route103_Movement_WatchRivalExitFacingNorth:
	delay_16
	delay_4
	walk_in_place_faster_left
	delay_16
	walk_in_place_faster_down
	step_end

Route103_Movement_RivalExit1:
	walk_down
	step_end

Route103_Movement_RivalExit2:
	jump_2_down
	delay_16
	walk_down
	walk_down
	walk_down
	step_end

Route103_Movement_WatchRivalExitFacingEastOrWest:
	delay_16
	walk_in_place_faster_down
	step_end

Route103_EventScript_Boy::
	msgbox Route103_Text_ShouldHaveBroughtPotion, MSGBOX_NPC
	end

Route103_EventScript_Man::
	msgbox Route103_Text_ShortcutToOldale, MSGBOX_NPC
	end

Route103_EventScript_RouteSign::
	msgbox Route103_Text_RouteSign, MSGBOX_SIGN
	end

Route103_EventScript_Daisy::
	trainerbattle_single TRAINER_DAISY, Route103_Text_DaisyIntro, Route103_Text_DaisyDefeated
	msgbox Route103_Text_DaisyPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Amy::
	trainerbattle_double TRAINER_AMY_AND_LIV_1, Route103_Text_AmyIntro, Route103_Text_AmyDefeated, Route103_Text_AmyNotEnoughPokemon, Route102_EventScript_AmyRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route102_EventScript_AmyRematch
	msgbox Route103_Text_AmyPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_AmyRegisterMatchCallAfterBattle::
	msgbox Route103_Text_AmyLivRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_AMY_AND_LIV_1
	release
	end

Route102_EventScript_AmyRematch::
	trainerbattle_rematch_double TRAINER_AMY_AND_LIV_1, Route103_Text_AmyRematchIntro, Route103_Text_AmyRematchDefeated, Route103_Text_AmyRematchNotEnoughPokemon
	msgbox Route103_Text_AmyRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Liv::
	trainerbattle_double TRAINER_AMY_AND_LIV_1, Route103_Text_LivIntro, Route103_Text_LivDefeated, Route103_Text_LivNotEnoughPokemon, Route102_EventScript_LivRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route102_EventScript_LivRematch
	msgbox Route103_Text_LivPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_LivRegisterMatchCallAfterBattle::
	msgbox Route103_Text_AmyLivRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_AMY_AND_LIV_1
	release
	end

Route102_EventScript_LivRematch::
	trainerbattle_rematch_double TRAINER_AMY_AND_LIV_1, Route103_Text_LivRematchIntro, Route103_Text_LivRematchDefeated, Route103_Text_LivRematchNotEnoughPokemon
	msgbox Route103_Text_LivRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Andrew::
	trainerbattle_single TRAINER_ANDREW, Route103_Text_AndrewIntro, Route103_Text_AndrewDefeated
	msgbox Route103_Text_AndrewPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Miguel::
	trainerbattle_single TRAINER_MIGUEL_1, Route103_Text_MiguelIntro, Route103_Text_MiguelDefeated, Route102_EventScript_MiguelRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route103_EventScript_MiguelRematch
	msgbox Route103_Text_MiguelPostBattle, MSGBOX_DEFAULT
	release
	end

Route102_EventScript_MiguelRegisterMatchCallAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route103_Text_MiguelRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_MIGUEL_1
	release
	end

Route103_EventScript_MiguelRematch::
	trainerbattle_rematch TRAINER_MIGUEL_1, Route103_Text_MiguelRematchIntro, Route103_Text_MiguelRematchDefeated
	msgbox Route103_Text_MiguelRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Marcos::
	trainerbattle_single TRAINER_MARCOS, Route103_Text_MarcosIntro, Route103_Text_MarcosDefeated
	msgbox Route103_Text_MarcosPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Rhett::
	trainerbattle_single TRAINER_RHETT, Route103_Text_RhettIntro, Route103_Text_RhettDefeated
	msgbox Route103_Text_RhettPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Pete::
	trainerbattle_single TRAINER_PETE, Route103_Text_PeteIntro, Route103_Text_PeteDefeated
	msgbox Route103_Text_PetePostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Isabelle::
	trainerbattle_single TRAINER_ISABELLE, Route103_Text_IsabelleIntro, Route103_Text_IsabelleDefeated
	msgbox Route103_Text_IsabellePostBattle, MSGBOX_AUTOCLOSE
	end

Route103_Text_MayRoute103Pokemon:
	.string "MAY: Let's see… The POKéMON found\n"
	.string "on ROUTE 103 include…$"

Route103_Text_MayLetsBattle:
	.string "Oh, hi, {PLAYER}{KUN}!\p"
	.string "…Oh, I see, my dad gave you\n"
	.string "a POKéMON as a gift.\p"
	.string "Since we're here, let's have a quick\n"
	.string "battle!\p"
	.string "I'll give you a taste of what being\n"
	.string "a TRAINER is like.$"

Route103_Text_MayDefeated:
	.string "Wow! That's great!\n"
	.string "{PLAYER}{KUN}, you're pretty good!$"

Route103_Text_MayTimeToHeadBack:
	.string "MAY: I think I know why my dad has\n"
	.string "an eye out for you now.\p"
	.string "I mean, you just got that POKéMON,\n"
	.string "but it already likes you.\p"
	.string "You might be able to befriend any\n"
	.string "kind of POKéMON easily.\p"
	.string "Well, it's time to head back to\n"
	.string "the LAB.$"

Route103_Text_BrendanRoute103Pokemon:
	.string "BRENDAN: Okay, so it's this one and\n"
	.string "that one that live on ROUTE 103…$"

Route103_Text_BrendanLetsBattle:
	.string "Hey, it's {PLAYER}!\p"
	.string "…Oh, yeah, Dad gave you a POKéMON.\p"
	.string "Since we're here, how about a little\n"
	.string "battle?\p"
	.string "I'll teach you what being a TRAINER's\n"
	.string "about!$"

Route103_Text_BrendanDefeated:
	.string "Huh, {PLAYER}, you're not too shabby.$"

Route103_Text_BrendanTimeToHeadBack:
	.string "BRENDAN: I think I get it.\n"
	.string "I think I know why my dad has his eye\l"
	.string "out for you now.\p"
	.string "Look, your POKéMON already likes you,\n"
	.string "even though you just got it.\p"
	.string "{PLAYER}, I get the feeling that you\n"
	.string "could befriend any POKéMON with ease.\p"
	.string "We should head back to the LAB.$"

Route103_Text_ShouldHaveBroughtPotion:
	.string "My POKéMON is staggeringly tired…\n"
	.string "I should have brought a POTION…$"

Route103_Text_ShortcutToOldale:
	.string "If you cross the sea from here,\n"
	.string "it'll be a shortcut to OLDALE TOWN.\p"
	.string "Fufufu, that's useful, isn't it?$"

Route103_Text_RouteSign:
	.string "ROUTE 103\n"
	.string "{DOWN_ARROW} OLDALE TOWN$"

Route103_Text_LostOtherFossils:
	.string "Seems we lost all the other\n"
	.string "fossils...$"
