SurvivalIsland_Pokemart_MapScripts::
	.byte 0

SurvivalIsland_HomeBase_Pokemart_EventScript_BallClerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	goto_if_ge VAR_BALL_ITEMS_FOUND, 9, SurvivalIsland_HomeBase_Pokemart_Ultimate
	goto_if_ge VAR_BALL_ITEMS_FOUND, 6, SurvivalIsland_HomeBase_Pokemart_Greater
	goto_if_ge VAR_BALL_ITEMS_FOUND, 3, SurvivalIsland_HomeBase_Pokemart_Basic
	goto_if_le VAR_BALL_ITEMS_FOUND, 2, SurvivalIsland_HomeBase_Pokemart_ShopClosed
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

SurvivalIsland_HomeBase_Pokemart_EventScript_BattleClerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	goto_if_ge VAR_BATTLE_ITEMS_FOUND, 9, SurvivalIsland_HomeBase_Pokemart_Strong
	goto_if_ge VAR_BATTLE_ITEMS_FOUND, 6, SurvivalIsland_HomeBase_Pokemart_Normal
	goto_if_ge VAR_BATTLE_ITEMS_FOUND, 3, SurvivalIsland_HomeBase_Pokemart_Weak
	goto_if_le VAR_BATTLE_ITEMS_FOUND, 2, SurvivalIsland_HomeBase_Pokemart_ShopClosed
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end


SurvivalIsland_HomeBase_Pokemart_EventScript_BerryCook::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	goto_if_ge VAR_BERRY_ITEMS_FOUND, 9, SurvivalIsland_HomeBase_Pokemart_Meager
	goto_if_ge VAR_BERRY_ITEMS_FOUND, 6, SurvivalIsland_HomeBase_Pokemart_Filling
	goto_if_ge VAR_BERRY_ITEMS_FOUND, 3, SurvivalIsland_HomeBase_Pokemart_Barebones
	goto_if_le VAR_BERRY_ITEMS_FOUND, 2, SurvivalIsland_HomeBase_Pokemart_ShopClosed
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

SurvivalIsland_HomeBase_Pokemart_Ultimate:
	pokemart SurvivalIsland_HomeBase_Pokemart_UltimateShop
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

SurvivalIsland_HomeBase_Pokemart_UltimateShop:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_LEVEL_BALL
	.2byte ITEM_FAST_BALL
	.2byte ITEM_HEAVY_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_DREAM_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_QUICK_BALL
	release
	end

SurvivalIsland_HomeBase_Pokemart_Greater:
	pokemart SurvivalIsland_HomeBase_Pokemart_GreaterShop
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

SurvivalIsland_HomeBase_Pokemart_GreaterShop:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_FAST_BALL
	.2byte ITEM_HEAVY_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_QUICK_BALL
	release
	end

SurvivalIsland_HomeBase_Pokemart_Basic:
	pokemart SurvivalIsland_HomeBase_Pokemart_BasicShop
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

SurvivalIsland_HomeBase_Pokemart_BasicShop:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_QUICK_BALL
	release
	end

SurvivalIsland_HomeBase_Pokemart_ShopClosed:
	msgbox SurvivalIsland_HomeBase_Pokemart_Text_ShopClosed, MSGBOX_DEFAULT
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

SurvivalIsland_HomeBase_Pokemart_Strong:
	pokemart SurvivalIsland_HomeBase_Pokemart_StrongShop
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

SurvivalIsland_HomeBase_Pokemart_StrongShop:
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_SP_ATK
	.2byte ITEM_GUARD_SPEC
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_AWAKENING
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_REVIVE
	.2byte ITEM_MAX_REVIVE

SurvivalIsland_HomeBase_Pokemart_Normal:
	pokemart SurvivalIsland_HomeBase_Pokemart_NormalShop
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

SurvivalIsland_HomeBase_Pokemart_NormalShop:
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_SP_ATK
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_AWAKENING
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE

SurvivalIsland_HomeBase_Pokemart_Weak:
	pokemart SurvivalIsland_HomeBase_Pokemart_WeakShop
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

SurvivalIsland_HomeBase_Pokemart_WeakShop:
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_AWAKENING
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_PARALYZE_HEAL

SurvivalIsland_HomeBase_Pokemart_Meager:
	pokemart SurvivalIsland_HomeBase_Pokemart_MeagerShop
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

SurvivalIsland_HomeBase_Pokemart_MeagerShop:
	.2byte ITEM_CHERI_BERRY
	.2byte ITEM_CHESTO_BERRY
	.2byte ITEM_PECHA_BERRY
	.2byte ITEM_RAWST_BERRY
	.2byte ITEM_ASPEAR_BERRY
	.2byte ITEM_LEPPA_BERRY
	.2byte ITEM_ORAN_BERRY
	.2byte ITEM_PERSIM_BERRY
	.2byte ITEM_LUM_BERRY
	.2byte ITEM_SITRUS_BERRY
	.2byte ITEM_FIGY_BERRY
	.2byte ITEM_WIKI_BERRY
	.2byte ITEM_MAGO_BERRY
	.2byte ITEM_AGUAV_BERRY
	.2byte ITEM_IAPAPA_BERRY
	.2byte ITEM_OCCA_BERRY
	.2byte ITEM_PASSHO_BERRY
	.2byte ITEM_WACAN_BERRY
	.2byte ITEM_RINDO_BERRY
	.2byte ITEM_YACHE_BERRY
	.2byte ITEM_CHOPLE_BERRY
	.2byte ITEM_KEBIA_BERRY
	.2byte ITEM_SHUCA_BERRY
	.2byte ITEM_COBA_BERRY
	.2byte ITEM_PAYAPA_BERRY
	.2byte ITEM_TANGA_BERRY
	.2byte ITEM_CHARTI_BERRY
	.2byte ITEM_KASIB_BERRY
	.2byte ITEM_HABAN_BERRY
	.2byte ITEM_COLBUR_BERRY
	.2byte ITEM_BABIRI_BERRY
	.2byte ITEM_ROSELI_BERRY
	.2byte ITEM_LIECHI_BERRY
	.2byte ITEM_GANLON_BERRY
	.2byte ITEM_SALAC_BERRY
	.2byte ITEM_PETAYA_BERRY
	.2byte ITEM_APICOT_BERRY
	.2byte ITEM_LANSAT_BERRY
	.2byte ITEM_STARF_BERRY
	.2byte ITEM_ENIGMA_BERRY
	.2byte ITEM_MICLE_BERRY
	.2byte ITEM_CUSTAP_BERRY
	.2byte ITEM_JABOCA_BERRY
	.2byte ITEM_ROWAP_BERRY
	.2byte ITEM_KEE_BERRY
	.2byte ITEM_MARANGA_BERRY

SurvivalIsland_HomeBase_Pokemart_Filling:
	pokemart SurvivalIsland_HomeBase_Pokemart_FillingShop
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

SurvivalIsland_HomeBase_Pokemart_FillingShop:
	.2byte ITEM_CHERI_BERRY
	.2byte ITEM_CHESTO_BERRY
	.2byte ITEM_PECHA_BERRY
	.2byte ITEM_RAWST_BERRY
	.2byte ITEM_ASPEAR_BERRY
	.2byte ITEM_LEPPA_BERRY
	.2byte ITEM_ORAN_BERRY
	.2byte ITEM_PERSIM_BERRY
	.2byte ITEM_OCCA_BERRY
	.2byte ITEM_PASSHO_BERRY
	.2byte ITEM_WACAN_BERRY
	.2byte ITEM_RINDO_BERRY
	.2byte ITEM_YACHE_BERRY
	.2byte ITEM_CHOPLE_BERRY
	.2byte ITEM_KEBIA_BERRY
	.2byte ITEM_SHUCA_BERRY
	.2byte ITEM_COBA_BERRY
	.2byte ITEM_PAYAPA_BERRY
	.2byte ITEM_TANGA_BERRY
	.2byte ITEM_CHARTI_BERRY
	.2byte ITEM_KASIB_BERRY
	.2byte ITEM_HABAN_BERRY
	.2byte ITEM_COLBUR_BERRY
	.2byte ITEM_BABIRI_BERRY
	.2byte ITEM_ROSELI_BERRY
	.2byte ITEM_LIECHI_BERRY
	.2byte ITEM_MICLE_BERRY
	.2byte ITEM_CUSTAP_BERRY
	.2byte ITEM_JABOCA_BERRY
	.2byte ITEM_ROWAP_BERRY
	.2byte ITEM_KEE_BERRY
	.2byte ITEM_MARANGA_BERRY

SurvivalIsland_HomeBase_Pokemart_Barebones:
	pokemart SurvivalIsland_HomeBase_Pokemart_BareBonesShop
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

SurvivalIsland_HomeBase_Pokemart_BareBonesShop:
	.2byte ITEM_CHERI_BERRY
	.2byte ITEM_CHESTO_BERRY
	.2byte ITEM_PECHA_BERRY
	.2byte ITEM_RAWST_BERRY
	.2byte ITEM_ASPEAR_BERRY
	.2byte ITEM_LEPPA_BERRY
	.2byte ITEM_ORAN_BERRY
	.2byte ITEM_PERSIM_BERRY

SurvivalIsland_HomeBase_Pokemart_EventScript_VendingMachine::
	lockall
	message LilycoveCity_DepartmentStoreRooftop_Text_WhichDrinkWouldYouLike
	waitmessage
	showmoneybox 0, 0
	goto_if_defeated ISLAND_BOSS_RODERICK_EASY, SurvivalIsland_HomeBase_Pokemart_EventScript_ChooseDrink_Expanded2
	goto_if_defeated ISLAND_BOSS_RODERICK_NORMAL, SurvivalIsland_HomeBase_Pokemart_EventScript_ChooseDrink_Expanded2
	goto_if_defeated ISLAND_BOSS_RODERICK_HARD, SurvivalIsland_HomeBase_Pokemart_EventScript_ChooseDrink_Expanded2
	goto_if_defeated ISLAND_BOSS_RODERICK_ULTIMATE, SurvivalIsland_HomeBase_Pokemart_EventScript_ChooseDrink_Expanded2
	goto_if_defeated ISLAND_BOSS_JOSHUA_EASY, SurvivalIsland_HomeBase_Pokemart_EventScript_ChooseDrink_Expanded
	goto_if_defeated ISLAND_BOSS_JOSHUA_EASY, SurvivalIsland_HomeBase_Pokemart_EventScript_ChooseDrink_Expanded
	goto_if_defeated ISLAND_BOSS_JOSHUA_EASY, SurvivalIsland_HomeBase_Pokemart_EventScript_ChooseDrink_Expanded
	goto_if_defeated ISLAND_BOSS_JOSHUA_EASY, SurvivalIsland_HomeBase_Pokemart_EventScript_ChooseDrink_Expanded
	goto SurvivalIsland_HomeBase_Pokemart_EventScript_ChooseDrink
	end

SurvivalIsland_HomeBase_Pokemart_EventScript_ChooseDrink::
	multichoice 16, 0, MULTI_VENDING_MACHINE_1, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, SurvivalIsland_HomeBase_Pokemart_EventScript_BerryJuice
	msgbox SurvivalIsland_HomeBase_Pokemart_Text_DecidedAgainstBuyingDrink, MSGBOX_DEFAULT
	goto SurvivalIsland_HomeBase_Pokemart_EventScript_ExitVendingMachine
	end

SurvivalIsland_HomeBase_Pokemart_EventScript_ChooseDrink_Expanded::
	multichoice 16, 0, MULTI_VENDING_MACHINE_2, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, SurvivalIsland_HomeBase_Pokemart_EventScript_BerryJuice
	case 1, SurvivalIsland_HomeBase_Pokemart_EventScript_FreshWater
	case 2, SurvivalIsland_HomeBase_Pokemart_EventScript_SodaPop
	case 3, SurvivalIsland_HomeBase_Pokemart_EventScript_Lemonade
	msgbox SurvivalIsland_HomeBase_Pokemart_Text_DecidedAgainstBuyingDrink, MSGBOX_DEFAULT
	goto SurvivalIsland_HomeBase_Pokemart_EventScript_ExitVendingMachine
	end

SurvivalIsland_HomeBase_Pokemart_EventScript_ChooseDrink_Expanded2::
	multichoice 16, 0, MULTI_VENDING_MACHINE_3, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, SurvivalIsland_HomeBase_Pokemart_EventScript_BerryJuice
	case 1, SurvivalIsland_HomeBase_Pokemart_EventScript_FreshWater
	case 2, SurvivalIsland_HomeBase_Pokemart_EventScript_SodaPop
	case 3, SurvivalIsland_HomeBase_Pokemart_EventScript_Lemonade
	case 4, SurvivalIsland_HomeBase_Pokemart_EventScript_MooMooMilk
	msgbox SurvivalIsland_HomeBase_Pokemart_Text_DecidedAgainstBuyingDrink, MSGBOX_DEFAULT
	goto SurvivalIsland_HomeBase_Pokemart_EventScript_ExitVendingMachine
	end

SurvivalIsland_HomeBase_Pokemart_EventScript_BerryJuice::
	setvar VAR_TEMP_0, ITEM_BERRY_JUICE
	goto SurvivalIsland_HomeBase_Pokemart_EventScript_TryBuyDrink
	end

SurvivalIsland_HomeBase_Pokemart_EventScript_FreshWater::
	setvar VAR_TEMP_0, ITEM_FRESH_WATER
	goto SurvivalIsland_HomeBase_Pokemart_EventScript_TryBuyDrink
	end

SurvivalIsland_HomeBase_Pokemart_EventScript_SodaPop::
	setvar VAR_TEMP_0, ITEM_SODA_POP
	goto SurvivalIsland_HomeBase_Pokemart_EventScript_TryBuyDrink
	end

SurvivalIsland_HomeBase_Pokemart_EventScript_Lemonade::
	setvar VAR_TEMP_0, ITEM_LEMONADE
	goto SurvivalIsland_HomeBase_Pokemart_EventScript_TryBuyDrink
	end

SurvivalIsland_HomeBase_Pokemart_EventScript_MooMooMilk::
	setvar VAR_TEMP_0, ITEM_MOOMOO_MILK
	goto SurvivalIsland_HomeBase_Pokemart_EventScript_TryBuyDrink
	end


SurvivalIsland_HomeBase_Pokemart_EventScript_CheckMoneyBerryJuice::
	checkmoney 50
	return

SurvivalIsland_HomeBase_Pokemart_EventScript_CheckMoneyFreshWater::
	checkmoney 200
	return

SurvivalIsland_HomeBase_Pokemart_EventScript_CheckMoneySodaPop::
	checkmoney 300
	return

SurvivalIsland_HomeBase_Pokemart_EventScript_CheckMoneyLemonade::
	checkmoney 350
	return

SurvivalIsland_HomeBase_Pokemart_EventScript_CheckMoneyMoomooMilk::
	checkmoney 500
	return

SurvivalIsland_HomeBase_Pokemart_EventScript_RemoveMoneyBerryJuice::
	removemoney 50
	return

SurvivalIsland_HomeBase_Pokemart_EventScript_RemoveMoneyFreshWater::
	removemoney 200
	return

SurvivalIsland_HomeBase_Pokemart_EventScript_RemoveMoneySodaPop::
	removemoney 300
	return

SurvivalIsland_HomeBase_Pokemart_EventScript_RemoveMoneyLemonade::
	removemoney 350
	return

SurvivalIsland_HomeBase_Pokemart_EventScript_RemoveMoneyMoomooMilk::
	removemoney 350
	return

SurvivalIsland_HomeBase_Pokemart_EventScript_TryBuyDrink::
	call_if_eq VAR_TEMP_1, 0, SurvivalIsland_HomeBase_Pokemart_EventScript_CheckMoneyBerryJuice
	call_if_eq VAR_TEMP_1, 1, SurvivalIsland_HomeBase_Pokemart_EventScript_CheckMoneyFreshWater
	call_if_eq VAR_TEMP_1, 2, SurvivalIsland_HomeBase_Pokemart_EventScript_CheckMoneySodaPop
	call_if_eq VAR_TEMP_1, 3, SurvivalIsland_HomeBase_Pokemart_EventScript_CheckMoneyLemonade
	call_if_eq VAR_TEMP_1, 4, SurvivalIsland_HomeBase_Pokemart_EventScript_CheckMoneyMoomooMilk
	goto_if_eq VAR_RESULT, FALSE, SurvivalIsland_HomeBase_Pokemart_EventScript_NotEnoughMoneyForDrink
	checkitemspace VAR_TEMP_0
	goto_if_eq VAR_RESULT, FALSE, SurvivalIsland_HomeBase_Pokemart_EventScript_NoRoomForDrink
	call_if_eq VAR_TEMP_1, 0, SurvivalIsland_HomeBase_Pokemart_EventScript_RemoveMoneyBerryJuice
	call_if_eq VAR_TEMP_1, 1, SurvivalIsland_HomeBase_Pokemart_EventScript_RemoveMoneyFreshWater
	call_if_eq VAR_TEMP_1, 2, SurvivalIsland_HomeBase_Pokemart_EventScript_RemoveMoneySodaPop
	call_if_eq VAR_TEMP_1, 3, SurvivalIsland_HomeBase_Pokemart_EventScript_RemoveMoneyLemonade
	call_if_eq VAR_TEMP_1, 4, SurvivalIsland_HomeBase_Pokemart_EventScript_RemoveMoneyMoomooMilk
	updatemoneybox
	bufferitemname STR_VAR_1, VAR_TEMP_0
	playse SE_VEND
	msgbox LilycoveCity_DepartmentStoreRooftop_Text_CanOfDrinkDroppedDown, MSGBOX_DEFAULT
	additem VAR_TEMP_0
	bufferitemname STR_VAR_2, VAR_TEMP_0
	bufferstdstring STR_VAR_3, STDSTRING_ITEMS
	msgbox gText_PutItemInPocket, MSGBOX_DEFAULT
	random 64  @ 1/64 chance of an additional drink dropping
	goto_if_ne VAR_RESULT, 0, SurvivalIsland_HomeBase_Pokemart_EventScript_ChooseNewDrink
	checkitemspace VAR_TEMP_0
	goto_if_eq VAR_RESULT, FALSE, SurvivalIsland_HomeBase_Pokemart_EventScript_NoRoomForDrink
	playse SE_VEND
	msgbox LilycoveCity_DepartmentStoreRooftop_Text_ExtraCanOfDrinkDroppedDown, MSGBOX_DEFAULT
	additem VAR_TEMP_0
	bufferitemname STR_VAR_2, VAR_TEMP_0
	bufferstdstring STR_VAR_3, STDSTRING_ITEMS
	msgbox gText_PutItemInPocket, MSGBOX_DEFAULT
	random 64  @ 1/64 * the prev 1/64 chance of a third additional drink dropping, ~ 0.02% chance
	goto_if_ne VAR_RESULT, 0, SurvivalIsland_HomeBase_Pokemart_EventScript_ChooseNewDrink
	checkitemspace VAR_TEMP_0
	goto_if_eq VAR_RESULT, 0, SurvivalIsland_HomeBase_Pokemart_EventScript_NoRoomForDrink
	playse SE_VEND
	msgbox LilycoveCity_DepartmentStoreRooftop_Text_ExtraCanOfDrinkDroppedDown, MSGBOX_DEFAULT
	additem VAR_TEMP_0
	bufferitemname STR_VAR_2, VAR_TEMP_0
	bufferstdstring STR_VAR_3, STDSTRING_ITEMS
	msgbox gText_PutItemInPocket, MSGBOX_DEFAULT
	goto SurvivalIsland_HomeBase_Pokemart_EventScript_ChooseNewDrink
	end

SurvivalIsland_HomeBase_Pokemart_EventScript_ChooseNewDrink::
	message LilycoveCity_DepartmentStoreRooftop_Text_WhichDrinkWouldYouLike
	waitmessage
	goto_if_defeated ISLAND_BOSS_RODERICK_EASY, SurvivalIsland_HomeBase_Pokemart_EventScript_ChooseDrink_Expanded2
	goto_if_defeated ISLAND_BOSS_RODERICK_NORMAL, SurvivalIsland_HomeBase_Pokemart_EventScript_ChooseDrink_Expanded2
	goto_if_defeated ISLAND_BOSS_RODERICK_HARD, SurvivalIsland_HomeBase_Pokemart_EventScript_ChooseDrink_Expanded2
	goto_if_defeated ISLAND_BOSS_RODERICK_ULTIMATE, SurvivalIsland_HomeBase_Pokemart_EventScript_ChooseDrink_Expanded2
	goto_if_defeated ISLAND_BOSS_JOSHUA_EASY, SurvivalIsland_HomeBase_Pokemart_EventScript_ChooseDrink_Expanded
	goto_if_defeated ISLAND_BOSS_JOSHUA_EASY, SurvivalIsland_HomeBase_Pokemart_EventScript_ChooseDrink_Expanded
	goto_if_defeated ISLAND_BOSS_JOSHUA_EASY, SurvivalIsland_HomeBase_Pokemart_EventScript_ChooseDrink_Expanded
	goto_if_defeated ISLAND_BOSS_JOSHUA_EASY, SurvivalIsland_HomeBase_Pokemart_EventScript_ChooseDrink_Expanded
	goto SurvivalIsland_HomeBase_Pokemart_EventScript_ChooseDrink

	end

SurvivalIsland_HomeBase_Pokemart_EventScript_NotEnoughMoneyForDrink::
	msgbox LilycoveCity_DepartmentStoreRooftop_Text_NotEnoughMoney, MSGBOX_DEFAULT
	goto SurvivalIsland_HomeBase_Pokemart_EventScript_ExitVendingMachine
	end

SurvivalIsland_HomeBase_Pokemart_EventScript_NoRoomForDrink::
	msgbox gText_TheBagIsFull, MSGBOX_DEFAULT
	goto SurvivalIsland_HomeBase_Pokemart_EventScript_ExitVendingMachine
	end

SurvivalIsland_HomeBase_Pokemart_EventScript_ExitVendingMachine::
	hidemoneybox
	releaseall
	end

SurvivalIsland_HomeBase_Pokemart_Text_DecidedAgainstBuyingDrink:
	.string "Decided against buying a drink.$"


SurvivalIsland_HomeBase_Pokemart_Text_ShopClosed:
	.string "Sorry, due to the lack of\n"
	.string "neccessary research and productive\l"
	.string "materials, this shop is closed.$"

