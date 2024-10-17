.set LOCALID_BOLT_FOSSIL, 1 @.set LOCALID_HOOF_FOSSIL, 1

FossilCave_Electric_MapScripts::
	.byte 0

FossilCave_Electric_EventScript_StrangeTrashCan::
	lock
	faceplayer
	goto_if_unset FLAG_STAFF_OF_MAGIC_PICKED_UP FossilCave_Electric_EventScript_StrangeTrashCan_Part2
	msgbox FossilCave_Electric_Text_TrashWasEmpty MSGBOX_AUTOCLOSE
	release
	end

FossilCave_Electric_EventScript_StrangeTrashCan_Part2::
	msgbox FossilCave_Electric_Text_StrangeTrashIsOutofPlaceandDangerous, MSGBOX_DEFAULT
	giveitem ITEM_STAFF_OF_MAGIC
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	closemessage
	goto_if_eq VAR_RESULT, TRUE, FossilCave_Electric_EventScript_StrangeTrashCan_Part3
	release
	end

FossilCave_Electric_EventScript_StrangeTrashCan_Part3::
	checkitem ITEM_SLIDE_AMULET
	goto_if_eq VAR_RESULT, TRUE, FossilCave_Electric_EventScript_StrangeTrashCan_Part4
	setflag FLAG_STAFF_OF_MAGIC_PICKED_UP
	release
	end	

FossilCave_Electric_EventScript_StrangeTrashCan_Part4::	
	msgbox FossilCave_Electric_Text_StrangeAmuletReacted MSGBOX_DEFAULT
	setflag FLAG_STAFF_OF_MAGIC_PICKED_UP
	release
	end	


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
	warpteleport MAP_ROUTE103, 15, 8
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

FossilCave_Electric_Text_TrashWasEmpty:
	.string "This trash can is strange and out\n"
	.string "of place.\p"
	.string "{PLAYER} peered inside the trash\n"
	.string "can…\p"
	.string "But it was empty…$"

FossilCave_Electric_Text_StrangeTrashIsOutofPlaceandDangerous:
	.string "This strange trash can appears\n"
	.string "of place and positioned in a.\l"
	.string "dangerous location.\p"
	.string "{PLAYER} peered inside the trash\n"
	.string "can and found a source of powerful\l"
	.string "magic eminating from within.\p"
	.string "{PLAYER} reached inside and pulled\n"
	.string "out a STAFF hidden within!$"

FossilCave_Electric_Text_StrangeAmuletReacted:
	.string "The amulet within {PLAYER}'s bag\n"
	.string "flashed brightly.\p"
	.string "{PLAYER} took out the amulet\n"
	.string "inspected it.\p"
	.string "The closer you moved the amulet\n"
	.string "to the staff, the brighter it\l"
	.string "became.\p"
	.string "It seems to be reacting to the\n"
	.string "staff…\l" 
	.string "and something else…$"
