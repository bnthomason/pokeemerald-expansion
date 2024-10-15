.set LOCALID_IRON_FOSSIL, 1

FossilCave_Steel_MapScripts::
	.byte 0

FossilCave_Steel_EventScript_IronFossil::
	lock
	faceplayer
	msgbox FossilCave_Steel_Text_TakeIronFossil, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FossilCave_Steel_EventScript_LeaveIronFossil
	giveitem ITEM_FEATHER_FOSSIL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	closemessage
	setflag FLAG_HIDE_FOSSIL_CAVE_ICE_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_FIRE_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_WATER_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_ELECTRIC_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_GROUND_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_FLYING_FOSSIL
	removeobject LOCALID_IRON_FOSSIL
	delay 30
	goto FossilCave_Steel_EventScript_CollapseFossilCave
	end

FossilCave_Steel_EventScript_LeaveIronFossil::
	msgbox FossilCave_Steel_Text_LeftIronFossilAlone, MSGBOX_DEFAULT
	release
	end


FossilCave_Steel_EventScript_CollapseFossilCave::
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


FossilCave_Steel_Text_TakeIronFossil:
	.string "You found the IRON FOSSIL.\p"
	.string "If this FOSSIL is taken, the ground\n"
	.string "around it will likely collapse…\p"
	.string "Take the IRON FOSSIL anyway?$"

FossilCave_Steel_Text_LeftIronFossilAlone:
	.string "{PLAYER} left the IRON FOSSIL alone.$"