.set LOCALID_FEATHER_FOSSIL, 1

FossilCave_Ice_MapScripts::
	.byte 0

FossilCave_Ice_EventScript_StrangeRock::
	lock
	faceplayer
	goto_if_unset FLAG_BOOK_OF_WILL_PICKED_UP FossilCave_Ice_EventScript_StrangeRock_Part2
	msgbox FossilCave_Ice_Text_StrangeRockWasEmpty MSGBOX_AUTOCLOSE
	release
	end

FossilCave_Ice_EventScript_StrangeRock_Part2::
	msgbox FossilCave_Ice_Text_StrangeRockHoldsSomekindofPower, MSGBOX_DEFAULT
	giveitem ITEM_BOOK_OF_WILL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	closemessage
	goto_if_eq VAR_RESULT, TRUE, FossilCave_Ice_EventScript_StrangeRockPart3
	release
	end

FossilCave_Ice_EventScript_StrangeRockPart3::
	msgbox FossilCave_Ice_Text_StrangeAmuletReacted MSGBOX_DEFAULT
	setflag FLAG_BOOK_OF_WILL_PICKED_UP
	release
	end	

FossilCave_Ice_EventScript_FeatherFossil::
	lock
	faceplayer
	msgbox FossilCave_Ice_Text_TakeFeatherFossil, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FossilCave_Ice_EventScript_LeaveFeatherFossil
	giveitem ITEM_FEATHER_FOSSIL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	closemessage
	setflag FLAG_HIDE_FOSSIL_CAVE_ICE_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_FIRE_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_WATER_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_ELECTRIC_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_GROUND_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_FLYING_FOSSIL
	removeobject LOCALID_FEATHER_FOSSIL
	delay 30
	goto FossilCave_Ice_EventScript_CollapseFossilCave
	end

FossilCave_Ice_EventScript_LeaveFeatherFossil::
	msgbox FossilCave_Ice_Text_LeftFeatherFossilAlone, MSGBOX_DEFAULT
	release
	end


FossilCave_Ice_EventScript_CollapseFossilCave::
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

FossilCave_Ice_Text_StrangeRockHoldsSomekindofPower:
	.string "This strange rock seems to hold.\n"
	.string "some kind of mystical power.\p"
	.string "{PLAYER} checked the rock and…\n"
	.string "found a spell book within.$"

FossilCave_Ice_Text_StrangeAmuletReacted:
	.string "The amulet within {PLAYER}'s bag\n"
	.string "flashed brightly.\p"
	.string "{PLAYER} took out the amulet\n"
	.string "inspected it.\p"
	.string "The closer you moved the amulet\n"
	.string "to the book, the brighter it\l"
	.string "became.\p"
	.string "It seems to be reacting to the\n"
	.string "book…\l" 
	.string "and something else…$"

FossilCave_Ice_Text_StrangeRockWasEmpty:
	.string "This strange rock appears to be\n"
	.string "exuding a faint hint of magic.\p"
	.string "Checked inside the rock…\p"
	.string "But it was empty…$"

FossilCave_Ice_Text_TakeFeatherFossil:
	.string "You found the FEATHER FOSSIL.\p"
	.string "If this FOSSIL is taken, the ground\n"
	.string "around it will likely collapse…\p"
	.string "Take the FEATHER FOSSIL anyway?$"

FossilCave_Ice_Text_LeftFeatherFossilAlone:
	.string "{PLAYER} left the FEATHER FOSSIL alone.$"
