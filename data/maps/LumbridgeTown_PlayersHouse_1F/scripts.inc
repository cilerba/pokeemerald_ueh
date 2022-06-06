LumbridgeTown_PlayersHouse_1F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LumbridgeTown_PlayersHouse_1F_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

LumbridgeTown_PlayersHouse_1F_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_LUMBRIDGEPLAYER_STATE, 0, LumbridgeTown_PlayersHouse_1F_Frame_0
	.2byte 0


LumbridgeTown_PlayersHouse_1F_Frame_0::
	setrespawn HEAL_LOCATION_LUMBRIDGE_TOWN_PLAYERS_HOUSE_2F
	lock
	applymovement 1, LumbridgeTown_PlayersHouse_1F_Mom_InitMove
	waitmovement 1
	msgbox LumbridgeTown_PlayersHouse_1F_Frame_0_Text_0
	msgbox LumbridgeTown_PlayersHouse_1F_Frame_0_Text_1
	msgbox LumbridgeTown_PlayersHouse_1F_Frame_0_Text_2
	msgbox LumbridgeTown_PlayersHouse_1F_Frame_0_Text_3
	msgbox LumbridgeTown_PlayersHouse_1F_Frame_0_Text_4
	msgbox LumbridgeTown_PlayersHouse_1F_Frame_0_Text_5
	closemessage
	applymovement 1, Lumbridgetown_PlayersHouse_1F_Mom_Return
	waitmovement 1
	setvar VAR_LUMBRIDGEPLAYER_STATE, 1
	release
	end


LumbridgeTown_PlayersHouse_1F_Mom::
	lock
	switch VAR_LUMBRIDGEPLAYER_STATE
	case 1, LumbridgeTown_PlayersHouse_1F_Mom_3
	case 2, LumbridgeTown_PlayersHouse_1F_Mom_4
	case 4, LumbridgeTown_PlayersHouse_1F_Mom_5
	case 5, LumbridgeTown_PlayersHouse_1F_Mom_6
LumbridgeTown_PlayersHouse_1F_Mom_1:
	end

LumbridgeTown_PlayersHouse_1F_Mom_3:
	faceplayer
	msgbox LumbridgeTown_PlayersHouse_1F_Mom_Text_0
	release
	goto LumbridgeTown_PlayersHouse_1F_Mom_1

LumbridgeTown_PlayersHouse_1F_Mom_4:
	faceplayer
	msgbox LumbridgeTown_PlayersHouse_1F_Mom_Text_1
	release
	goto LumbridgeTown_PlayersHouse_1F_Mom_1

LumbridgeTown_PlayersHouse_1F_Mom_5:
	faceplayer
	goto_if_set FLAG_SAID_BYE_MOM, LumbridgeTown_PlayersHouse_1F_Mom_8
	msgbox LumbridgeTown_PlayersHouse_1F_Mom_Text_3
	setflag FLAG_SAID_BYE_MOM
	goto_if_set FLAG_SAID_BYE_DAD, LumbridgeTown_PlayersHouse_1F_Mom_11
LumbridgeTown_PlayersHouse_1F_Mom_7:
	release
	goto LumbridgeTown_PlayersHouse_1F_Mom_1

LumbridgeTown_PlayersHouse_1F_Mom_6:
	faceplayer
	msgbox LumbridgeTown_PlayersHouse_1F_Mom_Text_4
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	incrementgamestat GAME_STAT_RESTED_AT_HOME
	msgbox LumbridgeTown_PlayersHouse_1F_Mom_Text_5
	release
	goto LumbridgeTown_PlayersHouse_1F_Mom_1

LumbridgeTown_PlayersHouse_1F_Mom_8:
	msgbox LumbridgeTown_PlayersHouse_1F_Mom_Text_2
	goto LumbridgeTown_PlayersHouse_1F_Mom_7

LumbridgeTown_PlayersHouse_1F_Mom_11:
	setvar VAR_LUMBRIDGEPLAYER_STATE, 5
	goto LumbridgeTown_PlayersHouse_1F_Mom_7


LumbridgeTown_PlayersHouse_1F_TV::
	lock
	msgbox LumbridgeTown_PlayersHouse_1F_TV_Text_0
	release
	end


LumbridgeTown_PlayersHouse_1F_Sink::
	lock
	msgbox LumbridgeTown_PlayersHouse_1F_Sink_Text_0
	release
	end


LumbridgeTown_PlayersHouse_1F_Refrigerator::
	lock
	msgbox LumbridgeTown_PlayersHouse_1F_Refrigerator_Text_0
	release
	end


LumbridgeTown_PlayersHouse_1F_Display::
	lock
	msgbox LumbridgeTown_PlayersHouse_1F_Display_Text_0
	release
	end


LumbridgeTown_PlayersHouse_1F_Phone::
	lock
	msgbox LumbridgeTown_PlayersHouse_1F_Phone_Text_0
	release
	end


LumbridgeTown_PlayersHouse_1F_Mom_InitMove:
	face_player
	emote_exclamation_mark
	delay_16
	delay_16
	delay_16
	delay_16
	walk_up
	walk_up
	walk_right
	step_end

Lumbridgetown_PlayersHouse_1F_Mom_Return:
	walk_left
	walk_down
	walk_down
	face_left
	step_end

LumbridgeTown_PlayersHouse_1F_Frame_0_Text_0:
	.string "Hello, dear!\p"
	.string "Did you hear the news?\l"
	.string "Your Trainer ID arrived today!$"

LumbridgeTown_PlayersHouse_1F_Frame_0_Text_1:
	.string "With your Trainer ID, you'll be one step\n"
	.string "closer to officially being a Pokémon\l"
	.string "Trainer!$"

LumbridgeTown_PlayersHouse_1F_Frame_0_Text_2:
	.string "Once you become an official Pokémon\n"
	.string "Trainer, you'll be able to take on the\l"
	.string "Azoria Gym Challenge.$"

LumbridgeTown_PlayersHouse_1F_Frame_0_Text_3:
	.string "Isn't that great?\p"
	.string "I'm so glad we moved here!\p"
	.string "Your father found new work as a feller\n"
	.string "and now you get to take on the Azoria\l"
	.string "Gym Challenge and become a Pokémon\l"
	.string "Trainer!$"

LumbridgeTown_PlayersHouse_1F_Frame_0_Text_4:
	.string "Anyway…$"

LumbridgeTown_PlayersHouse_1F_Frame_0_Text_5:
	.string "Your Trainer ID was delivered to\n"
	.string "Professor Larch's laboratory.\p"
	.string "Why don't you go by to pick it up?\p"
	.string "You can also say hello to your father on\n"
	.string "the way!\l"
	.string "He's working in the field.$"

LumbridgeTown_PlayersHouse_1F_Mom_Text_0:
	.string "Your Trainer ID was delivered to\n"
	.string "Professor Larch's laboratory.$"

LumbridgeTown_PlayersHouse_1F_Mom_Text_1:
	.string "Look at you! An official Pokémon\n"
	.string "Trainer…\p"
	.string "Wow, Professor Larch even gave you a\n"
	.string "Pokémon?$"

LumbridgeTown_PlayersHouse_1F_Mom_Text_2:
	.string "You're going to do great, honey!$"

LumbridgeTown_PlayersHouse_1F_Mom_Text_3:
	.string "You're ready to set off on your Pokémon\n"
	.string "journey?\p"
	.string "{PLAYER}, you're going to do so well in\n"
	.string "the Gym Challenge.\p"
	.string "I can't wait to see you excel.$"

LumbridgeTown_PlayersHouse_1F_Mom_Text_4:
	.string "How are you doing, {PLAYER}?\n"
	.string "You look a little tired.\p"
	.string "I think you should rest a bit.$"

LumbridgeTown_PlayersHouse_1F_Mom_Text_5:
	.string "All better!$"

LumbridgeTown_PlayersHouse_1F_TV_Text_0:
	.string "There's a show on TV.\p"
	.string "It looks like two agents are solving a\n"
	.string "mystery.\p"
	.string "What's that little green thing?$"

LumbridgeTown_PlayersHouse_1F_Sink_Text_0:
	.string "The sink is squeaky clean!\p"
	.string "I should hope so. I just cleaned it last\n"
	.string "night.$"

LumbridgeTown_PlayersHouse_1F_Refrigerator_Text_0:
	.string "Dad just brought in groceries. Nice!$"

LumbridgeTown_PlayersHouse_1F_Display_Text_0:
	.string "Mom likes to display all of her mugs\n"
	.string "here.$"

LumbridgeTown_PlayersHouse_1F_Phone_Text_0:
	.string "I don't have time to use the phone right\n"
	.string "now.$"
