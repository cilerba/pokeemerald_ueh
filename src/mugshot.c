#include "global.h"
#include "blit.h"
#include "window.h"
#include "menu.h"
#include "palette.h"
#include "event_data.h"
#include "constants/mugshots.h"

#define MUGSHOT_PALETTE_NUM 13
#define MUGSHOT_X 21
#define MUGSHOT_Y 9
#define MUGSHOT_SIZE 40 // Used for width and height

struct Mugshot{
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    const u32* image;
    const u16* palette;
};

void DrawMugshot(void); //VAR_0x8000 = mugshot id
void DrawMugshotAtPos(void); //VAR_0x8000 = mugshot id, VAR_0x8001 = x, VAR_0x8002 = y
void ClearMugshot(void);

static const u32 sMugshotImg_Larch[] = INCBIN_U32("graphics/mugshots/larch.4bpp.lz");
static const u16 sMugshotPal_Larch[] = INCBIN_U16("graphics/mugshots/larch.gbapal");

static const u32 sMugshotImg_Clyde[] = INCBIN_U32("graphics/mugshots/clyde.4bpp.lz");
static const u16 sMugshotPal_Clyde[] = INCBIN_U16("graphics/mugshots/clyde.gbapal");

static const struct Mugshot sMugshots[] = {
    [MUGSHOT_LARCH] = {
        .x = MUGSHOT_X,
        .y = MUGSHOT_Y,
        .width = MUGSHOT_SIZE,
        .height = MUGSHOT_SIZE,
        .image = sMugshotImg_Larch,
        .palette = sMugshotPal_Larch},
    [MUGSHOT_CLYDE] = {
        .x = MUGSHOT_X,
        .y = MUGSHOT_Y,
        .width = MUGSHOT_SIZE,
        .height = MUGSHOT_SIZE,
        .image = sMugshotImg_Clyde,
        .palette = sMugshotPal_Clyde},
};


//WindowId + 1, 0 if window is not open
static EWRAM_DATA u8 sMugshotWindow = 0;

void ClearMugshot(void){
    if(sMugshotWindow != 0){
        ClearStdWindowAndFrameToTransparent(sMugshotWindow - 1, 0);
        CopyWindowToVram(sMugshotWindow - 1, 3);
        RemoveWindow(sMugshotWindow - 1);
        sMugshotWindow = 0;
    }
}

static void DrawMugshotCore(const struct Mugshot* const mugshot, int x, int y){
    struct WindowTemplate t;
    u16 windowId;
    
    if(sMugshotWindow != 0){
        ClearMugshot();
    }
    
    #if GAME_VERSION==VERSION_EMERALD
    SetWindowTemplateFields(&t, 0, x, y, mugshot->width/8, mugshot->height/8, MUGSHOT_PALETTE_NUM, 0x40);
    #else
    t = SetWindowTemplateFields(0, x, y, mugshot->width/8, mugshot->height/8, MUGSHOT_PALETTE_NUM, 0x40);
    #endif
    windowId = AddWindow(&t);
    sMugshotWindow = windowId + 1;
    
    LoadPalette(mugshot->palette, 16 * MUGSHOT_PALETTE_NUM, 32);
    CopyToWindowPixelBuffer(windowId, (const void*)mugshot->image, 0, 0);
    PutWindowRectTilemap(windowId, 0, 0, mugshot->width/8, mugshot->height/8);
    CopyWindowToVram(windowId, 3);
}

void DrawMugshot(void){
    const struct Mugshot* const mugshot = sMugshots + VarGet(VAR_0x8000);
    DrawMugshotCore(mugshot, mugshot->x, mugshot->y);
}

void DrawMugshotAtPos(void){
    DrawMugshotCore(sMugshots + VarGet(VAR_0x8000), VarGet(VAR_0x8001), VarGet(VAR_0x8002));
}