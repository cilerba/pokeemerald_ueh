IreniaTown_House1_MapScripts::
	.byte 0


IreniaTown_House1_NPCWoman::
	lock
	faceplayer
	msgbox IreniaTown_House1_NPCWoman_Text_0
	release
	end


IreniaTown_House1_NPCChild::
	lock
	faceplayer
	bufferleadmonspeciesname 0
	msgbox IreniaTown_House1_NPCChild_Text_0
	release
	end


IreniaTown_House1_NPCWoman_Text_0:
	.string "I was walking with my Zigzagoon and\n"
	.string "found it holding an item.\p"
	.string "I wonder if it's related to its Pickup\n"
	.string "ability.$"

IreniaTown_House1_NPCChild_Text_0:
	.string "Wow! Is that a\n"
	.string "{STR_VAR_1}?\p"
	.string "That's so cool! I'm going to have my own\n"
	.string "Pokémon one day.$"
