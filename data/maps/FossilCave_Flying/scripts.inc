.set LOCALID_HORN_FOSSIL, 1

FossilCave_Flying_MapScripts::
	.byte 0

FossilCave_Flying_EventScript_StrangeGraveStone::
	lock
	faceplayer
	goto_if_unset FLAG_STAFF_OF_MAGIC_PICKED_UP FossilCave_Flying_EventScript_StrangeGraveStone_Part2
	msgbox FossilCave_Flying_Text_GraveWasBarren MSGBOX_AUTOCLOSE
	release
	end

FossilCave_Flying_EventScript_MessageSign::
	lock
	faceplayer
	msgbox FossilCave_Flying_Text_HereLieTheDead MSGBOX_NPC
	release
	end

FossilCave_Flying_EventScript_StrangeGraveStone_Part2::
	msgbox FossilCave_Flying_Text_StrangeGraveIsDifferentlyColored, MSGBOX_DEFAULT
	giveitem ITEM_STAFF_OF_MAGIC
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	closemessage
	goto_if_eq VAR_RESULT, TRUE, FossilCave_Flying_EventScript_StrangeGraveStone_Part3
	release
	end

FossilCave_Flying_EventScript_StrangeGraveStone_Part3::
	msgbox FossilCave_Flying_Text_StrangeAmuletReacted MSGBOX_DEFAULT
	setflag FLAG_STAFF_OF_MAGIC_PICKED_UP
	release
	end	



FossilCave_Flying_EventScript_HornFossil::
	lock
	faceplayer
	msgbox FossilCave_Flying_Text_TakeHornFossil, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FossilCave_Flying_EventScript_LeaveHornFossil
	giveitem ITEM_FEATHER_FOSSIL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	closemessage
	setflag FLAG_HIDE_FOSSIL_CAVE_ICE_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_FIRE_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_WATER_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_ELECTRIC_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_GROUND_FOSSIL
	setflag FLAG_HIDE_FOSSIL_CAVE_FLYING_FOSSIL
	removeobject LOCALID_HORN_FOSSIL
	delay 30
	goto FossilCave_Flying_EventScript_CollapseFossilCave
	end

FossilCave_Flying_EventScript_LeaveHornFossil::
	msgbox FossilCave_Flying_Text_LeftHornFossilAlone, MSGBOX_DEFAULT
	release
	end


FossilCave_Flying_EventScript_CollapseFossilCave::
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


FossilCave_Flying_Text_HereLieTheDead:
	.string "In loving memory…$"


FossilCave_Flying_Text_StrangeAmuletReacted:
	.string "The amulet within {PLAYER}'s bag\n"
	.string "flashed brightly.\p"
	.string "{PLAYER} took out the amulet\n"
	.string "inspected it.\p"
	.string "The closer you moved the amulet\n"
	.string "to the halo, the brighter it\l"
	.string "became.\p"
	.string "It seems to be reacting to the\n"
	.string "Halo…\l" 
	.string "and something else…$"


FossilCave_Flying_Text_StrangeGraveIsDifferentlyColored:
	.string "This strange gravestone appears\n"
	.string "differently colored than the.\l"
	.string "other gravestones..\p"
	.string "{PLAYER} examined the gravestone\n"
	.string "closer and discovered a light from\l"
	.string "within the grave.\p"
	.string "{PLAYER} opened the gravetomb and\n"
	.string "found a HALO within!$"

FossilCave_Flying_Text_GraveWasBarren:
	.string "This strange gravestone appears\n"
	.string "differently colored than the.\l"
	.string "other gravestones..\p"
	.string "{PLAYER} examined the gravestone\n"
	.string "and found it was barren.$"


FossilCave_Flying_Text_TakeHornFossil:
	.string "You found the HORN FOSSIL.\p"
	.string "If this FOSSIL is taken, the ground\n"
	.string "around it will likely collapse…\p"
	.string "Take the HORN FOSSIL anyway?$"

FossilCave_Flying_Text_LeftHornFossilAlone:
	.string "{PLAYER} left the HORN FOSSIL alone.$"

