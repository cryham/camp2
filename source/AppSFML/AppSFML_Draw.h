#pragma once
#include "../App/App.h"
#include "../App/AppConst.h"
#include "../System/defines.h"
#include "../Settings/Settings.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>


class AppSFMLDraw : public App
{
public:
	AppSFMLDraw();
	bool Run();

protected:
	//  Run stages
	void CreateWindow();
	bool LoadResources(), CreateTextures(), LoadFonts();
	
	void LoopMain();
	void DestroyAll();

	//  Draw stages
	void DrawAll();
	void DrawPlayer(), DrawVisual(), DrawTabs();
	void DrawPlaylist(), DrawPls_1Names(), DrawPls_2Times(), DrawPls_3Cursors();
	void DrawPls_Header(), DrawPls_Slider();
	std::vector<int> plsTxtW;  // pls text widths temp
	const static int ciMaxScreenX = 8192;

	//  Views
	int iLastView = 0;
	void UpdateView(bool load, int v) override;
	void SetViewFromWnd();  // after resize and before save
	
	
	//  Windows Gui
	//----------------------------------------------------
	typedef std::unique_ptr<sf::RenderWindow> PWindow;
	PWindow pWindow = nullptr;  // main window

	//  Options windows
	PWindow vWindows[WO_All] = {nullptr,};
	struct SWndConst
	{
		std::string group = "no group";
		std::string title = "no title";
		std::string FullTitle() const
		{	return group + " - " + title;  }
		int width = 400, height = 300;
	};
	const static SWndConst wndConst[WO_All];

	bool wndInited = false;
	EWndOpt wndOpen = WO_All;  // open next from Main
	bool wndFocus = false;  // after show
	int wndSizeX = 400, wndSizeY = 300;  // actual dims
	void WndFocus();

	void WndOpen(EWndOpt type, bool center = true) override;
	bool WndVisible(EWndOpt w);
	void WndProcessAll();
	void WndClose(int w);
	
	void WndDrawAll(sf::Time time);
	void WndDraw_PlsFind(), WndDraw_PlsFilter(), WndDraw_PlsTab(), WndDraw_AppTabs();
	void WndDraw_AppView(), WndDraw_AppStats(), WndDraw_AppAudio(), WndDraw_AppVis();
	void WndDraw_AppTest(), WndDraw_AppAbout(), WndDraw_Main();

	
	//  Resources
	//----------------------------------------------------
	std::unique_ptr<sf::Texture> pTexture = nullptr, pVisTexture = nullptr;
	std::unique_ptr<sf::Sprite> pBackgr = nullptr, pVisSprite = nullptr;  // vis spectrogram

	std::unique_ptr<sf::Font> pFont[Fnt_All] = {nullptr};
	sf::Text text[Fnt_All];
	sf::Image icon;
	
	
	//  text and color
	//--------------------------
	sf::String str;
	sf::Color clr;
	bool bold = false;

	void Clr(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b)
	{
		clr = sf::Color(r,g,b);
	}
	sf::String Str(const std::string& s);

	///  draw utils
	//----------------------------------------------------
	//  write out text, from str
	//  returns width, x advance
	int Text(EFont n, int x, int y, bool draw=true);

	void Format(const char* format, ...);
	
	
	//  draw textured rect, stretched at
	//  x,y pos, width,height,  texture coords uv start,size,  color rgb
	void RectUV(int x, int y, int w, int h,  int ux, int uy, int uw, int uh,  bool add=false,
			  sf::Uint8 r=255, sf::Uint8 g=255, sf::Uint8 b=255);
	void Rect(int x, int y, int w, int h,  ETexUV uv,  bool add=false,
			  sf::Uint8 r=255, sf::Uint8 g=255, sf::Uint8 b=255);

	
	///  Gui utils
	//--------------------------
	void TextG(const char* s);
	void TextG(std::string s);
	void Sep(int h), Line();  // separators

	//  Text:   value  [Slider],  same line as if > 0
	int xText = 0, xSlider = 0;
	void SliderValue(const std::string& text, const std::string& val);
	
	bool SliderF(float& val, float vmin, float vmax,
				 const std::string& text, const std::string& uid, const std::string& value="");
	bool SliderI(int& val, float vmin, float vmax,
				 const std::string& text, const std::string& uid, const std::string& value="");

	void SetupGuiStyle();  // ImGui theme
};
