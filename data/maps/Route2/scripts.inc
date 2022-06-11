Route2_MapScripts::
	.byte 0


Route2_Trainer_BugCatcher::
	trainerbattle_single TRAINER_JULIAN, Route2_Trainer_BugCatcherIntro, Route2_Trainer_BugCatcherDefeated
	msgbox Route2_Trainer_BugCatcher_Text_0
	closemessage
	release
	end


Route2_Trainer_Lass::
	trainerbattle_single TRAINER_CLAUDIA, Route2_Trainer_LassIntro, Route2_Trainer_LassDefeated
	msgbox Route2_Trainer_BugCatcher_Text_0
	closemessage
	release
	end


Route2_Beauty::
	lock
	faceplayer
	msgbox Route2_Beauty_Text_0
	release
	end


Route2_Trainer_BugCatcher_Text_0:
	.string "Test$"

Route2_Beauty_Text_0:
	.string "I like the view from here.\p"
	.string "I get to watch all the Pokémon battles\n"
	.string "that take place down the hill.$"

Route2_Trainer_BugCatcherIntro::
	.string "$"

Route2_Trainer_BugCatcherDefeated::
	.string "$"

Route2_Trainer_LassIntro::
	.string "$"

Route2_Trainer_LassDefeated::
	.string "$"
