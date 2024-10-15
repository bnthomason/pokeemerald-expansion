FossilCave_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, FossilCave_SetHoleWarp
	.byte 0

FossilCave_SetHoleWarp:
	setstepcallback STEP_CB_CRACKED_FLOOR
	setholewarp MAP_FOSSIL_CAVE_STEEL
	end
