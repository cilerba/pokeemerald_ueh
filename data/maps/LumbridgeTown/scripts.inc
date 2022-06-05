LumbridgeTown_MapScripts::
	.byte 0


LumbridgeTown_MomsBike::
	lock
	msgbox LumbridgeTown_MomsBike_Text_0
	msgbox LumbridgeTown_MomsBike_Text_1
	release
	end


LumbridgeTown_Dad::
	lock
	switch VAR_LUMBRIDGEPLAYER_STATE
	case 1, LumbridgeTown_Dad_3
	case 2, LumbridgeTown_Dad_4
	case 4, LumbridgeTown_Dad_5
	case 5, LumbridgeTown_Dad_6
LumbridgeTown_Dad_1:
	release
	end

LumbridgeTown_Dad_3:
	faceplayer
	msgbox LumbridgeTown_Dad_Text_0
	goto LumbridgeTown_Dad_1

LumbridgeTown_Dad_4:
	faceplayer
	msgbox LumbridgeTown_Dad_Text_1
	goto LumbridgeTown_Dad_1

LumbridgeTown_Dad_5:
	faceplayer
	goto_if_set FLAG_SAID_BYE_DAD, LumbridgeTown_Dad_7
	msgbox LumbridgeTown_Dad_Text_3
	setflag FLAG_SAID_BYE_DAD
	goto_if_set FLAG_SAID_BYE_MOM, LumbridgeTown_Dad_10
	goto LumbridgeTown_Dad_1

LumbridgeTown_Dad_6:
	faceplayer
	msgbox LumbridgeTown_Dad_Text_4
	goto LumbridgeTown_Dad_1

LumbridgeTown_Dad_7:
	msgbox LumbridgeTown_Dad_Text_2
	goto LumbridgeTown_Dad_1

LumbridgeTown_Dad_10:
	setvar VAR_LUMBRIDGEPLAYER_STATE, 5
	goto LumbridgeTown_Dad_1


LumbridgeTown_Worker::
	lock
	faceplayer
	msgbox LumbridgeTown_Worker_Text_0
	release
	end


LumbridgeTown_PlayerMailbox::
	lock
	msgbox LumbridgeTown_PlayerMailbox_Text_0, MSGBOX_SIGN
	release
	end


LumbridgeTown_ProfMailbox::
	lock
	msgbox LumbridgeTown_ProfMailbox_Text_0, MSGBOX_SIGN
	release
	end


LumbridgeTown_ProfSign::
	lock
	msgbox LumbridgeTown_ProfSign_Text_0, MSGBOX_SIGN
	release
	end


LumbridgeTown_TownSign::
	lock
	msgbox LumbridgeTown_TownSign_Text_0, MSGBOX_SIGN
	release
	end


LumbridgeTown_LumberSign::
	lock
	msgbox LumbridgeTown_LumberSign_Text_0, MSGBOX_SIGN
	release
	end


LumbridgeTown_Technology::
	lock
	faceplayer
	msgbox LumbridgeTown_Technology_Text_0
	release
	end


LumbridgeTown_Trigger::
	lock
	msgbox LumbridgeTown_Trigger_Text_0
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, LumbridgeTown_Player_MoveLeft
	waitmovement 0
	release
	end


LumbridgeTown_Trigger_Bye::
	lock
	msgbox LumbridgeTown_Trigger_Bye_Text_0
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, LumbridgeTown_Player_MoveLeft
	waitmovement 0
	release
	end


LumbridgeTown_Player_MoveLeft:
	walk_left
	step_end

LumbridgeTown_MomsBike_Text_0:
	.string "It's Mom's bike.$"

LumbridgeTown_MomsBike_Text_1:
	.string "Maybe one day I'll have my own!$"

LumbridgeTown_Dad_Text_0:
	.string "Hey there, {PLAYER}!\p"
	.string "Have you spoken to Professor Larch\n"
	.string "yet? Mom told me there's a package\l"
	.string "waiting for you.$"

LumbridgeTown_Dad_Text_1:
	.string "Congrats, {PLAYER}! I can't believe\n"
	.string "the day has finally come.$"

LumbridgeTown_Dad_Text_2:
	.string "Good luck, {PLAYER}!$"

LumbridgeTown_Dad_Text_3:
	.string "You're off, huh?\p"
	.string "I'm really proud of you, {PLAYER}.\p"
	.string "Mom and I will be rooting for you.$"

LumbridgeTown_Dad_Text_4:
	.string "Workin' hard!$"

LumbridgeTown_Worker_Text_0:
	.string "Sometimes I bring my Pokémon out to\n"
	.string "help me chop trees.\p"
	.string "Erm...Please don't tell my boss.$"

LumbridgeTown_PlayerMailbox_Text_0:
	.string "{PLAYER}'s Home$"

LumbridgeTown_ProfMailbox_Text_0:
	.string "Professor Larch's Home$"

LumbridgeTown_ProfSign_Text_0:
	.string "Larch Laboratory$"

LumbridgeTown_TownSign_Text_0:
	.string "Lumbridge Town$"

LumbridgeTown_LumberSign_Text_0:
	.string "Lumber Yard$"

LumbridgeTown_Technology_Text_0:
	.string "Professor Larch has been making\n"
	.string "amazing progress in reverse\l"
	.string "engineering the science behind Poké\l"
	.string "Balls.\p"
	.string "Technology is incredible!$"

LumbridgeTown_Trigger_Text_0:
	.string "I should speak to Professor Larch\n"
	.string "first.$"

LumbridgeTown_Trigger_Bye_Text_0:
	.string "I should say bye to mom and dad first.$"
