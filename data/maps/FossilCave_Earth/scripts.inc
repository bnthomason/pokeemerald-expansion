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


FossilCave_Earth_Text_TakeHideFossil:
	.string "You found the HIDE FOSSIL.\p"
	.string "If this FOSSIL is taken, the ground\n"
	.string "around it will likely collapse…\p"
	.string "Take the HIDE FOSSIL anyway?$"

FossilCave_Earth_Text_LeftHideFossilAlone:
	.string "{PLAYER} left the HIDE FOSSIL alone.$"