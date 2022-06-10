IreniaTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, IreniaTown_PokemonCenter_1F_MapScripts_MAP_SCRIPT_ON_RESUME
	.byte 0

IreniaTown_PokemonCenter_1F_MapScripts_MAP_SCRIPT_ON_RESUME:
	call CableClub_OnResume
	return


IreniaTown_PokemonCenter_1F_Nurse::
	setvar VAR_0x800B, 2
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	return


IreniaTown_PokemonCenter_1F_Teala::
	lock
	faceplayer
	msgbox IreniaTown_PokemonCenter_1F_Teala_Text_0
	release
	end


IreniaTown_PokemonCenter_1F_Teala_Text_0:
	.string "The Cable Club is currently undergoing\n"
	.string "maintenance.\p"
	.string "We apologize for any inconvenience.$"
