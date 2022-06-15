#include "global.h"
#include "main.h"
#include "battle.h"
#include "bg.h"
#include "contest_effect.h"
#include "data.h"
#include "event_data.h"
#include "field_screen_effect.h"
#include "gpu_regs.h"
#include "crafting.h"
#include "list_menu.h"
#include "malloc.h"
#include "menu.h"
#include "menu_helpers.h"
#include "menu_specialized.h"
#include "overworld.h"
#include "palette.h"
#include "pokemon_summary_screen.h"
#include "script.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "item.h"
#include "item_icon.h"
#include "item_menu.h"
#include "constants/items.h"
#include "recipes.h"

#define MENU_STATE_FADE_TO_BLACK                    0
#define MENU_STATE_WAIT_FOR_FADE                    1
#define MENU_STATE_UNREACHABLE                      2
#define MENU_STATE_SETUP                            3
#define MENU_STATE_IDLE                             4
#define MENU_STATE_PRINT_CRAFT_PROMPT               5
#define MENU_STATE_CRAFT_CONFIRM                    6
#define MENU_STATE_PRINT_GIVE_UP_PROMPT             7
#define MENU_STATE_GIVE_UP_CONFIRM                  8
#define MENU_STATE_FADE_AND_RETURN                  9
#define MENU_STATE_RETURN_TO_FIELD                  10
#define MENU_STATE_PRINT_TEXT_THEN_FANFARE          11
#define MENU_STATE_WAIT_FOR_FANFARE                 12
#define MENU_STATE_WAIT_FOR_A_BUTTON                13

static EWRAM_DATA struct
{
    u8 state;
    u8 numMenuChoices;
    u8 numToShowAtOnce;
    u8 craftListMenuTask;
    u8 craftListScrollArrowTask;
    u8 craftDisplayArrowTask;
    u16 scrollOffset;
    struct ListMenuItem menuItems[16];
    const u16 *itemList;
} *sCraftingStruct = {0};

static EWRAM_DATA struct {
    u16 listOffset;
    u16 listRow;
} sCraftMenuState = {0};

static const struct BgTemplate sCraftMenuMenuBackgroundTemplates[] =
{
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0,
    },
    {
        .bg = 1,
        .charBaseIndex = 0,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0,
    },
};

static const struct ItemRecipe sTempRecipes[] =
{
    {ITEM_SUPER_POTION, {{ITEM_POTION, 2}}}
};

static void ShowCraftText(const u8 *str);
static void DoCraftMain(void);
static void CreateUISprites(void);
static void CB2_CraftMain(void);
static void Task_WaitForFadeOut(u8 taskId);
static void CB2_InitCraft(void);
//static void CB2_InitLearnMoveReturnFromSelectMove(void);
static void InitCraftBackgroundLayers(void);
static void AddScrollArrows(void);
static void HandleInput(u8);
static void ShowItemDesc(u8);
static s32  GetCurrentSelectedItem(void);
static void FreeCraftResources(void);
static void RemoveScrollArrows(void);
//static void HideHeartSpritesAndShowTeachMoveText(bool8);

#include "data/recipes.h"

static void VBlankCB_Crafting(void)
{
    //LoadOam();
    //ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void OpenCraftingMenu(void)
{
    ScriptContext2_Enable();
    CreateTask(Task_WaitForFadeOut, 10);
    // Fade to black
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 0x10, RGB_BLACK);
}

static void Task_WaitForFadeOut(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(CB2_InitCraft);
        gFieldCallback = FieldCB_ContinueScriptHandleMusic;
        DestroyTask(taskId);
    }
}

static void CB2_InitCraft(void)
{
    ResetSpriteData();
    FreeAllSpritePalettes();
    ResetTasks();
    ClearScheduledBgCopiesToVram();
    SetVBlankCallback(VBlankCB_Crafting);

    InitCraftBackgroundLayers();
    InitCraftWindows(FALSE);

    sCraftMenuState.listOffset = 0;
    sCraftMenuState.listRow = 0;
    
    sCraftingStruct->craftListMenuTask = ListMenuInit(&gMultiuseListMenuTemplate, sCraftMenuState.listOffset, sCraftMenuState.listRow);
    FillPalette(RGB_BLACK, 0, 2);
    SetMainCallback2(CB2_CraftMain);
}

static void InitCraftBackgroundLayers(void)
{
    ResetVramOamAndBgCntRegs();
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sCraftMenuMenuBackgroundTemplates, ARRAY_COUNT(sCraftMenuMenuBackgroundTemplates));
    ResetAllBgsCoordinates();
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 |
                                  DISPCNT_OBJ_1D_MAP |
                                  DISPCNT_OBJ_ON);
    ShowBg(0);
    ShowBg(1);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
}

static void CB2_CraftMain(void)
{
    DoCraftMain();
    RunTasks();
    //AnimateSprites();
    //BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void FormatAndPrintText(const u8 *src)
{
    StringExpandPlaceholders(gStringVar4, src);
    CraftPrintText(gStringVar4);
}

static void DoCraftMain(void)
{
    switch (sCraftingStruct->state)
    {
        case MENU_STATE_FADE_TO_BLACK:
            sCraftingStruct->state++;
            ShowCraftText(gText_CraftWhat);
            BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
            break;
        case MENU_STATE_WAIT_FOR_FADE:
            if (!gPaletteFade.active)
            {
                sCraftingStruct->state = MENU_STATE_IDLE;
            }
            break;
        case MENU_STATE_UNREACHABLE:
            sCraftingStruct->state++;
            break;
        case MENU_STATE_SETUP:
            ShowCraftText(gText_CraftWhat);
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

                if (selection == 0)
                {
                    if (CanCraftItem(GetCurrentSelectedItem()) == TRUE)
                    {
                        if (AddBagItem(GetCurrentSelectedItem(), 1) == TRUE)
                        {
                            ShowCraftText(gText_CraftSuccess);
                            CraftLoadMaterials(GetCurrentSelectedItem());
                            sCraftingStruct->state = MENU_STATE_WAIT_FOR_A_BUTTON;
                        }
                        else
                        {
                            ShowCraftText(gText_NoMoreRoomForThis);
                            sCraftingStruct->state = MENU_STATE_WAIT_FOR_A_BUTTON;
                        }
                    }
                    else
                    {
                        ShowCraftText(gText_CraftFail);
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
                    sCraftingStruct->state = MENU_STATE_FADE_AND_RETURN;
                }
                else if (selection == -1 || selection == 1)
                {
                    sCraftingStruct->state = MENU_STATE_SETUP;
                }
            }
            break;
        case MENU_STATE_FADE_AND_RETURN:
            BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
            sCraftingStruct->state++;
            break;
        case MENU_STATE_RETURN_TO_FIELD:
            if (!gPaletteFade.active)
            {
                FreeCraftResources();
                SetMainCallback2(CB2_ReturnToField);
            }
            break;
        //case MENU_STATE_PRINT_TEXT_THEN_FANFARE:
        //    break;
        //case MENU_STATE_WAIT_FOR_FANFARE:
        //    break;
        case MENU_STATE_WAIT_FOR_A_BUTTON:
            if (JOY_NEW(A_BUTTON))
            {
                PlaySE(SE_SELECT);
                sCraftingStruct->state = MENU_STATE_SETUP;
            }
            break;
    }
}

static void FreeCraftResources(void)
{
    DestroyListMenuTask(sCraftingStruct->craftListMenuTask, &sCraftMenuState.listOffset, &sCraftMenuState.listRow);
    FreeAllWindowBuffers();
    FREE_AND_SET_NULL(sCraftingStruct);
    ResetSpriteData();
    FreeAllSpritePalettes();
}

static void ShowCraftText(const u8 *str)
{
    StringExpandPlaceholders(gStringVar4, str);
    FillWindowPixelBuffer(3, 0x11);
    AddTextPrinterParameterized(3, FONT_NORMAL, gStringVar4, 0, 1, 0, NULL);
}

static void HandleInput(bool8 showContest)
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

static s32 GetCurrentSelectedItem(void)
{
    return sCraftingStruct->menuItems[sCraftMenuState.listRow + sCraftMenuState.listOffset].id;
}

static void SetCraftableItems(const u16 *items)
{
    u16 i = 0;
    u16 itemId;

    sCraftingStruct = AllocZeroed(sizeof(*sCraftingStruct));
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

void CreateCraftingMenu(const u16 *itemsToCraft)
{
    SetCraftableItems(itemsToCraft);
    OpenCraftingMenu();
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