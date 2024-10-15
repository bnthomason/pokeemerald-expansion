.set LOCALID_FOSSIL_SCIENTIST, 5

RustboroCity_DevonCorp_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_DevonCorp_2F_OnTransition
	.byte 0

RustboroCity_DevonCorp_2F_OnTransition:
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	end

RustboroCity_DevonCorp_2F_EventScript_SetFossilReady::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 2
	return

RustboroCity_DevonCorp_2F_EventScript_TalkToPokemonScientist::
	lock
	faceplayer
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	msgbox RustboroCity_DevonCorp_2F_Text_DeviceForTalkingToPokemon, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_BallScientist::
	lock
	faceplayer
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	goto_if_set FLAG_MET_DEVON_EMPLOYEE, RustboroCity_DevonCorp_2F_EventScript_DevelopedBalls
	msgbox RustboroCity_DevonCorp_2F_Text_DevelopingNewBalls, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_DevelopedBalls::
	msgbox RustboroCity_DevonCorp_2F_Text_WeFinallyMadeNewBalls, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_PokenavScientist::
	lock
	faceplayer
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	goto_if_set FLAG_RECEIVED_POKENAV, RustboroCity_DevonCorp_2F_EventScript_HasPokenav
	msgbox RustboroCity_DevonCorp_2F_Text_IMadePokenav, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_HasPokenav::
	msgbox RustboroCity_DevonCorp_2F_Text_WowThatsAPokenav, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_PokemonDreamsScientist::
	lock
	faceplayer
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	msgbox RustboroCity_DevonCorp_2F_Text_DeviceToVisualizePokemonDreams, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_FossilScientist::
	lock
	faceplayer
	goto_if_eq VAR_FOSSIL_RESURRECTION_STATE, 2, RustboroCity_DevonCorp_2F_EventScript_FossilMonReady
	goto_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_StillRegenerating
	msgbox RustboroCity_DevonCorp_2F_Text_DevelopDeviceToResurrectFossils, MSGBOX_DEFAULT
	checkitem ITEM_ROOT_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_NoticeRootFossil
	checkitem ITEM_CLAW_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_NoticeClawFossil
	checkitem ITEM_HORN_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_NoticeHornFossil
	checkitem ITEM_HIDE_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_NoticeHideFossil
	checkitem ITEM_BOLT_FOSSIL @	checkitem ITEM_HIDE_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_NoticeBoltFossil	@	goto_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_NoticeHoofFossil
	checkitem ITEM_SCALE_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_NoticeScaleFossil
	checkitem ITEM_CLAW_FOSSIL_2
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_NoticeClawFossil2
	checkitem ITEM_FEATHER_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_NoticeFeatherFossil
	checkitem ITEM_STEEL_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_NoticeIronFossil
	release
	end

@ This whole section has needless duplication and could be condensed considerably
RustboroCity_DevonCorp_2F_EventScript_NoticeRootFossil::
	closemessage
	playse SE_PIN
	applymovement LOCALID_FOSSIL_SCIENTIST, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_FOSSIL_SCIENTIST, Common_Movement_Delay48
	waitmovement 0
	msgbox RustboroCity_DevonCorp_2F_Text_WantToBringFossilBackToLife, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_DeclineGiveFossil
	checkitem ITEM_CLAW_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_ChooseFossil
	goto RustboroCity_DevonCorp_2F_EventScript_GiveRootFossil
	end

RustboroCity_DevonCorp_2F_EventScript_GiveRootFossil::
	bufferitemname STR_VAR_1, ITEM_ROOT_FOSSIL
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_ROOT_FOSSIL
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 1
	release
	end

RustboroCity_DevonCorp_2F_EventScript_NoticeClawFossil::
	closemessage
	playse SE_PIN
	applymovement LOCALID_FOSSIL_SCIENTIST, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_FOSSIL_SCIENTIST, Common_Movement_Delay48
	waitmovement 0
	msgbox RustboroCity_DevonCorp_2F_Text_WantToBringFossilBackToLife, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_DeclineGiveFossil
	checkitem ITEM_ROOT_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_ChooseFossil
	goto RustboroCity_DevonCorp_2F_EventScript_GiveClawFossil
	end

RustboroCity_DevonCorp_2F_EventScript_GiveClawFossil::
	bufferitemname STR_VAR_1, ITEM_CLAW_FOSSIL
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_CLAW_FOSSIL
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 2
	release
	end


@ Dracoceros

RustboroCity_DevonCorp_2F_EventScript_NoticeHornFossil::
	closemessage
	playse SE_PIN
	applymovement LOCALID_FOSSIL_SCIENTIST, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_FOSSIL_SCIENTIST, Common_Movement_Delay48
	waitmovement 0
	msgbox RustboroCity_DevonCorp_2F_Text_WantToBringFossilBackToLife, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_DeclineGiveFossil
	goto RustboroCity_DevonCorp_2F_EventScript_GiveHornFossil
	end

RustboroCity_DevonCorp_2F_EventScript_GiveHornFossil::
	bufferitemname STR_VAR_1, ITEM_HORN_FOSSIL
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_HORN_FOSSIL
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 3
	release
	end

@ Nebugon

RustboroCity_DevonCorp_2F_EventScript_NoticeHideFossil::
	closemessage
	playse SE_PIN
	applymovement LOCALID_FOSSIL_SCIENTIST, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_FOSSIL_SCIENTIST, Common_Movement_Delay48
	waitmovement 0
	msgbox RustboroCity_DevonCorp_2F_Text_WantToBringFossilBackToLife, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_DeclineGiveFossil
	goto RustboroCity_DevonCorp_2F_EventScript_GiveHideFossil
	end

RustboroCity_DevonCorp_2F_EventScript_GiveHideFossil::
	bufferitemname STR_VAR_1, ITEM_HIDE_FOSSIL
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_HIDE_FOSSIL
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 4
	release
	end

@ Kirin

RustboroCity_DevonCorp_2F_EventScript_NoticeBoltFossil:: @RustboroCity_DevonCorp_2F_EventScript_NoticeHoofFossil::
	closemessage
	playse SE_PIN
	applymovement LOCALID_FOSSIL_SCIENTIST, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_FOSSIL_SCIENTIST, Common_Movement_Delay48
	waitmovement 0
	msgbox RustboroCity_DevonCorp_2F_Text_WantToBringFossilBackToLife, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_DeclineGiveFossil
	goto RustboroCity_DevonCorp_2F_EventScript_GiveBoltFossil @			goto RustboroCity_DevonCorp_2F_EventScript_GiveHoofFossil
	end

RustboroCity_DevonCorp_2F_EventScript_GiveBoltFossil:: @ RustboroCity_DevonCorp_2F_EventScript_GiveHoofFossil::
	bufferitemname STR_VAR_1, ITEM_BOLT_FOSSIL @	bufferitemname STR_VAR_1, ITEM_HOOF_FOSSIL
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_BOLT_FOSSIL
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 5
	release
	end

@ Faerial

RustboroCity_DevonCorp_2F_EventScript_NoticeScaleFossil::
	closemessage
	playse SE_PIN
	applymovement LOCALID_FOSSIL_SCIENTIST, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_FOSSIL_SCIENTIST, Common_Movement_Delay48
	waitmovement 0
	msgbox RustboroCity_DevonCorp_2F_Text_WantToBringFossilBackToLife, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_DeclineGiveFossil
	goto RustboroCity_DevonCorp_2F_EventScript_GiveScaleFossil
	end

RustboroCity_DevonCorp_2F_EventScript_GiveScaleFossil::
	bufferitemname STR_VAR_1, ITEM_SCALE_FOSSIL
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_SCALE_FOSSIL
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 6
	release
	end

@ Impyrian

RustboroCity_DevonCorp_2F_EventScript_NoticeClawFossil2::
	closemessage
	playse SE_PIN
	applymovement LOCALID_FOSSIL_SCIENTIST, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_FOSSIL_SCIENTIST, Common_Movement_Delay48
	waitmovement 0
	msgbox RustboroCity_DevonCorp_2F_Text_WantToBringFossilBackToLife, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_DeclineGiveFossil
	goto RustboroCity_DevonCorp_2F_EventScript_GiveClawFossil2
	end

RustboroCity_DevonCorp_2F_EventScript_GiveClawFossil2::
	bufferitemname STR_VAR_1, ITEM_CLAW_FOSSIL_2
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_CLAW_FOSSIL_2
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 7
	release
	end

@ Wintego

RustboroCity_DevonCorp_2F_EventScript_NoticeFeatherFossil::
	closemessage
	playse SE_PIN
	applymovement LOCALID_FOSSIL_SCIENTIST, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_FOSSIL_SCIENTIST, Common_Movement_Delay48
	waitmovement 0
	msgbox RustboroCity_DevonCorp_2F_Text_WantToBringFossilBackToLife, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_DeclineGiveFossil
	goto RustboroCity_DevonCorp_2F_EventScript_GiveFeatherFossil
	end

RustboroCity_DevonCorp_2F_EventScript_GiveFeatherFossil::
	bufferitemname STR_VAR_1, ITEM_FEATHER_FOSSIL
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_FEATHER_FOSSIL
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 7
	release
	end

@ Prototype

RustboroCity_DevonCorp_2F_EventScript_NoticeIronFossil::
	closemessage
	playse SE_PIN
	applymovement LOCALID_FOSSIL_SCIENTIST, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_FOSSIL_SCIENTIST, Common_Movement_Delay48
	waitmovement 0
	msgbox RustboroCity_DevonCorp_2F_Text_WantToBringFossilBackToLife, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_DeclineGiveFossil
	goto RustboroCity_DevonCorp_2F_EventScript_GiveIronFossil
	end

RustboroCity_DevonCorp_2F_EventScript_GiveIronFossil::
	bufferitemname STR_VAR_1, ITEM_STEEL_FOSSIL
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem ITEM_STEEL_FOSSIL
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 9
	release
	end	

RustboroCity_DevonCorp_2F_EventScript_DeclineGiveFossil::
	msgbox RustboroCity_DevonCorp_2F_Text_OhIsThatSo, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_StillRegenerating::
	msgbox RustboroCity_DevonCorp_2F_Text_FossilRegeneratorTakesTime, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_FossilMonReady::
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 1, RustboroCity_DevonCorp_2F_EventScript_LileepReady
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 2, RustboroCity_DevonCorp_2F_EventScript_AnorithReady
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 3, RustboroCity_DevonCorp_2F_EventScript_DracocerosReady
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 4, RustboroCity_DevonCorp_2F_EventScript_NebugonReady
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 5, RustboroCity_DevonCorp_2F_EventScript_KirinReady
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 6, RustboroCity_DevonCorp_2F_EventScript_FaerialReady
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 7, RustboroCity_DevonCorp_2F_EventScript_ImpyrianReady
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 8, RustboroCity_DevonCorp_2F_EventScript_WintegoReady
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 9, RustboroCity_DevonCorp_2F_EventScript_PrototypeReady
	end

RustboroCity_DevonCorp_2F_EventScript_LileepReady::
	bufferspeciesname STR_VAR_2, SPECIES_LILEEP
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	goto RustboroCity_DevonCorp_2F_EventScript_ReceiveLileep
	end

RustboroCity_DevonCorp_2F_EventScript_AnorithReady::
	bufferspeciesname STR_VAR_2, SPECIES_ANORITH
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	goto RustboroCity_DevonCorp_2F_EventScript_ReceiveAnorith
	end

RustboroCity_DevonCorp_2F_EventScript_DracocerosReady::
	bufferspeciesname STR_VAR_2, SPECIES_DRACOCEROS_HOLY_CHILD
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	goto RustboroCity_DevonCorp_2F_EventScript_ReceiveDracoceros
	end

RustboroCity_DevonCorp_2F_EventScript_NebugonReady::
	bufferspeciesname STR_VAR_2, SPECIES_NEBUGON_TANK_CHILD
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	goto RustboroCity_DevonCorp_2F_EventScript_ReceiveNebugon
	end

RustboroCity_DevonCorp_2F_EventScript_KirinReady::
	bufferspeciesname STR_VAR_2, SPECIES_KIRIN_MAGE_CHILD
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	goto RustboroCity_DevonCorp_2F_EventScript_ReceiveKirin
	end

RustboroCity_DevonCorp_2F_EventScript_FaerialReady::
	bufferspeciesname STR_VAR_2, SPECIES_FAERIAL_BEAUTY_CHILD
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	goto RustboroCity_DevonCorp_2F_EventScript_ReceiveFaerial
	end

RustboroCity_DevonCorp_2F_EventScript_ImpyrianReady::
	bufferspeciesname STR_VAR_2, SPECIES_IMPYRIAN_IMPERIAL_CHILD
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	goto RustboroCity_DevonCorp_2F_EventScript_ReceiveImpyrian
	end

RustboroCity_DevonCorp_2F_EventScript_WintegoReady::
	bufferspeciesname STR_VAR_2, SPECIES_WINTEGO_WINTER_CHILD
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	goto RustboroCity_DevonCorp_2F_EventScript_ReceiveWintego
	end

RustboroCity_DevonCorp_2F_EventScript_PrototypeReady::
	bufferspeciesname STR_VAR_2, SPECIES_PROTOTYPE_VILLAIN_CHILD
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	goto RustboroCity_DevonCorp_2F_EventScript_ReceivePrototype
	end

@ Lileep

RustboroCity_DevonCorp_2F_EventScript_ReceiveLileep::
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_LILEEP
	givemon SPECIES_LILEEP, 20
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveLileepParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveLileepPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveLileepParty::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedLileepFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_FinishReceivingLileep
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingLileep
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveLileepPC::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedLileepFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_TransferLileepToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RustboroCity_DevonCorp_2F_EventScript_TransferLileepToPC
	end

RustboroCity_DevonCorp_2F_EventScript_TransferLileepToPC::
	call Common_EventScript_TransferredToPC
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingLileep
	end

RustboroCity_DevonCorp_2F_EventScript_ReceivedLileepFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_LILEEP
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_LILEEP
	return

RustboroCity_DevonCorp_2F_EventScript_FinishReceivingLileep::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
	release
	end

@ Anorith

RustboroCity_DevonCorp_2F_EventScript_ReceiveAnorith::
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_ANORITH
	givemon SPECIES_ANORITH, 20
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveAnorithParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveAnorithPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveAnorithParty::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedAnorithFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_FinishReceivingAnorith
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingAnorith
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveAnorithPC::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedAnorithFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_TransferAnorithToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RustboroCity_DevonCorp_2F_EventScript_TransferAnorithToPC
	end

RustboroCity_DevonCorp_2F_EventScript_TransferAnorithToPC::
	call Common_EventScript_TransferredToPC
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingAnorith
	end

RustboroCity_DevonCorp_2F_EventScript_ReceivedAnorithFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_ANORITH
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_ANORITH
	return

RustboroCity_DevonCorp_2F_EventScript_FinishReceivingAnorith::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
	release
	end

@ Dracoceros

RustboroCity_DevonCorp_2F_EventScript_ReceiveDracoceros::
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_DRACOCEROS_HOLY_CHILD
	givemon SPECIES_DRACOCEROS_HOLY_CHILD, 20
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveDracocerosParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveDracocerosPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveDracocerosParty::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedDracocerosFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_FinishReceivingDracoceros
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingDracoceros
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveDracocerosPC::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedDracocerosFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_TransferDracocerosToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RustboroCity_DevonCorp_2F_EventScript_TransferDracocerosToPC
	end

RustboroCity_DevonCorp_2F_EventScript_TransferDracocerosToPC::
	call Common_EventScript_TransferredToPC
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingDracoceros
	end

RustboroCity_DevonCorp_2F_EventScript_ReceivedDracocerosFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_DRACOCEROS_HOLY_CHILD
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_DRACOCEROS_HOLY_CHILD
	return

RustboroCity_DevonCorp_2F_EventScript_FinishReceivingDracoceros::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	release
	end

@ Nebugon

RustboroCity_DevonCorp_2F_EventScript_ReceiveNebugon::
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_NEBUGON_TANK_CHILD
	givemon SPECIES_NEBUGON_TANK_CHILD, 20
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveNebugonParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveNebugonPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveNebugonParty::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedNebugonFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_FinishReceivingNebugon
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingNebugon
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveNebugonPC::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedNebugonFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_TransferNebugonToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RustboroCity_DevonCorp_2F_EventScript_TransferNebugonToPC
	end

RustboroCity_DevonCorp_2F_EventScript_TransferNebugonToPC::
	call Common_EventScript_TransferredToPC
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingNebugon
	end

RustboroCity_DevonCorp_2F_EventScript_ReceivedNebugonFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_NEBUGON_TANK_CHILD
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_NEBUGON_TANK_CHILD
	return

RustboroCity_DevonCorp_2F_EventScript_FinishReceivingNebugon::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	release
	end	

@ Kirin

RustboroCity_DevonCorp_2F_EventScript_ReceiveKirin::
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_KIRIN_MAGE_CHILD
	givemon SPECIES_KIRIN_MAGE_CHILD, 20
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveKirinParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveKirinPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveKirinParty::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedKirinFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_FinishReceivingKirin
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingKirin
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveKirinPC::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedKirinFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_TransferKirinToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RustboroCity_DevonCorp_2F_EventScript_TransferKirinToPC
	end

RustboroCity_DevonCorp_2F_EventScript_TransferKirinToPC::
	call Common_EventScript_TransferredToPC
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingKirin
	end

RustboroCity_DevonCorp_2F_EventScript_ReceivedKirinFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_KIRIN_MAGE_CHILD
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_KIRIN_MAGE_CHILD
	return

RustboroCity_DevonCorp_2F_EventScript_FinishReceivingKirin::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	release
	end	

@ Faerial

RustboroCity_DevonCorp_2F_EventScript_ReceiveFaerial::
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_FAERIAL_BEAUTY_CHILD
	givemon SPECIES_FAERIAL_BEAUTY_CHILD, 20
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveFaerialParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveFaerialPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveFaerialParty::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedFaerialFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_FinishReceivingFaerial
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingFaerial
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveFaerialPC::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedFaerialFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_TransferFaerialToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RustboroCity_DevonCorp_2F_EventScript_TransferFaerialToPC
	end

RustboroCity_DevonCorp_2F_EventScript_TransferFaerialToPC::
	call Common_EventScript_TransferredToPC
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingFaerial
	end

RustboroCity_DevonCorp_2F_EventScript_ReceivedFaerialFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_FAERIAL_BEAUTY_CHILD
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_FAERIAL_BEAUTY_CHILD
	return

RustboroCity_DevonCorp_2F_EventScript_FinishReceivingFaerial::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	release
	end	

@ Impyrian

RustboroCity_DevonCorp_2F_EventScript_ReceiveImpyrian::
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_IMPYRIAN_IMPERIAL_CHILD
	givemon SPECIES_IMPYRIAN_IMPERIAL_CHILD, 20
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveImpyrianParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveImpyrianPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveImpyrianParty::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedImpyrianFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_FinishReceivingImpyrian
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingImpyrian
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveImpyrianPC::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedImpyrianFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_TransferImpyrianToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RustboroCity_DevonCorp_2F_EventScript_TransferImpyrianToPC
	end

RustboroCity_DevonCorp_2F_EventScript_TransferImpyrianToPC::
	call Common_EventScript_TransferredToPC
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingImpyrian
	end

RustboroCity_DevonCorp_2F_EventScript_ReceivedImpyrianFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_IMPYRIAN_IMPERIAL_CHILD
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_IMPYRIAN_IMPERIAL_CHILD
	return

RustboroCity_DevonCorp_2F_EventScript_FinishReceivingImpyrian::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	release
	end	


@ Wintego

RustboroCity_DevonCorp_2F_EventScript_ReceiveWintego::
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_WINTEGO_WINTER_CHILD
	givemon SPECIES_WINTEGO_WINTER_CHILD, 20
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveWintegoParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveWintegoPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveWintegoParty::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedWintegoFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_FinishReceivingWintego
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingWintego
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveWintegoPC::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedWintegoFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_TransferWintegoToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RustboroCity_DevonCorp_2F_EventScript_TransferWintegoToPC
	end

RustboroCity_DevonCorp_2F_EventScript_TransferWintegoToPC::
	call Common_EventScript_TransferredToPC
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingWintego
	end

RustboroCity_DevonCorp_2F_EventScript_ReceivedWintegoFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_WINTEGO_WINTER_CHILD
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_WINTEGO_WINTER_CHILD
	return

RustboroCity_DevonCorp_2F_EventScript_FinishReceivingWintego::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	release
	end	


@ Prototype

RustboroCity_DevonCorp_2F_EventScript_ReceivePrototype::
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_PROTOTYPE_VILLAIN_CHILD
	givemon SPECIES_PROTOTYPE_VILLAIN_CHILD, 20
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceivePrototypeParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceivePrototypePC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RustboroCity_DevonCorp_2F_EventScript_ReceivePrototypeParty::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedPrototypeFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_FinishReceivingPrototype
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingPrototype
	end

RustboroCity_DevonCorp_2F_EventScript_ReceivePrototypePC::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedPrototypeFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_TransferPrototypeToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RustboroCity_DevonCorp_2F_EventScript_TransferPrototypeToPC
	end

RustboroCity_DevonCorp_2F_EventScript_TransferPrototypeToPC::
	call Common_EventScript_TransferredToPC
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceivingPrototype
	end

RustboroCity_DevonCorp_2F_EventScript_ReceivedPrototypeFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_PROTOTYPE_VILLAIN_CHILD
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_PROTOTYPE_VILLAIN_CHILD
	return

RustboroCity_DevonCorp_2F_EventScript_FinishReceivingPrototype::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	release
	end	

RustboroCity_DevonCorp_2F_EventScript_ChooseFossil::
	message RustboroCity_DevonCorp_2F_Text_TwoFossilsPickOne
	waitmessage
	multichoice 17, 6, MULTI_FOSSIL, FALSE
	switch VAR_RESULT
	case 0, RustboroCity_DevonCorp_2F_EventScript_ChooseClawFossil
	case 1, RustboroCity_DevonCorp_2F_EventScript_ChooseRootFossil
	case 2, RustboroCity_DevonCorp_2F_EventScript_CancelFossilSelect
	case MULTI_B_PRESSED, RustboroCity_DevonCorp_2F_EventScript_CancelFossilSelect
	end


RustboroCity_DevonCorp_2F_EventScript_ChooseClawFossil::
	goto RustboroCity_DevonCorp_2F_EventScript_GiveClawFossil
	end

RustboroCity_DevonCorp_2F_EventScript_ChooseRootFossil::
	goto RustboroCity_DevonCorp_2F_EventScript_GiveRootFossil
	end

RustboroCity_DevonCorp_2F_EventScript_CancelFossilSelect::
	release
	end

RustboroCity_DevonCorp_2F_EventScript_MatchCallScientist::
	lock
	faceplayer
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	goto_if_ge VAR_RUSTBORO_CITY_STATE, 6, RustboroCity_DevonCorp_2F_EventScript_WorkOnNext
	msgbox RustboroCity_DevonCorp_2F_Text_DevelopNewPokenavFeature, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_WorkOnNext::
	msgbox RustboroCity_DevonCorp_2F_Text_WhatToWorkOnNext, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_Text_DeviceForTalkingToPokemon:
	.string "We're developing a device for talking\n"
	.string "with POKéMON.\p"
	.string "But we haven't had much success…$"

RustboroCity_DevonCorp_2F_Text_DevelopingNewBalls:
	.string "I'm developing new kinds of\n"
	.string "POKé BALLS…\p"
	.string "But I haven't made much headway…$"

RustboroCity_DevonCorp_2F_Text_WeFinallyMadeNewBalls:
	.string "We finally made new kinds of\n"
	.string "POKé BALLS!\p"
	.string "The REPEAT BALL makes it easier to\n"
	.string "catch POKéMON you've caught before.\p"
	.string "The TIMER BALL gets better at catching\n"
	.string "POKéMON the longer a battle runs.\p"
	.string "Both are proudly developed by\n"
	.string "the DEVON CORPORATION.\p"
	.string "Please give them a try!$"

RustboroCity_DevonCorp_2F_Text_IMadePokenav:
	.string "I made the POKéNAV!\p"
	.string "As an engineer, I feel blessed to have\n"
	.string "made something so great!$"

RustboroCity_DevonCorp_2F_Text_WowThatsAPokenav:
	.string "Oh, wow!\n"
	.string "That's a POKéNAV!\p"
	.string "It came about as a result of our\n"
	.string "PRESIDENT's desire to learn about\l"
	.string "the feelings of POKéMON.\p"
	.string "Would you like me to describe its\n"
	.string "features in detail?\p"
	.string "No, no. I think you'll find out just by\n"
	.string "trying the POKéNAV out.$"

RustboroCity_DevonCorp_2F_Text_DeviceToVisualizePokemonDreams:
	.string "I'm trying to develop a device that\n"
	.string "visually reproduces the dreams of\l"
	.string "POKéMON…\p"
	.string "But it's not going well.$"

RustboroCity_DevonCorp_2F_Text_DevelopDeviceToResurrectFossils:
	.string "I've been trying to develop a device\n"
	.string "that resurrects POKéMON from fossils…\p"
	.string "And, it's working!$"

RustboroCity_DevonCorp_2F_Text_WantToBringFossilBackToLife:
	.string "Wait! That thing you have there…\n"
	.string "Is that a POKéMON fossil?\p"
	.string "Would you like to bring that POKéMON\n"
	.string "back to life?\p"
	.string "I can with my newly developed\n"
	.string "FOSSIL REGENERATOR.$"

RustboroCity_DevonCorp_2F_Text_OhIsThatSo:
	.string "Oh, is that so?\p"
	.string "DEVON's technological expertise\n"
	.string "is outstanding, I tell you.$"

RustboroCity_DevonCorp_2F_Text_TwoFossilsPickOne:
	.string "Oh, now that's a surprise!\n"
	.string "You have not one, but two, fossils?\p"
	.string "Unfortunately, my machine can only\n"
	.string "regenerate one POKéMON at a time.\p"
	.string "Would you like to pick one of your\n"
	.string "fossils for regeneration?$"

RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher:
	.string "Excellent!\n"
	.string "Let's do this right away.\p"
	.string "{PLAYER} handed the {STR_VAR_1} to\n"
	.string "the DEVON RESEARCHER.$"

RustboroCity_DevonCorp_2F_Text_FossilRegeneratorTakesTime:
	.string "The FOSSIL REGENERATOR, which I made,\n"
	.string "is incredible.\p"
	.string "But it has one drawback--it takes\n"
	.string "a long time to work.\p"
	.string "So, uh… How about you go for a stroll\n"
	.string "and look around for a while?$"

RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife:
	.string "Thanks for waiting!\p"
	.string "Your fossilized POKéMON has been\n"
	.string "brought back to life!\p"
	.string "The fossil was an ancient POKéMON.\n"
	.string "{STR_VAR_2}, it was!$"

RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher:
	.string "{PLAYER} received {STR_VAR_2} from\n"
	.string "the DEVON RESEARCHER.$"

@ Unused
RustboroCity_DevonCorp_2F_Text_TooManyPokemon:
	.string "Uh-oh, you've got too many POKéMON.\n"
	.string "You have no room for this one.$"

RustboroCity_DevonCorp_2F_Text_DevelopNewPokenavFeature:
	.string "I'm trying to develop a new feature\n"
	.string "for the POKéNAV…\p"
	.string "But it's not going well.$"

RustboroCity_DevonCorp_2F_Text_WhatToWorkOnNext:
	.string "Well, now what shall I work on\n"
	.string "developing next?\p"
	.string "Our company allows us to make our\n"
	.string "inspirations into reality.\p"
	.string "One couldn't ask for a better\n"
	.string "environment as an engineer.$"

