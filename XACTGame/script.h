
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}//LUA

#include <LuaBridge.h>
#include <stdarg.h>
#include <stddef.h>

#include "DXUT.h"

#define MENU_MAIN 0
#define MENU_VIDEO 1
#define MENU_AUDIO 2
#define MENU_INPUT 3

//global state
using namespace luabridge;
extern lua_State* Lua;
void initLua();
extern struct MenuPageLua{ const wchar_t*  Title;
                   int x; 
				   int y;
				   int width;
				   int height;
				   D3DCOLOR Topleft;
				   D3DCOLOR Topright;
				   D3DCOLOR Bottomleft;
				   D3DCOLOR Bottomright;};

extern MenuPageLua MenuOpt;
extern MenuPageLua InputOpt;
extern MenuPageLua VideoOpt;
extern MenuPageLua AudioOpt;
#include "SDKmisc.h"
#include "game.h"
extern CDXUTTextHelper *txtHelper;

void Lua_loadGuiMenu(int type);
void Lua_RenderText(ID3DXFont* pFont,ID3DXSprite* pTextSprite,D3DXCOLOR cl);  // Sprite for batching draw text calls);
void Lua_OPT_DLG_SetBgColor(CDXUTDialog *dialog,MenuPageLua* page);
void Lua_OPT_DLG_SetSize(CDXUTDialog *dialog,MenuPageLua* page);
void Lua_OPT_DLG_SetLocation(const D3DSURFACE_DESC* pBackBufferSurfaceDesc,CDXUTDialog *dialog,MenuPageLua* page);


						

