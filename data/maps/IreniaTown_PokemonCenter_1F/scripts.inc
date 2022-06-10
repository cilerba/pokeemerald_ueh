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


IreniaTown_PokemonCenter_1F_FatMan::
	lock
	faceplayer
	msgbox IreniaTown_PokemonCenter_1F_FatMan_Text_0
	release
	end


IreniaTown_PokemonCenter_1F_Swimmer::
	lock
	faceplayer
	msgbox IreniaTown_PokemonCenter_1F_Swimmer_Text_0
	release
	end


IreniaTown_PokemonCenter_1F_Teala_Text_0:
	.string "The Cable Club is currently undergoing\n"
	.string "maintenance.\p"
	.string "We apologize for any inconvenience.$"

IreniaTown_PokemonCenter_1F_FatMan_Text_0:
	.string "At every Pokémon Center, you'll find a\n"
	.string "collection of free books to read\l"
	.string "through.\p"
	.string "It's like a mini library!$"

IreniaTown_PokemonCenter_1F_Swimmer_Text_0:
	.string "Phew! I just swam all the way through\n"
	.string "Route 13 to visit Irenia Town.\p"
	.string "$"
