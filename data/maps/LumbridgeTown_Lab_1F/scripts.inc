LumbridgeTown_Lab_1F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LumbridgeTown_Lab_1F_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

LumbridgeTown_Lab_1F_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_LUMBRIDGEPLAYER_STATE, 1, LumbridgeTown_Lab_1F_Intro
	map_script_2 VAR_LUMBRIDGEPLAYER_STATE, 3, LumbridgeTown_Lab_1F_DeliverPackage
	.2byte 0


LumbridgeTown_Lab_1F_Intro::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, LumbridgeTown_Lab_1F_Intro_PlayerUp
	waitmovement 0
	msgbox LumbridgeTown_Lab_1F_Intro_Text_0
	closemessage
	applymovement 1, LumbridgeTown_Lab_1F_Intro_FaceLeft
	waitmovement 1
	msgbox LumbridgeTown_Lab_1F_Intro_Text_1
	closemessage
	applymovement 2, LumbridgeTown_Lab_1F_Intro_FaceRight
	waitmovement 2
	msgbox LumbridgeTown_Lab_1F_Intro_Text_2
	closemessage
	applymovement 2, LumbridgeTown_Lab_1F_Intro_FaceDown
	applymovement 1, LumbridgeTown_Lab_1F_Intro_FaceDown
	waitmovement 2
	msgbox LumbridgeTown_Lab_1F_Intro_Text_3
	msgbox LumbridgeTown_Lab_1F_Intro_Text_4
	msgbox LumbridgeTown_Lab_1F_Intro_Text_5
	closemessage
	applymovement 2, LumbridgeTown_Lab_1F_Intro_StepDown
	waitmovement 2
	playfanfare MUS_OBTAIN_ITEM
	msgbox LumbridgeTown_Lab_1F_Intro_Text_6
	waitmessage
	waitfanfare
	setflag FLAG_SYS_TRAINERID_GET
	applymovement 2, LumbridgeTown_Lab_1F_Intro_StepBack
	waitmovement 2
	msgbox LumbridgeTown_Lab_1F_Intro_Text_7
	closemessage
	delay 120
	msgbox LumbridgeTown_Lab_1F_Intro_Text_8
	applymovement 1, LumbridgeTown_Lab_1F_Intro_FaceLeft
	waitmovement 1
	msgbox LumbridgeTown_Lab_1F_Intro_Text_9
	waitmessage
	applymovement 2, LumbridgeTown_Lab_1F_Intro_Exclamation
	msgbox LumbridgeTown_Lab_1F_Intro_Text_10
	closemessage
	applymovement 2, LumbridgeTown_Lab_1F_Intro_FaceRight
	waitmovement 2
	msgbox LumbridgeTown_Lab_1F_Intro_Text_11
	closemessage
	applymovement 2, LumbridgeTown_Lab_1F_Intro_FaceDown
	applymovement 1, LumbridgeTown_Lab_1F_Intro_FaceDown
	waitmovement 1
	msgbox LumbridgeTown_Lab_1F_Intro_Text_12
	msgbox LumbridgeTown_Lab_1F_Intro_Text_13
	closemessage
	applymovement 2, LumbridgeTown_Lab_1F_Intro_StepDown
	waitmovement 2
	special ChooseStarter
	waitstate
	setflag FLAG_SYS_POKEMON_GET
	bufferleadmonspeciesname 0
	msgbox LumbridgeTown_Lab_1F_Intro_Text_14
	closemessage
	applymovement 2, LumbridgeTown_Lab_1F_Intro_StepBack
	waitmovement 2
	msgbox LumbridgeTown_Lab_1F_Intro_Text_15
	closemessage
	delay 48
	msgbox LumbridgeTown_Lab_1F_Intro_Text_16
	closemessage
	applymovement 2, LumbridgeTown_Lab_1F_Intro_StepDown
	waitmovement 2
	giveitem ITEM_TOWN_MAP
	applymovement 2, LumbridgeTown_Lab_1F_Intro_StepBack
	waitmovement 2
	msgbox LumbridgeTown_Lab_1F_Intro_Text_17
	setvar VAR_LUMBRIDGEPLAYER_STATE, 2
	release
	end


LumbridgeTown_Lab_1F_DeliverPackage::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, LumbridgeTown_Lab_1F_Intro_PlayerUp
	waitmovement 0
	msgbox LumbridgeTown_Lab_1F_DeliverPackage_Text_0
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, LumbridgeTown_Lab_1F_Dex_WalkUp
	waitmovement 0
	setvar VAR_0x8004, ITEM_PARCEL
	call Common_EventScript_PlayerHandedOverTheItem
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, LumbridgeTown_Lab_1F_Dex_WalkDown
	waitmovement 0
	msgbox LumbridgeTown_Lab_1F_DeliverPackage_Text_1
	closemessage
	applymovement 2, LumbridgeTown_Lab_1F_Dex_FaceAway
	waitmovement 2
	msgbox LumbridgeTown_Lab_1F_DeliverPackage_Text_2
	closemessage
	applymovement 2, LumbridgeTown_Lab_1F_Intro_StepDown
	waitmovement 2
	playfanfare MUS_OBTAIN_ITEM
	msgbox LumbridgeTown_Lab_1F_DeliverPackage_Text_3
	waitfanfare
	closemessage
	setflag FLAG_SYS_POKEDEX_GET
	special SetUnlockedPokedexFlags
	applymovement 2, LumbridgeTown_Lab_1F_Intro_StepBack
	waitmovement 2
	applymovement 2, LumbridgeTown_Lab_1F_Dex_WalkInPlaceDown
	waitmovement 2
	msgbox LumbridgeTown_Lab_1F_DeliverPackage_Text_4
	closemessage
	applymovement 1, LumbridgeTown_Lab_1F_Intro_FaceLeft
	waitmovement 1
	msgbox LumbridgeTown_Lab_1F_DeliverPackage_Text_5
	closemessage
	applymovement 1, LumbridgeTown_Lab_1F_Intro_FaceDown
	waitmovement 1
	msgbox LumbridgeTown_Lab_1F_DeliverPackage_Text_6
	closemessage
	applymovement 2, LumbridgeTown_Lab_1F_Intro_StepDown
	waitmovement 2
	giveitem ITEM_POKE_BALL, 20
	applymovement 2, LumbridgeTown_Lab_1F_Intro_StepBack
	waitmovement 2
	msgbox LumbridgeTown_Lab_1F_DeliverPackage_Text_7
	setvar VAR_LUMBRIDGEPLAYER_STATE, 4
	release
	end


LumbridgeTown_Lab_1F_Professor::
	lock
	faceplayer
	switch VAR_LUMBRIDGEPLAYER_STATE
	case 2, LumbridgeTown_Lab_1F_Professor_3
	case 4, LumbridgeTown_Lab_1F_Professor_4
	case 5, LumbridgeTown_Lab_1F_Professor_5
LumbridgeTown_Lab_1F_Professor_1:
	release
	end

LumbridgeTown_Lab_1F_Professor_3:
	msgbox LumbridgeTown_Lab_1F_Professor_Text_0
	goto LumbridgeTown_Lab_1F_Professor_1

LumbridgeTown_Lab_1F_Professor_4:
	msgbox LumbridgeTown_Lab_1F_Professor_Text_1
	goto LumbridgeTown_Lab_1F_Professor_1

LumbridgeTown_Lab_1F_Professor_5:
	msgbox LumbridgeTown_Lab_1F_Professor_Text_2
	goto LumbridgeTown_Lab_1F_Professor_1


LumbridgeTown_Lab_1F_Assistant::
	lock
	faceplayer
	switch VAR_LUMBRIDGEPLAYER_STATE
	case 2, LumbridgeTown_Lab_1F_Assistant_3
	case 4, LumbridgeTown_Lab_1F_Assistant_4
	case 5, LumbridgeTown_Lab_1F_Assistant_4
LumbridgeTown_Lab_1F_Assistant_1:
	release
	end

LumbridgeTown_Lab_1F_Assistant_3:
	msgbox LumbridgeTown_Lab_1F_Assistant_Text_0
	goto LumbridgeTown_Lab_1F_Assistant_1

LumbridgeTown_Lab_1F_Assistant_4:
	msgbox LumbridgeTown_Lab_1F_Assistant_Text_1
	goto LumbridgeTown_Lab_1F_Assistant_1


LumbridgeTown_Lab_1F_Scientist1::
	lock
	faceplayer
	msgbox LumbridgeTown_Lab_1F_Scientist1_Text_0
	release
	end


LumbridgeTown_Lab_1F_Scientist2::
	lock
	faceplayer
	switch VAR_LUMBRIDGEPLAYER_STATE
	case 1, LumbridgeTown_Lab_1F_Scientist2_3
	case 2, LumbridgeTown_Lab_1F_Scientist2_4
	case 5, LumbridgeTown_Lab_1F_Scientist2_5
LumbridgeTown_Lab_1F_Scientist2_1:
	release
	end

LumbridgeTown_Lab_1F_Scientist2_3:
	msgbox LumbridgeTown_Lab_1F_Scientist2_Text_0
	goto LumbridgeTown_Lab_1F_Scientist2_1

LumbridgeTown_Lab_1F_Scientist2_4:
	msgbox LumbridgeTown_Lab_1F_Scientist2_Text_1
	goto LumbridgeTown_Lab_1F_Scientist2_1

LumbridgeTown_Lab_1F_Scientist2_5:
	msgbox LumbridgeTown_Lab_1F_Scientist2_Text_2
	goto LumbridgeTown_Lab_1F_Scientist2_1


LumbridgeTown_Lab_1F_Intro_PlayerUp:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LumbridgeTown_Lab_1F_Intro_FaceLeft:
	face_left
	delay_16
	step_end

LumbridgeTown_Lab_1F_Intro_FaceDown:
	face_down
	delay_16
	step_end

LumbridgeTown_Lab_1F_Intro_FaceRight:
	face_right
	delay_16
	step_end

LumbridgeTown_Lab_1F_Intro_StepDown:
	walk_down
	delay_16
	step_end

LumbridgeTown_Lab_1F_Intro_StepBack:
	lock_facing_direction
	walk_up
	unlock_facing_direction
	step_end

LumbridgeTown_Lab_1F_Intro_Exclamation:
	emote_exclamation_mark
	delay_16
	delay_16
	delay_16
	delay_16
	step_end

LumbridgeTown_Lab_1F_Dex_FaceAway:
	face_up
	delay_16
	delay_16
	delay_16
	walk_in_place_up
	delay_16
	delay_16
	face_down
	step_end

LumbridgeTown_Lab_1F_Dex_WalkInPlaceDown:
	walk_in_place_down
	step_end

LumbridgeTown_Lab_1F_Dex_WalkUp:
	walk_up
	step_end

LumbridgeTown_Lab_1F_Dex_WalkDown:
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

LumbridgeTown_Lab_1F_Intro_Text_0:
	.string "Hey it's {PLAYER}! What brings you\n"
	.string "here?$"

LumbridgeTown_Lab_1F_Intro_Text_1:
	.string "Um…ma'am.\p"
	.string "The package.$"

LumbridgeTown_Lab_1F_Intro_Text_2:
	.string "Oh yes!\l"
	.string "How could I forget?$"

LumbridgeTown_Lab_1F_Intro_Text_3:
	.string "{PLAYER}, I'm so glad you're here.$"

LumbridgeTown_Lab_1F_Intro_Text_4:
	.string "As you may know, Professor Elm and I\n"
	.string "have been working together to register\l"
	.string "you as a Pokémon Trainer ever since\l"
	.string "you moved here a few weeks ago.$"

LumbridgeTown_Lab_1F_Intro_Text_5:
	.string "Today, I'm happy to announce that the\n"
	.string "registration process is complete!\p"
	.string "Your Trainer ID arrived this morning via\n"
	.string "PeliPost.$"

LumbridgeTown_Lab_1F_Intro_Text_6:
	.string "{PLAYER} received a Trainer ID!$"

LumbridgeTown_Lab_1F_Intro_Text_7:
	.string "Congratulations!\p"
	.string "You are officially a Pokémon Trainer.$"

LumbridgeTown_Lab_1F_Intro_Text_8:
	.string "… …$"

LumbridgeTown_Lab_1F_Intro_Text_9:
	.string "Um…ma'am.\p"
	.string "Did you forge-$"

LumbridgeTown_Lab_1F_Intro_Text_10:
	.string "Pokémon!$"

LumbridgeTown_Lab_1F_Intro_Text_11:
	.string "Thanks, Clyde.$"

LumbridgeTown_Lab_1F_Intro_Text_12:
	.string "Yes, Professor Elm and I agreed that\n"
	.string "one cannot start a Pokémon journey\l"
	.string "without a partner of their own.$"

LumbridgeTown_Lab_1F_Intro_Text_13:
	.string "So, Professor Elm sent over 3 Pokémon\n"
	.string "and we would like you to choose one to\l"
	.string "be your partner.$"

LumbridgeTown_Lab_1F_Intro_Text_14:
	.string "{STR_VAR_1}! It's one of my\n"
	.string "favorites.$"

LumbridgeTown_Lab_1F_Intro_Text_15:
	.string "Now, before you begin your journey, I do\n"
	.string "have one small request.\p"
	.string "I have one more gift for you, but it's in\n"
	.string "Irenia Town.\p"
	.string "Would you be willing to take your new\n"
	.string "partner to retrieve this parcel for me?$"

LumbridgeTown_Lab_1F_Intro_Text_16:
	.string "Super!\n"
	.string "You won't regret it!\p"
	.string "It was delivered to the Irenia Town\n"
	.string "Mart.\p"
	.string "Actually…let's make this a little easier\n"
	.string "for you, shall we?$"

LumbridgeTown_Lab_1F_Intro_Text_17:
	.string "If you're unsure where to go, just open\n"
	.string "your Town Map!$"

LumbridgeTown_Lab_1F_DeliverPackage_Text_0:
	.string "Hm? Oh hi, {PLAYER}.\n"
	.string "What's up?\p"
	.string "That's right! I asked you to pick up a\n"
	.string "delivery for me.\p"
	.string "How'd it go?$"

LumbridgeTown_Lab_1F_DeliverPackage_Text_1:
	.string "Super!$"

LumbridgeTown_Lab_1F_DeliverPackage_Text_2:
	.string "Here it is!$"

LumbridgeTown_Lab_1F_DeliverPackage_Text_3:
	.string "{PLAYER} received the Pokédex!$"

LumbridgeTown_Lab_1F_DeliverPackage_Text_4:
	.string "I'm sure you've heard of the Pokédex by\n"
	.string "now, so I'll spare you the details.\p"
	.string "With this high-tech encyclopedia you'll\n"
	.string "be able to log information on any\l"
	.string "Pokémon you encounter in the wild.\p"
	.string "Even more information becomes\n"
	.string "available when you catch the Pokémon!\p"
	.string "An essential for any Pokémon Trainer.\p"
	.string "Speaking of catching Pokémon, I\n"
	.string "haven't given you Poké Balls yet, have\l"
	.string "I?$"

LumbridgeTown_Lab_1F_DeliverPackage_Text_5:
	.string "You haven't.$"

LumbridgeTown_Lab_1F_DeliverPackage_Text_6:
	.string "Well! Poké Balls are a fascinating piece\n"
	.string "of technology that are used to\l"
	.string "capture wild Pokémon.\p"
	.string "My goal as a professor is actually to\n"
	.string "discover how they were created!\p"
	.string "I intend to make that knowledge public\n"
	.string "for all to use and learn from.\p"
	.string "I would like to gift you a handful of\n"
	.string "Poké Balls to start your journey off.$"

LumbridgeTown_Lab_1F_DeliverPackage_Text_7:
	.string "It looks like you're ready to depart and\n"
	.string "take on the Azoria Gym Challenge!\p"
	.string "Go, {PLAYER}! Rare Pokémon and new\n"
	.string "friends await!\p"
	.string "You should say goodbye to your family\n"
	.string "before you leave.$"

LumbridgeTown_Lab_1F_Professor_Text_0:
	.string "So much to do. Let's see…$"

LumbridgeTown_Lab_1F_Professor_Text_1:
	.string "Have you said bye to your family yet?$"

LumbridgeTown_Lab_1F_Professor_Text_2:
	.string "Rare Pokémon and new friends await!$"

LumbridgeTown_Lab_1F_Assistant_Text_0:
	.string "Congratulations, {PLAYER}.$"

LumbridgeTown_Lab_1F_Assistant_Text_1:
	.string "Feel free to stop by during your\n"
	.string "journey to learn more about our Poké\l"
	.string "Ball-related discoveries.$"

LumbridgeTown_Lab_1F_Scientist1_Text_0:
	.string "Ah! Goodness…y-you startled me.\p"
	.string "I'm trying to put this Poké Ball\n"
	.string "together but I think I'm missing a\l"
	.string "piece…$"

LumbridgeTown_Lab_1F_Scientist2_Text_0:
	.string "Greetings! You're {PLAYER}, yeah?\p"
	.string "We've been expecting you!$"

LumbridgeTown_Lab_1F_Scientist2_Text_1:
	.string "Congratulations on becoming a Pokémon\n"
	.string "Trainer, {PLAYER}!$"

LumbridgeTown_Lab_1F_Scientist2_Text_2:
	.string "Good luck taking on the Gym Challenge,\n"
	.string "{PLAYER}!$"
