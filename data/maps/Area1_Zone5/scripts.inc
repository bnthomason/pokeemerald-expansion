Area1_Zone5_MapScripts::
	.byte 0

Area1_HiddenItem_Repeat_Ball::
giveitem ITEM_REPEAT_BALL
addvar VAR_BALL_ITEMS_FOUND, 1
setflag FLAG_ITEM_AREA1_REPEAT_BALL

Area1_HiddenItem_Quick_Ball::
giveitem ITEM_QUICK_BALL
addvar VAR_BALL_ITEMS_FOUND, 1
setflag FLAG_ITEM_AREA1_QUICK_BALL
