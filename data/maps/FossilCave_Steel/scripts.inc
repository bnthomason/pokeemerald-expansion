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

FossilCave_Steel_EventScript_DoSparkle::
	setvar VAR_0x8004, 10  @ x
	setvar VAR_0x8005, 33  @ y
	call FossilCave_Steel_EventScript_DoSparkle1
	return

FossilCave_Steel_EventScript_DoSparkle1::
	setvar VAR_0x8006, 0
	dofieldeffectsparkle VAR_0x8004, VAR_0x8005, VAR_0x8006
	waitfieldeffect FLDEFF_SPARKLE
	return


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

FossilCave_Steel_EventScript_GroundFlashes_Part1::
	lock
	faceplayer
	goto_if_unset FLAG_CLOAK_OF_MASTERMIND_PICKED_UP FossilCave_Steel_EventScript_GroundFlashes_Part2
	msgbox FossilCave_Steel_Text_GroundFlashesNothingThere MSGBOX_AUTOCLOSE
	release
	end

FossilCave_Steel_EventScript_GroundFlashes_Part2::
	msgbox FossilCave_Steel_Text_GroundFlashesSparkles, MSGBOX_DEFAULT
	giveitem ITEM_CLOAK_OF_MASTERMIND
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	closemessage
	goto_if_eq VAR_RESULT, TRUE, FossilCave_Steel_EventScript_GroundFlashes_Part3
	release
	end

FossilCave_Steel_EventScript_GroundFlashes_Part3::
	msgbox FossilCave_Steel_Text_StrangeAmuletReacted MSGBOX_DEFAULT
	setflag FLAG_CLOAK_OF_MASTERMIND_PICKED_UP
	release
	end	

FossilCave_Steel_Text_GroundFlashesNothingThere:
	.string "The ground flashes right here.\p"
	.string "{PLAYER} examined the ground\p"
	.string "But there was nothing there…$"


FossilCave_Steel_Text_GroundFlashesSparkles:
	.string "The ground flashes right here.\p"
	.string "{PLAYER} examined the ground\n"
	.string "and found a black cloak hidden.\l"
	.string "in the dirt.\p"
	.string "{PLAYER} pulled the cloak\n"
	.string "out of the dirt.$"

FossilCave_Steel_Text_StrangeAmuletReacted:
	.string "The amulet within {PLAYER}'s bag\n"
	.string "flashed brightly.\p"
	.string "{PLAYER} took out the amulet\n"
	.string "inspected it.\p"
	.string "The closer you moved the amulet\n"
	.string "to the cloak, the brighter it\l"
	.string "became.\p"
	.string "It seems to be reacting to the\n"
	.string "cloak…\l"
	.string "and something else…$" 

FossilCave_Steel_Text_TakeIronFossil:
	.string "You found the IRON FOSSIL.\p"
	.string "If this FOSSIL is taken, the ground\n"
	.string "around it will likely collapse…\p"
	.string "Take the IRON FOSSIL anyway?$"

FossilCave_Steel_Text_LeftIronFossilAlone:
	.string "{PLAYER} left the IRON FOSSIL alone.$"