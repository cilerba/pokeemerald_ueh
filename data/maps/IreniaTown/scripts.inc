IreniaTown_MapScripts::
	.byte 0


IreniaTown_TownSign::
	lock
	msgbox IreniaTown_TownSign_Text_0
	release
	end


IreniaTown_StatueSign::
	lock
	msgbox IreniaTown_StatueSign_Text_0
	release
	end


IreniaTown_NPCShrine::
	lock
	faceplayer
	msgbox IreniaTown_NPCShrine_Text_0
	release
	end


IreniaTown_NPCWater::
	lock
	faceplayer
	msgbox IreniaTown_NPCWater_Text_0
	release
	end


IreniaTown_NPCLass::
	lock
	faceplayer
	msgbox IreniaTown_NPCLass_Text_0
	release
	end


IreniaTown_CantLeave::
	lock
	msgbox IreniaTown_CantLeave_Text_0
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp
	waitmovement OBJ_EVENT_ID_PLAYER
	release
	end


IreniaTown_TownSign_Text_0:
	.string "Irenia Town$"

IreniaTown_StatueSign_Text_0:
	.string "Our Guardian Lugia's Shrine$"

IreniaTown_NPCShrine_Text_0:
	.string "My son was sick many years ago.\p"
	.string "I came to this statue every morning to\n"
	.string "pray to our Guardian Lugia.\p"
	.string "One morning I awoke to a loud cry and\n"
	.string "strong winds.\p"
	.string "Upon exiting my home, I saw it. Our\n"
	.string "Guardian Lugia.\p"
	.string "It heard us.\p"
	.string "The next day my son was healthy and\n"
	.string "back to normal.\p"
	.string "Ever since that day, I come here every\n"
	.string "morning to give thanks to our Guardian\l"
	.string "Lugia.$"

IreniaTown_NPCWater_Text_0:
	.string "Do you ever wonder what's on the other\n"
	.string "side of this water?\p"
	.string "Really makes you think…$"

IreniaTown_NPCLass_Text_0:
	.string "I recently read Professor Larch's\n"
	.string "article on her latest research.\p"
	.string "Did you know, in ancient times, Poké\n"
	.string "Balls weren't used at all?\p"
	.string "I wonder how Pokémon Trainers caught\n"
	.string "their Pokémon.$"

IreniaTown_CantLeave_Text_0:
	.string "I need to deliver Professor Larch's\n"
	.string "package.$"
