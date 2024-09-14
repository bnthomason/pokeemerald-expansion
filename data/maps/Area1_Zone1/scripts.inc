Area1_Zone1_MapScripts::
	.byte 0

Area1_HiddenItem_Potion::
	giveitem ITEM_POTION
	addvar VAR_BATTLE_ITEMS_FOUND, 1
	setflag FLAG_ITEM_AREA1_POTION

Area1_HiddenItem_Pokeball::
	giveitem ITEM_POKE_BALL
	addvar VAR_BALL_ITEMS_FOUND, 1
	setflag FLAG_ITEM_AREA1_POKEBALL
