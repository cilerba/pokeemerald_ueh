#include "global.h"
#include "strings.h"
#include "bg.h"
#include "data.h"
#include "decompress.h"
#include "event_data.h"
#include "field_screen_effect.h"
#include "field_weather.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "item.h"
#include "item_menu.h"
#include "item_menu_icons.h"
#include "list_menu.h"
#include "item_icon.h"
#include "item_use.h"
#include "international_string_util.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "menu_helpers.h"
#include "palette.h"
#include "party_menu.h"
#include "scanline_effect.h"
#include "script.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text_window.h"
#include "overworld.h"
#include "event_data.h"
#include "constants/items.h"
#include "constants/field_weather.h"
#include "constants/songs.h"
#include "constants/rgb.h"
#include "recipes.h"
#include "crafting.h"

#define MENU_STATE_SETUP                            0
#define MENU_STATE_IDLE                             1
#define MENU_STATE_PRINT_CRAFT_PROMPT               2
#define MENU_STATE_CRAFT_CONFIRM                    3
#define MENU_STATE_PRINT_GIVE_UP_PROMPT             4
#define MENU_STATE_GIVE_UP_CONFIRM                  5
#define MENU_STATE_WAIT_FOR_A_BUTTON                6

static EWRAM_DATA struct
{
    u8 state;
    u8 numMenuChoices;
    u8 numToShowAtOnce;
    u8 craftListMenuTask;
    u8 craftListScrollArrowTask;
    u8 craftDisplayArrowTask;
    u8 gfxLoadState;
    u16 scrollOffset;
    struct ListMenuItem menuItems[16];
    const u16 *itemList;
} *sCraftingStruct = {0};

static EWRAM_DATA struct {
    u16 listOffset;
    u16 listRow;
} sCraftMenuState = {0};

#define WINDOW_LEFT     0
#define WINDOW_RIGHT    1
#define WINDOW_BOTTOM   2
#define WINDOW_YESNO    3

static EWRAM_DATA u8 *sBg1TilemapBuffer = NULL;

//==========STATIC=DEFINES==========//
static void CraftingRunSetup(void);
static bool8 CraftingDoGfxSetup(void);
static bool8 CraftingInitBgs(void);
static void CraftingFadeAndBail(void);
static bool8 CraftingLoadGraphics(void);
static void CraftingInitWindows(void);
static void PrintToWindow(u8 windowId, u8 colorIdx);
static void Task_CraftingWaitFadeIn(u8 taskId);
static void Task_CraftingMain(u8 taskId);
static void CraftingVBlankCB(void);
static void CraftingMainCB(void);
static void Task_WaitForFadeOut(u8 taskId);

static void FormatAndPrintText(const u8 *src);
static void HandleInput();
static s32 GetCurrentSelectedItem(void);
static void SetCraftableItems(const u16 *items);
static u8 LoadCraftItemsList(const struct ListMenuItem *items, u16 numChoices);
static void CraftCursorCallback(s32 itemIndex, bool8 onInit, struct ListMenu *list);
static void CraftLoadMaterials(u32 chosenItem);
static void CraftPrintText(u8 *str);
static bool16 CraftRunTextPrinters(void);
static void CraftCreateYesNoMenu(void);

#include "data/recipes.h"

//==========CONST=DATA==========//
static const struct BgTemplate sCraftMenuMenuBackgroundTemplates[] =
{
    {
        .bg = 0, // Windows
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .priority = 1,
    },
    {
        .bg = 1, // Tilemap
        .charBaseIndex = 3,
        .mapBaseIndex = 30,
        .priority = 2,
    },
};

static const struct WindowTemplate sCraftWindowTemplates[] = 
{
    {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 1,
        .width = 10,
        .height = 12,
        .paletteNum = 0xF,
        .baseBlock = 0x18A
    },
    {
        .bg = 0,
        .tilemapLeft = 13,
        .tilemapTop = 1,
        .width = 16,
        .height = 12,
        .paletteNum = 0xF,
        .baseBlock = 0xCA
    },
    {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 15,
        .width = 28,
        .height = 4,
        .paletteNum = 0xF,
        .baseBlock = 0x202
    },
    {
        .bg = 0,
        .tilemapLeft = 22,
        .tilemapTop = 8,
        .width = 5,
        .height = 4,
        .paletteNum = 0xF,
        .baseBlock = 0x272
    }
};

static const struct WindowTemplate sCraftYesNoMenuTemplate =
{
    .bg = 0,
    .tilemapLeft = 22,
    .tilemapTop = 8,
    .width = 5,
    .height = 4,
    .paletteNum = 0xF,
    .baseBlock = 0x272
};

static const struct ListMenuTemplate sCraftItemsListTemplate =
{
    .items = NULL,
    .moveCursorFunc = CraftCursorCallback,
    .itemPrintFunc = NULL,
    .totalItems = 0,
    .maxShowed = 0,
    .windowId = WINDOW_LEFT,
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 0,
    .cursorPal = TEXT_COLOR_WHITE,
    .fillValue = 0,
    .cursorShadowPal = TEXT_COLOR_DARK_GRAY,
    .lettersSpacing = 0,
    .itemVerticalPadding = 0,
    .scrollMultiple = LIST_NO_MULTIPLE_SCROLL,
    .fontId = FONT_NARROW,
    .cursorKind = 0
};

static const u32 sCraftTiles[] = INCBIN_U32("graphics/crafting/tiles.4bpp.lz");
static const u32 sCraftTilemap[] = INCBIN_U32("graphics/crafting/tilemap.bin.lz");
static const u16 sCraftPalette[] = INCBIN_U16("graphics/crafting/palette.gbapal");

static const u8 sCraftWindowFontColors[][3] = 
{
    {TEXT_COLOR_TRANSPARENT,  TEXT_COLOR_WHITE,  TEXT_COLOR_LIGHT_GRAY},
};


// Entry point
void CraftingInit(const u16 *itemsToCraft)
{
    sCraftingStruct = AllocZeroed(sizeof(*sCraftingStruct));
    sCraftingStruct->gfxLoadState = 0;

    SetCraftableItems(itemsToCraft);
    ScriptContext2_Enable();

    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 0x10, RGB_BLACK);
    CreateTask(Task_WaitForFadeOut, 10);
}

static void Task_WaitForFadeOut(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(CraftingRunSetup);
        gFieldCallback = FieldCB_ContinueScriptHandleMusic;
        DestroyTask(taskId);
    }
}

static void CraftingRunSetup(void)
{
    while (1)
    {
        if (CraftingDoGfxSetup() == TRUE)
            break;
    }
}

static bool8 CraftingDoGfxSetup(void)
{
    u8 taskId;
    switch (gMain.state)
    {
        case 0:
            DmaClearLarge16(3, (void *)VRAM, VRAM_SIZE, 0x1000)
            SetVBlankHBlankCallbacksToNull();
            ClearScheduledBgCopiesToVram();
            gMain.state++;
            break;
        case 1:
            ScanlineEffect_Stop();
            FreeAllSpritePalettes();
            ResetPaletteFade();
            ResetSpriteData();
            ResetTasks();
            gMain.state++;
            break;
        case 2:
            if (CraftingInitBgs())
            {
                sCraftingStruct->gfxLoadState = 0;
                gMain.state++;
            }
            else
            {
                CraftingFadeAndBail();
                return TRUE;
            }
            break;
        case 3:
            if (CraftingLoadGraphics() == TRUE)
                gMain.state++;
            break;
        case 4:
            LoadMessageBoxAndBorderGfx();
            CraftingInitWindows();

            sCraftMenuState.listOffset = 0;
            sCraftMenuState.listRow = 0;
            sCraftingStruct->craftListMenuTask = ListMenuInit(&gMultiuseListMenuTemplate, sCraftMenuState.listOffset, sCraftMenuState.listRow);

            gMain.state++;
            break;
        case 5:
            FormatAndPrintText(gText_CraftWhat);
            taskId = CreateTask(Task_CraftingWaitFadeIn, 0);
            BlendPalettes(0xFFFFFFFF, 16, RGB_BLACK);
            gMain.state++;
            break;
        case 6:
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
            gMain.state++;
            break;
        default:
            SetVBlankCallback(CraftingVBlankCB);
            SetMainCallback2(CraftingMainCB);
            return TRUE;
    }
    return FALSE;
}

#define try_free(ptr) ({        \
    void ** ptr__ = (void **)&(ptr);   \
    if (*ptr__ != NULL)                \
        Free(*ptr__);                  \
})

static void CraftingFreeResources(void)
{
    DestroyListMenuTask(sCraftingStruct->craftListMenuTask, &sCraftMenuState.listOffset, &sCraftMenuState.listRow);
    try_free(sCraftingStruct);
    try_free(sBg1TilemapBuffer);
    FreeAllWindowBuffers();
}


static void Task_CraftingWaitFadeAndBail(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        CraftingFreeResources();
        DestroyTask(taskId);
    }
}

static void CraftingFadeAndBail(void)
{
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    CreateTask(Task_CraftingWaitFadeAndBail, 0);
    SetVBlankCallback(CraftingVBlankCB);
    SetMainCallback2(CraftingMainCB);
}

static bool8 CraftingInitBgs(void)
{
    ResetAllBgsCoordinates();
    sBg1TilemapBuffer = Alloc(0x800);
    if (sBg1TilemapBuffer == NULL)
        return FALSE;
    
    memset(sBg1TilemapBuffer, 0, 0x800);
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sCraftMenuMenuBackgroundTemplates, NELEMS(sCraftMenuMenuBackgroundTemplates));
    SetBgTilemapBuffer(1, sBg1TilemapBuffer);
    ScheduleBgCopyTilemapToVram(0);
    ShowBg(0);
    ShowBg(1);
    return TRUE;
}

static bool8 CraftingLoadGraphics(void)
{
    switch (sCraftingStruct->gfxLoadState)
    {
        case 0:
            ResetTempTileDataBuffers();
            DecompressAndCopyTileDataToVram(1, sCraftTiles, 0, 0, 0);
            sCraftingStruct->gfxLoadState++;
            break;
        case 1:
            if (FreeTempTileDataBuffersIfPossible() != TRUE)
            {
                LZDecompressWram(sCraftTilemap, sBg1TilemapBuffer);
                sCraftingStruct->gfxLoadState++;
            }
            break;
        case 2:
            LoadPalette(sCraftPalette, 0, 32);
            sCraftingStruct->gfxLoadState++;
            break;
        default:
            sCraftingStruct->gfxLoadState = 0;
            return TRUE;
    }
    return FALSE;
}

static void CraftingInitWindows(void)
{
    u32 i;

    InitWindows(sCraftWindowTemplates);
    DeactivateAllTextPrinters();
    ScheduleBgCopyTilemapToVram(0);
    
    FillWindowPixelBuffer(WINDOW_LEFT, 0);
    FillWindowPixelBuffer(WINDOW_RIGHT, 0);
    FillWindowPixelBuffer(WINDOW_BOTTOM, 0);
    LoadUserWindowBorderGfx(WINDOW_YESNO, 720, 14 * 16);
    PutWindowTilemap(WINDOW_LEFT);
    PutWindowTilemap(WINDOW_RIGHT);
    PutWindowTilemap(WINDOW_BOTTOM);
    CopyWindowToVram(WINDOW_LEFT, 3);
    CopyWindowToVram(WINDOW_RIGHT, 3);
    CopyWindowToVram(WINDOW_BOTTOM, 3);

    ScheduleBgCopyTilemapToVram(1);
}

static void CraftingMainCB(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void CraftingVBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void Task_CraftingWaitFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_CraftingMain;
}

static void Task_CraftingTurnOff(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (!gPaletteFade.active)
    {
        SetMainCallback2(CB2_ReturnToField);
        CraftingFreeResources();
        DestroyTask(taskId);
    }
}

/* This is the meat of the UI. This is where you wait for player inputs and can branch to other tasks accordingly */
static void Task_CraftingMain(u8 taskId)
{
    switch (sCraftingStruct->state)
    {
        case MENU_STATE_SETUP:
            FormatAndPrintText(gText_CraftWhat);
            sCraftingStruct->state++;
            break;
        case MENU_STATE_IDLE:
            HandleInput(FALSE);
            break;
        case MENU_STATE_PRINT_CRAFT_PROMPT:
            if (!CraftRunTextPrinters())
            {
                CraftCreateYesNoMenu();
                sCraftingStruct->state++;
            }
            break;
        case MENU_STATE_CRAFT_CONFIRM:
            {
                s8 selection = Menu_ProcessInputNoWrapClearOnChoose();
                u16 selectedItem = GetCurrentSelectedItem();

                if (selection == 0)
                {
                    if (CanCraftItem(selectedItem) == TRUE)
                    {
                        if (AddBagItem(selectedItem, 1) == TRUE)
                        {
                            CopyItemName(selectedItem, gStringVar1);
                            FormatAndPrintText(gText_CraftSuccess);
                            CraftLoadMaterials(selectedItem);
                            sCraftingStruct->state = MENU_STATE_WAIT_FOR_A_BUTTON;
                        }
                        else
                        {
                            FormatAndPrintText(gText_NoMoreRoomForThis);
                            sCraftingStruct->state = MENU_STATE_WAIT_FOR_A_BUTTON;
                        }
                    }
                    else
                    {
                        FormatAndPrintText(gText_CraftFail);
                        sCraftingStruct->state = MENU_STATE_WAIT_FOR_A_BUTTON;
                    }
                }
                else if (selection == MENU_B_PRESSED || selection == 1)
                {
                    sCraftingStruct->state = MENU_STATE_SETUP;
                }
            }
            break;
        case MENU_STATE_PRINT_GIVE_UP_PROMPT:
            if (!CraftRunTextPrinters())
            {
                CraftCreateYesNoMenu();
                sCraftingStruct->state++;
            }
            break;
        case MENU_STATE_GIVE_UP_CONFIRM:
            {
                s8 selection = Menu_ProcessInputNoWrapClearOnChoose();

                if (selection == 0)
                {
                    gSpecialVar_0x8004 = FALSE;
                    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
                    gTasks[taskId].func = Task_CraftingTurnOff;
                }
                else if (selection == -1 || selection == 1)
                {
                    sCraftingStruct->state = MENU_STATE_SETUP;
                }
            }
            break;
        case MENU_STATE_WAIT_FOR_A_BUTTON:
            if (JOY_NEW(A_BUTTON))
            {
                PlaySE(SE_SELECT);
                sCraftingStruct->state = MENU_STATE_SETUP;
            }
    }
}

static void FormatAndPrintText(const u8 *src)
{
    StringExpandPlaceholders(gStringVar4, src);
    CraftPrintText(gStringVar4);
}

static void HandleInput()
{
    s32 itemId = ListMenu_ProcessInput(sCraftingStruct->craftListMenuTask);
    ListMenuGetScrollAndRow(sCraftingStruct->craftListMenuTask, &sCraftMenuState.listOffset, &sCraftMenuState.listRow);

    switch (itemId)
    {
        case LIST_NOTHING_CHOSEN:
            break;
        case LIST_CANCEL:
            PlaySE(SE_SELECT);
            sCraftingStruct->state = MENU_STATE_PRINT_GIVE_UP_PROMPT;
            StringCopy(gStringVar4, gText_CraftCancel);
            CraftPrintText(gStringVar4);
            break;
        default:
            PlaySE(SE_SELECT);
            sCraftingStruct->state = MENU_STATE_PRINT_CRAFT_PROMPT;
            
            CopyItemName(gRecipes[itemId].outputId, gStringVar2);
            
            StringExpandPlaceholders(gStringVar4, gText_CraftConfirm);
            CraftPrintText(gStringVar4);
            break;
    }
}

// Crafting Utilities

static s32 GetCurrentSelectedItem(void)
{
    return sCraftingStruct->menuItems[sCraftMenuState.listRow + sCraftMenuState.listOffset].id;
}

static void SetCraftableItems(const u16 *items)
{
    u16 i = 0;
    u16 itemId;

    sCraftingStruct->numMenuChoices = ARRAY_COUNT(items) - 1;

    for (i = 0; i < sCraftingStruct->numMenuChoices; i++)
    {
        itemId = items[i];
        CopyItemName(gRecipes[itemId].outputId, gStringVar1);
        sCraftingStruct->menuItems[i].name = gStringVar1;
        sCraftingStruct->menuItems[i].id = gRecipes[itemId].outputId;
    }

    sCraftingStruct->menuItems[sCraftingStruct->numMenuChoices].name = gText_Cancel;
    sCraftingStruct->menuItems[sCraftingStruct->numMenuChoices].id = LIST_CANCEL;
    sCraftingStruct->numMenuChoices++;
    sCraftingStruct->numToShowAtOnce = LoadCraftItemsList(sCraftingStruct->menuItems, sCraftingStruct->numMenuChoices);
}

static u8 LoadCraftItemsList(const struct ListMenuItem *items, u16 numChoices)
{
    gMultiuseListMenuTemplate = sCraftItemsListTemplate;
    gMultiuseListMenuTemplate.totalItems = numChoices;
    gMultiuseListMenuTemplate.items = items;

    if (numChoices < 6)
        gMultiuseListMenuTemplate.maxShowed = numChoices;
    else
        gMultiuseListMenuTemplate.maxShowed = 6;

    return gMultiuseListMenuTemplate.maxShowed;
}

static void CraftCursorCallback(s32 itemIndex, bool8 onInit, struct ListMenu *list)
{
    if (onInit != TRUE)
        PlaySE(SE_SELECT);

    CraftLoadMaterials(itemIndex);
}

static void CraftLoadMaterials(u32 chosenItem)
{
    s32 i;
    const struct ItemRecipe *recipe;
    struct TextPrinterTemplate printerTemplate;
    u8 pocket;
    u16 itemId;
    u16 itemBagIndex;
    u8 buffer[32];

    FillWindowPixelBuffer(WINDOW_RIGHT, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));

    if (chosenItem == LIST_CANCEL)
    {
        CopyWindowToVram(WINDOW_RIGHT, COPYWIN_GFX);
        return;
    }

    printerTemplate.windowId = WINDOW_RIGHT;
    printerTemplate.fontId = FONT_NARROW;
    printerTemplate.letterSpacing = gFonts[FONT_NARROW].letterSpacing;
    printerTemplate.lineSpacing = gFonts[FONT_NARROW].lineSpacing;
    printerTemplate.unk = gFonts[FONT_NARROW].unk;
    printerTemplate.fgColor = TEXT_COLOR_WHITE;
    printerTemplate.bgColor = TEXT_COLOR_TRANSPARENT;
    printerTemplate.shadowColor = TEXT_COLOR_DARK_GRAY;

    recipe = &gRecipes[chosenItem];

    for (i = 0; i < MATERIAL_LENGTH; i++)
    {

        if (recipe->materials[i].itemId != ITEM_NONE)
        {
            itemId = recipe->materials[i].itemId;
            printerTemplate.y = i * 16;
            printerTemplate.currentY = i * 16;

            // Print item name
            CopyItemName(recipe->materials[i].itemId, gStringVar1);

            printerTemplate.currentChar = gStringVar1;
            printerTemplate.x = 4;
            printerTemplate.currentX = 4;
            AddTextPrinter(&printerTemplate, 0, NULL);

            // Print Bag Quantity
            ConvertIntToDecimalStringN(gStringVar2, CheckBagQuantity(itemId), STR_CONV_MODE_RIGHT_ALIGN, 2);
            StringAppend(gStringVar2, gText_Slash);
            
            printerTemplate.currentChar = gStringVar2;
            printerTemplate.x = 98;
            printerTemplate.currentX = 98;
            AddTextPrinter(&printerTemplate, 0, NULL);

            // Print Required Quantity
            ConvertIntToDecimalStringN(gStringVar3, recipe->materials[i].quantity, STR_CONV_MODE_RIGHT_ALIGN, 2);

            printerTemplate.currentChar = gStringVar3;
            printerTemplate.x = 116;
            printerTemplate.currentX = 116;
            AddTextPrinter(&printerTemplate, 0, NULL);
        }
    }    
}

static void CraftPrintText(u8 *str)
{
    struct TextPrinterTemplate printerTemplate;

    FillWindowPixelBuffer(WINDOW_BOTTOM, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));

    printerTemplate.currentChar = str;
    printerTemplate.windowId = WINDOW_BOTTOM;
    printerTemplate.fontId = FONT_NORMAL;
    printerTemplate.letterSpacing = gFonts[FONT_NORMAL].letterSpacing;
    printerTemplate.lineSpacing = gFonts[FONT_NORMAL].lineSpacing;
    printerTemplate.unk = gFonts[FONT_NORMAL].unk;
    printerTemplate.x = 0;
    printerTemplate.currentX = 0;
    printerTemplate.y = 1;
    printerTemplate.currentY = 1;
    printerTemplate.fgColor = TEXT_COLOR_WHITE;
    printerTemplate.bgColor = TEXT_COLOR_TRANSPARENT;
    printerTemplate.shadowColor = TEXT_COLOR_DARK_GRAY;

    AddTextPrinter(&printerTemplate, 0, NULL);
}

static bool16 CraftRunTextPrinters(void)
{
    RunTextPrinters();
    return IsTextPrinterActive(3);
}

static void CraftCreateYesNoMenu(void)
{
    CreateYesNoMenu(&sCraftYesNoMenuTemplate, 720, 0xE, 0);
}

bool8 CanCraftItem(u16 itemId)
{
    u8 i;
    u8 itemCount;
    bool8 canCraft = FALSE;

    for (i = 0; i < MATERIAL_LENGTH; i++)
    {
        if (gRecipes[itemId].materials[i].itemId == ITEM_NONE)
        {
            break;
        }

        itemCount = CheckBagQuantity(gRecipes[itemId].materials[i].itemId);

        if (itemCount >= gRecipes[itemId].materials[i].quantity)
        {
            canCraft = RemoveBagItem(gRecipes[itemId].materials[i].itemId, gRecipes[itemId].materials[i].quantity);
            continue;
        } else
        {
            canCraft = FALSE;
            break;
        }
    }

    return canCraft;
}