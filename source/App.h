#pragma once
#include "Playlist.h"
#include "Settings.h"
#include "AppLog.h"
#include "TimeColors.h"

#include <SFML/Window/Event.hpp>  // input, use own enum?
#include <memory>
#include <vector>

class Audio;


class App : public LogErr
{
public:
    App();
	virtual ~App();

    virtual bool Run() = 0;

protected:
	
	Settings set;
	//ViewSet view;  // in set
	TimeClrSets timeColors;
	//std::unique_ptr<Skin> skin;  // todo:
	
	std::unique_ptr<Audio> audio;

	bool Init();
	bool Destroy();

	
	///  PlayLists Tabs  ------------------------------------------------
	std::vector<Playlist> vPls;  // always at least 1
	Playlist& Pls() {  return vPls[plsId];  }
	void LoadPls(), SavePls();  // for set
	Stats all, allFull;
	
	int plsId = 0, plsPlId = 0,  // current, playing
		plsSelId = -1,  // selected, copy from
		nTabMov = -1;
	
	void LoadState(), SaveState();  // set.st
	bool Play(bool set);
	
	void TabNext(int i, bool row, bool ofs);
	void TabMove(int n);
	void TabNew(int m);
	void TabClose();
	
	
	//void plsChg(int clrSel=0), plsPlChg(int id);
	//void updSelId(int clear=0), clrSelId();
	void OpenDirFile(bool files, Playlist::EInsert where = Playlist::Ins_End);
	
	std::string sFind;
	bool bFind = false;  // hide
	int iFoundAll = 0, iFoundVis = 0;
	void Find();
	
	
	///  Input  ------------------------------------------------
	//  keys
	bool alt = false, ctrl = false, shift = false;
	void UpdModifiers();
	bool KeyDown(sf::Event::KeyEvent key);

	enum EWndOpt
	{	WO_PlsFind, WO_PlsFilter, WO_PlsTab, WO_AppTabs,
		WO_AppShow, WO_AppAudio, WO_AppVis,
		WO_AppTest, WO_AppAbout, WO_Main,
		// todo: WO_AppHotKeys, WO_AppKeys, global hotkeys, app key binds
		// todo: theme, time colors,
		WO_All  };
	virtual void WndOpen(EWndOpt type) = 0;


	//  mouse pos
	int xMpos=0,yMpos=0, xMold=0,yMold=0;  //, xWclick,yWclick
	int xm=0,ym=0, xms=0,yms=0;  // pos,old
	
	//  mmb vars
	int xMs=0,yMs=0, yM_visH=0, xL_ofs=0,yL_sl=0;
	float mti=0.f, mtiv=0.f;

	//  buttons, s old state
	bool bLs=false,bL=false, bRs=false,bR=false, bMs=false,bM=false;
	bool bL_sl=false;
	
	int iDraw = 2;  // clean and redraw, when needed
	void Redraw() {  iDraw = 2;  }
	
	void Mouse();  // process, update
	void Mouse(int x, int y)
	{	xMpos = x;  yMpos = y;  }
	void Wheel(int d);
	void MouseDown(int b);
	void MouseUp(int b);

	
	//  Toggle
	float dt = 0.1f;   // frame time, ms
	bool bFps = false;   // show Fps
	bool bDebug = true; // show debug text
	int iTimeTest = 0;   // test pls time colors

	bool bAllStats = false;  // all playlists
	bool bFullStats = false;  // unfiltered
	

	//  Osd  ----
	//  short info msg on player
	std::string osdStr = "";
	float dtOsd = 0.f, dtOsdShow = 1.f;
	void Osd(std::string msg);
	
	
	///  Dimensions  ------------------------------------------------
	//  B = begin  E = end  W = width  H = height
	int yB_inf=0,  // file info
		yE_plr_btn=0,  // player buttons |< >|
		
		yB_vis=0,yE_vis=0,  // visualization
		yB_pos=0,yE_pos=0;  // seek pos bar
	float xW_pos = 0.03f;  // seek marker
		
		//  pls tabs, size
	int yB_tabs=0,yE_tabs=0,
		xW_tabs=0,yH_tabs=0,
		xW_tabs_btn=0,  // tabs btns ^ v
		
		//  pls header
		yB_pl_inf=0, xE_pl_inf=0,  // info
		xM_pl_filt=0,  // filter / * middle
		//  pls tracks
		yB_pl=0,yE_pl=0, yH_pl=0,
		yL_pl = 10,  // playlist view lines, auto set
		xWex_plS=0;  // extra width for slider drag
	
	void UpdDim();
};
