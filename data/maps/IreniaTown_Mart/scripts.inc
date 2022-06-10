IreniaTown_Mart_MapScripts::
	.byte 0


IreniaTown_Mart_Clerk::
	lock
	faceplayer
	switch VAR_LUMBRIDGEPLAYER_STATE
	case 2, IreniaTown_Mart_Clerk_3
	case 3, IreniaTown_Mart_Clerk_4
	case 4, IreniaTown_Mart_Clerk_5
IreniaTown_Mart_Clerk_5:
	msgbox IreniaTown_Mart_Clerk_Text_2
	waitmessage
	pokemart IreniaTown_Mart_Mart
	msgbox gText_PleaseComeAgain
IreniaTown_Mart_Clerk_1:
	release
	end

IreniaTown_Mart_Clerk_3:
	msgbox IreniaTown_Mart_Clerk_Text_0
	closemessage
	applymovement 1, IreniaTown_Mart_ClerkMove
	waitmovement 1
	giveitem ITEM_PARCEL, 1
	waitmessage
	msgbox IreniaTown_Mart_Clerk_Text_1
	closemessage
	setvar VAR_LUMBRIDGEPLAYER_STATE, 3
	goto IreniaTown_Mart_Clerk_1

IreniaTown_Mart_Clerk_4:
	msgbox IreniaTown_Mart_Clerk_Text_1
	closemessage
	goto IreniaTown_Mart_Clerk_1


IreniaTown_Mart_Mart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_NONE
	release
	end

IreniaTown_Mart_ClerkMove:
	face_up
	delay_16
	delay_16
	delay_16
	face_down
	delay_16
	delay_16
	delay_16
	face_left
	delay_16
	delay_16
	emote_exclamation_mark
	delay_16
	delay_16
	delay_16
	walk_left
	delay_16
	walk_in_place_left
	delay_16
	walk_right
	face_player
	step_end

IreniaTown_Mart_Clerk_Text_0:
	.string "Welcome!\pHow may I serve you?\pYou're here for a package?\pOne moment.$"

IreniaTown_Mart_Clerk_Text_1:
	.string "Say hello to Professor Larch for me!$"

IreniaTown_Mart_Clerk_Text_2:
	.string "Welcome!\pHow may I serve you?$"
