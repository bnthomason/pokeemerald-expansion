FossilCave_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, FossilCave_SetHoleWarp
	.byte 0

FossilCave_SetHoleWarp:
	setstepcallback STEP_CB_CRACKED_FLOOR
	setholewarp MAP_FOSSIL_CAVE_STEEL
	end

FossilCave_EventScript_SlideEvoItemUnderRock::
	lock
	faceplayer
	goto_if_unset FLAG_SLIDE_EVO_UNDERROCK_PICKED_UP, FossilCave_EventScript_GiveSlideItem
	msgbox FossilCave_Text_RockWasBareEmpty MSGBOX_NPC
	release
	end

FossilCave_EventScript_GiveSlideItem::
	lock
	faceplayer
	msgbox FossilCave_Text_FoundAStrangeObjectUndertheRock MSGBOX_DEFAULT
	giveitem ITEM_SLIDE_AMULET
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	closemessage
	goto_if_eq VAR_RESULT, TRUE, FossilCave_EventScript_SlideItemMessage
	release
	end

FossilCave_EventScript_SlideItemMessage::
	msgbox FossilCave_Text_TheObjectYouJustPickedUp MSGBOX_AUTOCLOSE
	setflag FLAG_SLIDE_EVO_UNDERROCK_PICKED_UP
	release
	end	

FossilCave_Text_FoundAStrangeObjectUndertheRock:
	.string "We checked underneath the rock\n"
	.string "and found a strange object under\l"
	.string "it.$"

FossilCave_Text_TheObjectYouJustPickedUp:
	.string "The object you just picked up.\n"
	.string "briefly flashed with power and\l"
	.string "then faded.\p"
	.string "Perhaps it's reacting to\n"
	.string "something nearby…$"

FossilCave_Text_RockWasBareEmpty:
	.string "We checked underneath the rock.\p"
	.string "But the rock was bare empty…$"
