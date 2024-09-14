Area1_Zone3_MapScripts::
	.byte 0

Area1_HiddenItem_Antidote::
giveitem ITEM_ANTIDOTE
addvar VAR_BATTLE_ITEMS_FOUND, 1
setflag FLAG_ITEM_AREA1_ANTIDOTE
