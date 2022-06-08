Route1_MapScripts::
	.byte 0


Route1_Sign::
	lock
	msgbox Route1_Sign_Text_0
	release
	end


Route1_Lass::
	lock
	faceplayer
	msgbox Route1_Lass_Text_0
	release
	end


Route1_Ledge::
	lock
	faceplayer
	msgbox Route1_Ledge_Text_0
	release
	end


Route1_Potion::
	lock
	faceplayer
	goto_if_unset FLAG_RECEIVED_POTION_ROUTE1, Route1_Potion_2
	msgbox Route1_Potion_Text_2
Route1_Potion_1:
	closemessage
	release
	end

Route1_Potion_2:
	msgbox Route1_Potion_Text_0
	waitmessage
	giveitem ITEM_POTION
	compare VAR_RESULT, FALSE
	goto_if_eq Route1_Potion_5
	setflag FLAG_RECEIVED_POTION_ROUTE1
	msgbox Route1_Potion_Text_2
	goto Route1_Potion_1

Route1_Potion_5:
	msgbox Route1_Potion_Text_1
	goto Route1_Potion_1


Route1_Sign_Text_0:
	.string "Route 1$"

Route1_Lass_Text_0:
	.string "Route 1 used to be populated largly by\n"
	.string "Wooloo until all the Poochyena came.\p"
	.string "Now they've all migrated to Route 2.$"

Route1_Ledge_Text_0:
	.string "Want to know something wicked?\p"
	.string "You can get some sick airtime by\n"
	.string "hopping over this ledge.\p"
	.string "It also makes it easier to get to\n"
	.string "Lumbridge Town!$"

Route1_Potion_Text_0:
	.string "Hello potential customer!\p"
	.string "My name is Marty and I'm here handing\n"
	.string "out free Poké Mart samples.\p"
	.string "One for you!$"

Route1_Potion_Text_1:
	.string "Come back when your bag isn't full, OK?$"

Route1_Potion_Text_2:
	.string "Use that Potion to heal your Pokémon!$"
