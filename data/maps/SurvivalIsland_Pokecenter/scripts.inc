.set LOCALID_NURSE, 1

SurvivalIsland_HomeBase_Pokecenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SurvivalIsland_Pokecenter_OnTransition
	.byte 0

SurvivalIsland_HomeBase_Pokecenter_OnTransition:
	setrespawn HEAL_LOCATION_SURVIVAL_ISLAND_HOMEBASE
	call_if_unset FLAG_STARTED_CHALLENGE, SurvivalIsland_HomeBase_Pokecenter_EventScript_NurseBlocksPC
	end

SurvivalIsland_HomeBase_Pokecenter_EventScript_NurseBlocksPC::
	setobjectxyperm LOCALID_NURSE, 10, 2, 
	return


SurvivalIsland_HomeBase_Pokecenter_Nurse::
	lockall
	faceplayer
	goto_if_set FLAG_STARTED_CHALLENGE, SurvivalIsland_HomeBase_Pokecenter_Eventscript_PCAdvice
	message SurvivalIsland_HomeBase_Pokecenter_Text_MustHavePokemonToUsePC
	waitmessage
	delay 120
	goto_if_unset FLAG_PICKED_SIX_POKEMON, SurvivalIsland_HomeBase_Pokecenter_Text_NeedAtLeastOnePokemon
	closemessage
	applymovement LOCALID_NURSE, SurvivalIsland_HomeBase_PokeCenter_Movement_NurseOutOfWay
	waitmovement 0
	delay 10
	message SurvivalIsland_HomeBase_Pokecenter_Eventscript_PCAdvice
	waitmessage
	closemessage
	copyobjectxytoperm LOCALID_NURSE
	setflag FLAG_STARTED_CHALLENGE
	releaseall
	end

SurvivalIsland_HomeBase_Pokecenter_Text_MustHavePokemonToUsePC:
	.string "To use the PC, you must have obtained\n"
	.string "at least 1 POKéMON. Let me check to\l"
	.string "see if you have recieved one.$"

SurvivalIsland_HomeBase_Pokecenter_Text_NeedAtLeastOnePokemon:
	.string "You haven't obtained a single POKéMON!\n"
	.string "You need at least 1 POKéMON to use\l"
	.string "the PC!\p"
	.string "Come back when you have obtained at\n"
	.string "least 1 POKéMON.$"

SurvivalIsland_HomeBase_Pokecenter_Eventscript_PCAdvice:
	.string "Remember, on this island, depositing\n"
	.string "a POKéMON to the PC won't heal it.\l"
	.string "You'll need to figure out some other\l"
	.string "way to heal your pokemon.\p"
	.string "Furthermore, we can't offer you a\n"
	.string "healing machine here... that's\l"
	.string "against the rules.$"
