.set LOCALID_HIDE_FOSSIL, 1

FossilCave_Earth_MapScripts::
	.byte 0

FossilCave_Earth_EventScript_HideFossil::
	lock
	faceplayer
	msgbox FossilCave_Earth_Text_TakeHideFossil, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FossilCave_Earth_EventScript_LeaveHideFossil
	giveitem ITEM_FEATHER_FOSSIL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	closemessage
	setflag FLAG_HIDE_FOSSIL_CAVE_ICE_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_FIRE_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_WATER_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_ELECTRIC_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_GROUND_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_FLYING_FOSSIL
	removeobject LOCALID_HIDE_FOSSIL
	delay 30
	goto FossilCave_Earth_EventScript_CollapseFossilCave
	end

FossilCave_Earth_EventScript_LeaveHideFossil::
	msgbox FossilCave_Earth_Text_LeftHideFossilAlone, MSGBOX_DEFAULT
	release
	end


FossilCave_Earth_EventScript_CollapseFossilCave::
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

FossilCave_Earth_EventScript_DustPile_Part1::
	lock
	faceplayer
	goto_if_unset FLAG_SHIELD_OF_DEFENDING_PICKED_UP FossilCave_Earth_EventScript_DustPile_Part2
	msgbox FossilCave_Earth_Text_DustPileNothingExtraordinary MSGBOX_AUTOCLOSE
	release
	end

FossilCave_Earth_EventScript_DustPile_Part2::
	msgbox FossilCave_Earth_Text_DustPileSparkles, MSGBOX_DEFAULT
	giveitem ITEM_SHIELD_OF_DEFENDING
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	closemessage
	goto_if_eq VAR_RESULT, TRUE, FossilCave_Earth_EventScript_DustPile_Part3
	release
	end

FossilCave_Earth_EventScript_DustPile_Part3::
	msgbox FossilCave_Earth_Text_StrangeAmuletReacted MSGBOX_DEFAULT
	setflag FLAG_SHIELD_OF_DEFENDING_PICKED_UP
	release
	end	

FossilCave_Earth_Text_DustPileNothingExtraordinary:
	.string "This dust pile sparkles like\n"
	.string "the night sky.\p"
	.string "{PLAYER} examined the dust pile\p"
	.string "Upon closer inspection, it\n"
	.string "appeared to be nothing\l"
	.string "extraordinary…$"


FossilCave_Earth_Text_DustPileSparkles:
	.string "This dust pile sparkles like\n"
	.string "the night sky.\p"
	.string "{PLAYER} examined the dust pile\n"
	.string "and found a something hiding.\l"
	.string "underneath.\p"
	.string "{PLAYER} pulled the shield\n"
	.string "out of the dust pile.$"

FossilCave_Earth_Text_StrangeAmuletReacted:
	.string "The amulet within {PLAYER}'s bag\n"
	.string "flashed brightly.\p"
	.string "{PLAYER} took out the amulet\n"
	.string "inspected it.\p"
	.string "The closer you moved the amulet\n"
	.string "to the shield, the brighter it\l"
	.string "became.\p"
	.string "It seems to be reacting to the\n"
	.string "shield…\l"
	.string "and something else…$" 


FossilCave_Earth_Text_TakeHideFossil:
	.string "You found the HIDE FOSSIL.\p"
	.string "If this FOSSIL is taken, the ground\n"
	.string "around it will likely collapse…\p"
	.string "Take the HIDE FOSSIL anyway?$"

FossilCave_Earth_Text_LeftHideFossilAlone:
	.string "{PLAYER} left the HIDE FOSSIL alone.$"
