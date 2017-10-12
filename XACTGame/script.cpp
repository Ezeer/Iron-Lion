#include "script.h"



//extern
 RENDER_STATE        g_Render;
 lua_State* Lua;
 MenuPageLua MenuOpt;
 MenuPageLua InputOpt;
 MenuPageLua VideoOpt;
 MenuPageLua AudioOpt;

 CDXUTTextHelper *txtHelper;
 
 
void InitTextHelper(CDXUTTextHelper *txtHelper,D3DXCOLOR cl)
 {
	txtHelper= new CDXUTTextHelper(g_Render.pFont,g_Render.pTextSprite,15 );
    txtHelper->Begin();
    txtHelper->SetInsertionPos( 2, 0 );
    txtHelper->SetForegroundColor( cl );
	txtHelper->End();
	
 }
void initLua()
{
	Lua = luaL_newstate();
    luaL_dofile(Lua, "script.lua");
    luaL_openlibs(Lua);
    lua_pcall(Lua, 0, 0, 0);
    D3DXCOLOR cl=D3DXCOLOR( 1.0f, 1.0f, 0.0f, 1.0f );
	InitTextHelper(txtHelper,cl);

}
void Lua_loadGuiMenu(int type)
{
	char* Name=NULL;
	MenuPageLua page;
	switch(type)
	{
	case MENU_VIDEO :
		Name="VideoMenuOption";break;
	case MENU_AUDIO :
		Name="AudioMenuOption";break;
	case MENU_INPUT :
		Name="InputMenuOption";break;
	case MENU_MAIN:
		Name="MainMenuOption";break;
	}
	
	LuaRef t = getGlobal(Lua,Name);
	//TITLE
    LuaRef title = t["title"];
	std::string txt = title.cast<std::string>();
	std::wstring wide_string = std::wstring(txt.begin(),txt.end());
    page.Title = wide_string.c_str();
    //POSITION
    LuaRef w = t["x"];
    LuaRef h = t["y"];
	//fill the C++ struct now
	page.splash=false;
	page.x = w.cast<int>();
    page.y = h.cast<int>();
	//SIZE
    LuaRef width = t["width"];
    LuaRef height = t["height"];
	//fill the C++ struct now
	page.width =width.cast<int>();
    page.height = height.cast<int>();
	//4 CORNERS COLORS
	//topleft
	LuaRef TopLeftClr = t["TopLeftClr"];
	LuaRef r = TopLeftClr["r"];
    LuaRef g = TopLeftClr["g"];
	LuaRef b = TopLeftClr["b"];
    LuaRef a = TopLeftClr["a"];
	page.Topleft =D3DCOLOR_ARGB( r.cast<int>(),g.cast<int>(),b.cast<int>(), a.cast<int>() ) ;
   //topright
	LuaRef TopRightClr = t["TopRightClr"];
	 r = TopRightClr["r"];
     g = TopRightClr["g"];
	 b = TopRightClr["b"];
     a = TopRightClr["a"];
	 page.Topright =D3DCOLOR_ARGB( r.cast<int>(),g.cast<int>(),b.cast<int>(), a.cast<int>() ) ;
    //BottomLeftClr
	LuaRef BottomLeftClr = t["BottomLeftClr"];
	 r = BottomLeftClr["r"];
     g = BottomLeftClr["g"];
	 b = BottomLeftClr["b"];
     a = BottomLeftClr["a"];
	 page.Bottomleft =D3DCOLOR_ARGB( r.cast<int>(),g.cast<int>(),b.cast<int>(), a.cast<int>() ) ;
    //BottomRightClr
	LuaRef BottomRightClr = t["BottomRightClr"];
	 r = BottomRightClr["r"];
     g = BottomRightClr["g"];
	 b = BottomRightClr["b"];
     a = BottomRightClr["a"];
	 page.Bottomright =D3DCOLOR_ARGB( r.cast<int>(),g.cast<int>(),b.cast<int>(), a.cast<int>() ) ;
   switch(type)
	{
	case MENU_VIDEO :
		VideoOpt=page;break;
	case MENU_AUDIO :
		AudioOpt=page;break;
	case MENU_INPUT :
		InputOpt=page;break;
	case MENU_MAIN:
		MenuOpt=page;break;
	}
}
void Lua_OPT_DLG_SetBgColor(CDXUTDialog *dialog,MenuPageLua* page)
{
	dialog->SetBackgroundColors(page->Topleft,page->Topright,page->Bottomleft,page->Bottomright );
}
		 

void Lua_OPT_DLG_SetSize(CDXUTDialog *dialog,MenuPageLua* page)
{
   dialog->SetSize( page->width, page->height );
}
void Lua_OPT_DLG_SetLocation(const D3DSURFACE_DESC* pBackBufferSurfaceDesc,CDXUTDialog *dialog,MenuPageLua* page)
{
	if(!page->splash)
    dialog->SetLocation( ( pBackBufferSurfaceDesc->Width - page->x) / 2,
     ( pBackBufferSurfaceDesc->Height - page->y ) / 2 );
	else
		dialog->SetLocation( 0,0);

}

						


void quitLua()
{
txtHelper=NULL;delete txtHelper;
}
void printLuaMessage() 
{
   // std::cout << s << std::endl;
}

void Lua_RenderText(ID3DXFont* pFont,ID3DXSprite* pTextSprite,D3DXCOLOR cl)
{
    CDXUTTextHelper txtHelper(g_Render.pFont,g_Render.pTextSprite,15 );
    txtHelper.Begin();
    txtHelper.SetInsertionPos( 2, 0 );
    txtHelper.SetForegroundColor( cl );
	txtHelper.End();
    txtHelper.Begin();
    txtHelper.DrawTextLine( DXUTGetFrameStats( true ) );
    txtHelper.DrawTextLine( DXUTGetDeviceStats() );
  
	//LUA REDESIGN
	
	getGlobalNamespace(Lua).addFunction("printMessage", printLuaMessage);
    //we don't load the script because it should be in memory
	//luaL_dofile(Lua, "script.lua");
    lua_pcall(Lua, 0, 0, 0);
    LuaRef output = getGlobal(Lua, "output");
    int result = output(5, 4);
	txtHelper.DrawTextLine( L" Lua console" );
    txtHelper.DrawFormattedTextLine( L"Lua say : %d",result  );
    txtHelper.End();
}

void Lua_loadSplash()
{
	LuaRef t = getGlobal(Lua,"SplashScreen");
	//TITLE
    LuaRef title = t["title"];
	std::string txt = title.cast<std::string>();
	std::wstring wide_string = std::wstring(txt.begin(),txt.end());
   
    //POSITION
    LuaRef w = t["x"];
    LuaRef h = t["y"];
	
	//SIZE
    LuaRef width = t["width"];
    LuaRef height = t["height"];
	//fill the C++ struct now
	
	
}