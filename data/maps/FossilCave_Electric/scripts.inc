.set LOCALID_BOLT_FOSSIL, 1 @.set LOCALID_HOOF_FOSSIL, 1

FossilCave_Electric_MapScripts::
	.byte 0

FossilCave_Electric_EventScript_BoltFossil:: @FossilCave_Electric_EventScript_HoofFossil::
	lock
	faceplayer
	msgbox FossilCave_Electric_Text_TakeBoltFossil, MSGBOX_YESNO @		msgbox FossilCave_Electric_Text_TakeHoofFossil, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FossilCave_Electric_EventScript_LeaveBoltFossil @ 	goto_if_eq VAR_RESULT, NO, FossilCave_Electric_EventScript_LeaveHoofFossil
	giveitem ITEM_FEATHER_FOSSIL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	closemessage
	setflag FLAG_HIDE_FOSSIL_CAVE_ICE_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_FIRE_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_WATER_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_ELECTRIC_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_GROUND_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_FLYING_FOSSIL
	removeobject LOCALID_BOLT_FOSSIL @	removeobject LOCALID_HOOF_FOSSIL
	delay 30
	goto FossilCave_Electric_EventScript_CollapseFossilCave
	end

FossilCave_Electric_EventScript_LeaveBoltFossil:: @FossilCave_Electric_EventScript_LeaveHoofFossil::
	msgbox FossilCave_Electric_Text_LeftBoltFossilAlone, MSGBOX_DEFAULT @ 	msgbox FossilCave_Electric_Text_LeftHoofFossilAlone, MSGBOX_DEFAULT 
	release
	end


FossilCave_Electric_EventScript_CollapseFossilCave::
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


FossilCave_Electric_Text_TakeBoltFossil: @ FossilCave_Electric_Text_TakeHoofFossil:
	.string "You found the BOLT FOSSIL.\p" @ 	.string "You found the HOOF FOSSIL.\p"
	.string "If this FOSSIL is taken, the ground\n"
	.string "around it will likely collapse…\p"
	.string "Take the BOLT FOSSIL anyway?$" @ 	.string "Take the HOOF FOSSIL anyway?$" 

FossilCave_Electric_Text_LeftBoltFossilAlone: @FossilCave_Electric_Text_LeftHoofFossilAlone
	.string "{PLAYER} left the BOLT FOSSIL alone.$" @ 	.string "{PLAYER} left the HOOF FOSSIL alone.$"