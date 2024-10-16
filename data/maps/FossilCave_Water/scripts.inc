.set LOCALID_SCALE_FOSSIL, 1

FossilCave_Water_MapScripts::
	.byte 0

FossilCave_Water_EventScript_ScaleFossil::
	lock
	faceplayer
	msgbox FossilCave_Water_Text_TakeScaleFossil, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FossilCave_Water_EventScript_LeaveScaleFossil
	giveitem ITEM_FEATHER_FOSSIL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	closemessage
	setflag FLAG_HIDE_FOSSIL_CAVE_ICE_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_FIRE_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_WATER_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_ELECTRIC_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_GROUND_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_FLYING_FOSSIL
	removeobject LOCALID_SCALE_FOSSIL
	delay 30
	goto FossilCave_Water_EventScript_CollapseFossilCave
	end

FossilCave_Water_EventScript_LeaveScaleFossil::
	msgbox FossilCave_Water_Text_LeftScaleFossilAlone, MSGBOX_DEFAULT
	release
	end


FossilCave_Water_EventScript_CollapseFossilCave::
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

FossilCave_Water_EventScript_WetRock_Part1::
	lock
	faceplayer
	goto_if_unset FLAG_MIRROR_OF_REFLECTION_PICKED_UP FossilCave_Water_EventScript_WetRock_Part2
	msgbox FossilCave_Water_Text_WetRockWasOnceBeautiful MSGBOX_AUTOCLOSE
	release
	end

FossilCave_Water_EventScript_WetRock_Part2::
	msgbox FossilCave_Water_Text_WetRockIsBeautiful, MSGBOX_DEFAULT
	giveitem ITEM_MIRROR_OF_REFLECTION
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	closemessage
	goto_if_eq VAR_RESULT, TRUE, FossilCave_Water_EventScript_WetRock_Part3
	release
	end

FossilCave_Water_EventScript_WetRock_Part3::
	msgbox FossilCave_Water_Text_StrangeAmuletReacted MSGBOX_DEFAULT
	setflag FLAG_MIRROR_OF_REFLECTION_PICKED_UP
	release
	end	

FossilCave_Water_Text_WetRockWasOnceBeautiful:
	.string "This wet rock is beautiful\n"
	.string "and inviting to look at.\p"
	.string "{PLAYER} examined the wet rock\p"
	.string "Upon closer inspection, its\n"
	.string "luster had already faded…$"


FossilCave_Water_Text_WetRockIsBeautiful:
	.string "This wet rock is beautiful\n"
	.string "and inviting to look at.\p"
	.string "{PLAYER} examined the wet rock\n"
	.string "and found a mirror sitting atop.\l"
	.string "of it.\p"
	.string "{PLAYER} reached out and took\n"
	.string "the mirror from the rock.$"

FossilCave_Water_Text_StrangeAmuletReacted:
	.string "The amulet within {PLAYER}'s bag\n"
	.string "flashed brightly.\p"
	.string "{PLAYER} took out the amulet\n"
	.string "inspected it.\p"
	.string "The closer you moved the amulet\n"
	.string "to the mirror, the brighter it\l"
	.string "became.\p"
	.string "It seems to be reacting to the\n"
	.string "mirror…\l"
	.string "and something else…$" 

FossilCave_Water_Text_TakeScaleFossil:
	.string "You found the SCALE FOSSIL.\p"
	.string "If this FOSSIL is taken, the ground\n"
	.string "around it will likely collapse…\p"
	.string "Take the SCALE FOSSIL anyway?$"

FossilCave_Water_Text_LeftScaleFossilAlone:
	.string "{PLAYER} left the SCALE FOSSIL alone.$"
