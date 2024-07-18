#pragma once
////////////////////////////////////////////////
//         MV C++ Performer 专属头文件         //
//          by Wormwaker, 禁止盗用             //
////////////////////////////////////////////////
//本文件是该框架 MV C++ Performer Framework 的入口，包含本文件即可引入整个框架。
//不过要注意的是，在包含本文件 mv_core.h 前，你需要定义一些东西：
//------------------------------------------------
// 宏 PRODUCT_NAME:   用于标识MV名称，日志名称等
// 宏 MV_SCRIPT_PATH: 指定起始脚本路径
//------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#include <iostream>
#include <sstream>
#include <fstream>
#include <Windows.h>
#include <tchar.h>
#include <cmath>
#include <cstdlib>
#include <io.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <ctime>
#include <memory>
#include <algorithm>
#include "graphics.h"
#pragma comment(lib, "graphics17.lib")
#define CJZAPI __stdcall
#define XCPT_L	try{
#define XCPT_R  }catch(exception& e)	\
				{	\
					ErrorLogTip("程序出现异常！理由为：" + string{ e.what() }, __func__);	\
				}

using namespace std;
#define ASSETS_DIR ("../" PRODUCT_NAME "/Assets/")
#define COMMON_DIR ("../Common/")
#define MV_CONTROLLER_PATH (COMMON_DIR+"MVController.exe"s)
#define DEF_UIX 1280
#define DEF_UIY 720
//全局变量
extern bool g_playing = false;
HWND hwnd{ nullptr };
float g_scale{ 1.0f };
float g_base_scale{ 1.0f };
bool show_debug{ false };
string log_path{ "" };
extern int uix = DEF_UIX, uiy = DEF_UIY;
extern int scr_w = 0, scr_h = 0, taskbar_h = 0, caption_h = 0;
clock_t g_beforeTime = 0L, g_bodyTime = 0L, g_afterTime = 0L;
extern PIMAGE imgBuffer{ nullptr };	//缓冲区（尺寸大于屏幕）
//必要的函数声明
void CJZAPI DebugLog(const char* s);
void CJZAPI DebugLog(const string& s);
template <typename _T>
inline void CJZAPI DebugLogA(const _T& value);
int CJZAPI DebugLogFormat(const char* szFormat, ...);
inline int CJZAPI ErrorLogTip(const string& text, const string& moduleName);
//子程序包含
#include "mv_string.h"			//字符串处理				(通用)
#include "mv_math.h"			//数学函数				(通用)
#include "mv_winsys.h"			//Windows系统函数			(通用)
#include "mv_fontmgr.h"			//字体管理器
#include "mv_display.h"			//绘制/呈现通用函数		(半通用)
#include "mv_imgmgr.h"			//图片管理器
#include "mv_bgmgr.h"			//背景管理器
#include "mv_json.h"			//JSON					(通用)
#include "cplayer.h"			//音乐播放器类			(通用)

clock_t drawStart = 0L;
#define DELTA_MS	(clock() - drawStart)
void MV_Unload();

#include "mv_perform.h"				//元素展示
#include "mv_sndmgr.h"				//音频管理器
#include "mv_script.h"				//脚本处理
CPlayer cplayer;					//主音乐播放
#include "mv_control.h"				//与控制器的交互

enum MVStage {		//框架运行阶段
	mvs_init,
	mvs_load,
	mvs_before,
	mvs_start,
	mvs_after,
	mvs_unload,
}g_stage;

void InitLogPath()
{
	log_path = "../Logs/";
	log_path += PRODUCT_NAME;
	log_path += ".LOG";
}
using InitMode = ULONG;
#define INITMODE_DEFAULT		0x00000000UL
#define INITMODE_FULL_BOTTOM	0x00000001UL
#define INITMODE_FULL_SCREEN    0x00000002UL
void MV_Init(const string& caption, InitMode initMode = INITMODE_DEFAULT)
{
	InitLogPath();
	if (!ExistFile("../Logs"))
		CreateDirectoryA("../Logs", NULL);
	if (ExistFile(log_path))
		DeleteFileA(log_path.c_str());
	FILE* fp = fopen(log_path.c_str(), "w");
	if (fp)
		fclose(fp);

	DebugLog("===========================");
	DebugLog("     MV C++ Performer      ");
	DebugLog("  Framework by Wormwaker   ");
	DebugLog("\n* Product Name: " + string{ PRODUCT_NAME });
	DebugLog("===========================");

	DebugLog("MV_Init: 初始化中...");
	g_stage = mvs_init;
	g_scale = GetScreenScaleFactor();
	g_base_scale = g_scale;
	DebugLogFormat("显示器缩放比例：%.0f%%", g_scale*100.0f);
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	//FreeConsole();
	bool xfull = false;
	scr_w = GetScreenWidth();
	scr_h = GetScreenHeight();
	taskbar_h = GetTaskbarHeight();
	caption_h = GetTitleHeight(GetForegroundWindow());

	if (uix > scr_w)	uix = scr_w, xfull = true;
	if (uiy > scr_h - taskbar_h - caption_h) uiy = scr_h - taskbar_h - caption_h;

	if (HaveFlag(initMode, INITMODE_FULL_BOTTOM))
	{
		uix = scr_w;
		uiy = scr_h - caption_h;
	}
	else if (HaveFlag(initMode, INITMODE_FULL_SCREEN))
	{
		uix = scr_w;
		uiy = scr_h;
	}
	else {
		uix = DEF_UIX;
		uiy = DEF_UIY;
	}
	DebugLogFormat("窗口尺寸： uix=%d, uiy=%d", uix, uiy);
	Camera::LeftSpace = Camera::RightSpace = uix * 0.9f;
	Camera::TopSpace = Camera::BottomSpace = uiy * 0.9f;

	initgraph(uix, uiy);
	setcaption(caption.c_str());
	setbkcolor(BLACK);
	setrendermode(RENDER_MANUAL);
	setbkmode(TRANSPARENT);

	hwnd = getHWnd();

	if (xfull)
	{
		if (HaveFlag(initMode, INITMODE_FULL_SCREEN))
			MoveWindow(hwnd, 0, -caption_h, uix, uiy, FALSE);
		else
			ShowWindow(hwnd, SW_SHOWMAXIMIZED);
	}
	else {
		MoveWindow(hwnd, scr_w / 2 - uix / 2, (scr_h - taskbar_h) / 2 - uiy / 2, uix, uiy, FALSE);
	}
	//InstallHook();
}
#define DRAW_CD 0
#define FRAME_MIN_TIME 1
void MV_Load();
void MV_Control()
{
	if (K(VK_ESCAPE))
	{
		DebugLog("按 Esc 退出！");
		MV_Unload();
		closegraph();
		exit(0);
		while (K(VK_ESCAPE));
	}
	else if (K(VK_F3))
	{
		show_debug = !show_debug;
		while (K(VK_F3));
	}
}

void MV_Before_Base()
{
	DebugLog("MV_Before: 播放前的展示");
	g_stage = mvs_before;
	drawStart = clock();
	g_playing = true;

#ifdef USE_CONTROLLER
	ConnectToController();
#endif
}
void MV_Draw_Before();
void MV_Before()
{
	XCPT_L
	clock_t lastDraw = clock();
	MV_Before_Base();
	while (is_run() && g_playing)
	{
		if (clock() - lastDraw >= DRAW_CD)
		{
			MV_Draw_Before();
			lastDraw = clock();
		}
		if (DELTA_MS >= g_beforeTime)
			break;
		MV_Control();
	}
	XCPT_R
}
void MV_Update()
{
	XCPT_L
	if (!regCtrl.waiting)
		scriptRunner.UpdateCommands();
	else
		regCtrl.UpdateShouldWait();
	elePfmr.CheckElementLives();
	camera.CheckEffectsLives();
#ifdef USE_CONTROLLER
	ControlInteraction();
#endif
	XCPT_R
}
void MV_Draw()
{
	XCPT_L
	if(!camera.HaveEffect(EFF_DRAG))
		cleardevice();
	if (imgBuffer == nullptr)
		imgBuffer = newimage(IMGBUFFER_WIDTH, IMGBUFFER_HEIGHT);
	else
		cleardevice(imgBuffer);
	//settarget(imgBuffer);
	setbkmode(TRANSPARENT, imgBuffer);
	setbkcolor(BLACK, imgBuffer);
	bgMgr.UpdateActualBackColor();

	elePfmr.Perform(imgBuffer);
	//settarget((PIMAGE)nullptr);
	camera.DrawScene(imgBuffer);
	//delimage(imgBuffer);
	//elePfmr.Perform(nullptr);
	if (show_debug)
		DrawDebug();
	delay_fps(60);
	XCPT_R
}
void MV_Start_Actions();

void MV_Start()
{
	XCPT_L
	g_stage = mvs_start;
	clock_t lastDraw = clock();
	g_playing = true;
	drawStart = clock();

	MV_Start_Actions();
	camera.Clear();
	AddCommands(MV_SCRIPT_PATH);

	cplayer.Play();

	while (is_run() && g_playing)
	{
		//clock_t frame_start = clock();
		if (clock() - lastDraw >= DRAW_CD)
		{
			MV_Draw();
			lastDraw = clock();
		}
		if (DELTA_MS >= g_bodyTime)
			break;
		MV_Control();
		MV_Update();
		/*clock_t frame_end = clock();
		if (frame_end - frame_start < FRAME_MIN_TIME)
			delay(FRAME_MIN_TIME - (frame_end - frame_start));*/
	}
	XCPT_R
}

void MV_After_Base()
{
	DebugLog("MV_After: 播放后的展示");
	g_stage = mvs_after;
	drawStart = clock();
	cplayer.Pause();
}
void MV_Draw_After();
void MV_After()
{
	XCPT_L
	clock_t lastDraw = clock();
	MV_After_Base();
	while (is_run() && g_playing)
	{
		if (clock() - lastDraw >= DRAW_CD)
		{
			MV_Draw_After();
			lastDraw = clock();
		}
		if (DELTA_MS >= g_afterTime)
			break;
		MV_Control();
	}
	XCPT_R
}

void MV_SetStageTimes(clock_t beforeTime, clock_t bodyTime, clock_t afterTime)
{
	g_beforeTime = beforeTime;
	g_bodyTime = bodyTime;
	g_afterTime = afterTime;
	DebugLogFormat("MV_SetStageTimes: 设置各阶段时长  前 %ld ms, 中 %ld ms, 后 %ld ms", g_beforeTime, g_bodyTime, g_afterTime);
}

template <typename T2>
void MV_Load_Base(const string& musicPath, initializer_list<string> fontFamilies, T2&& imageNames)
{
	XCPT_L
	DebugLog("MV_Load: 载入中...");
	g_stage = mvs_load;
	cplayer.SetWindowHwnd(hwnd);

	BOOL bRet = cplayer.Open(musicPath.c_str());
	if (!bRet)
	{
		ErrorLogTip("MV所需音频缺失：" + musicPath, "MV_Load");
		closegraph();
		exit(0);
	}
	fontMgr.AddFontFamilies(fontFamilies);
	imgMgr.AddImages(imageNames);
	XCPT_R
}
void MV_Unload_Base()
{
	XCPT_L
	DebugLog("MV_Unload: 开始卸载数据...");
	//UninstallHook();
	g_stage = mvs_unload;
	g_playing = false;
	cplayer.Stop();
	cplayer.Close();
	fontMgr.Dispose();
	if (imgBuffer)
		delimage(imgBuffer);
	camera.DeletePureColorImages();
	XCPT_R
}