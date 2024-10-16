.set LOCALID_CLAW_FOSSIL, 1

FossilCave_Fire_MapScripts::
	.byte 0

FossilCave_Fire_EventScript_ClawFossil::
	lock
	faceplayer
	msgbox FossilCave_Fire_Text_TakeClawFossil, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FossilCave_Fire_EventScript_LeaveClawFossil
	giveitem ITEM_FEATHER_FOSSIL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	closemessage
	setflag FLAG_HIDE_FOSSIL_CAVE_ICE_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_FIRE_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_WATER_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_ELECTRIC_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_GROUND_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_FLYING_FOSSIL
	removeobject LOCALID_CLAW_FOSSIL
	delay 30
	goto FossilCave_Fire_EventScript_CollapseFossilCave
	end

FossilCave_Fire_EventScript_LeaveClawFossil::
	msgbox FossilCave_Fire_Text_LeftClawFossilAlone, MSGBOX_DEFAULT
	release
	end


FossilCave_Fire_EventScript_CollapseFossilCave::
	setvar VAR_0x8004, 1   @ vertical pan
	setvar VAR_0x8005, 1   @ horizontal pan
	setvar VAR_0x8006, 32  @ num shakes
	setvar VAR_0x8007, 2   @ shake delay
	special ShakeCamera
	waitstate
	special DoFossilCaveCeilingCrumble
	waitstate
	setvar VAR_FOSSIL_CAVE_STATE, 1
	clearflag FLAG_LANDMARK_FOSSIL_CAVE
	warpteleport MAP_ROUTE103, 8, 8
	waitstate
	release
	end


FossilCave_Fire_EventScript_MysteriousStone_Part1::
	lock
	faceplayer
	goto_if_unset FLAG_IMPERIAL_SWORD_PICKED_UP FossilCave_Fire_EventScript_MysteriousStone_Part2
	msgbox FossilCave_Fire_Text_StoneWasStoneCold MSGBOX_AUTOCLOSE
	release
	end

FossilCave_Fire_EventScript_MysteriousStone_Part2::
	msgbox FossilCave_Fire_Text_MysteriousStoneIsWarmAndVibrant, MSGBOX_DEFAULT
	giveitem ITEM_IMPERIAL_SWORD
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	closemessage
	checkitem ITEM_SLIDE_AMULET
	goto_if_eq VAR_RESULT, TRUE, FossilCave_Fire_EventScript_MysteriousStone_Part3
	release
	end

FossilCave_Fire_EventScript_MysteriousStone_Part3::
	checkitem ITEM_SLIDE_AMULET
	goto_if_eq VAR_RESULT, TRUE, FossilCave_Fire_EventScript_MysteriousStone_Part4
	setflag FLAG_IMPERIAL_SWORD_PICKED_UP
	release
	end	

FossilCave_Fire_EventScript_MysteriousStone_Part4::	
	msgbox FossilCave_Fire_Text_StrangeAmuletReacted MSGBOX_DEFAULT
	setflag FLAG_IMPERIAL_SWORD_PICKED_UP
	release
	end	
	

FossilCave_Fire_Text_StoneWasStoneCold:
	.string "This mysterious stone appears warm\n"
	.string "and vibrant… you can't seem to\l"
	.string "resist touching it..\p"
	.string "{PLAYER} reached for the stone\n"
	.string "and touched it.\l"
	.string "But it was stone cold…$"

FossilCave_Fire_Text_MysteriousStoneIsWarmAndVibrant:
	.string "This mysterious stone appears warm\n"
	.string "and vibrant… you can't seem to\l"
	.string "resist touching it..\p"
	.string "{PLAYER} reached for the stone\p"
	.string "and found a sword stuck within.\l"
	.string "{PLAYER} pulled upon the sword\n"
	.string "and dislodged it from the stone.$"

FossilCave_Fire_Text_StrangeAmuletReacted:
	.string "The amulet within {PLAYER}'s bag\n"
	.string "flashed brightly.\p"
	.string "{PLAYER} took out the amulet\n"
	.string "inspected it.\p"
	.string "The closer you moved the amulet\n"
	.string "to the sword, the brighter it\l"
	.string "became.\p"
	.string "It seems to be reacting to the\n"
	.string "sword…\l" 
	.string "and something else…$"


FossilCave_Fire_Text_TakeClawFossil:
	.string "You found the CLAW FOSSIL.\p"
	.string "If this FOSSIL is taken, the ground\n"
	.string "around it will likely collapse…\p"
	.string "Take the CLAW FOSSIL anyway?$"

FossilCave_Fire_Text_LeftClawFossilAlone:
	.string "{PLAYER} left the CLAW FOSSIL alone.$"
