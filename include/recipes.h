#ifndef GUARD_RECIPES_H
#define GUARD_RECIPES_H

#define MATERIAL_LENGTH 4

struct ItemRecipe
{
    u16 outputId;
    struct ItemSlot materials[MATERIAL_LENGTH];
};

extern const struct ItemRecipe gRecipes[];

#endif //GUARD_RECIPES_H
