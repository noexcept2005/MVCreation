/***************************************************
 *                   main.cpp                      *
 *            ��ΰ���ҡ�������ɳ۵ĸ���               *
 *              Author: Wormwaker                  *
 *            StartDate: 2024/4/4                *
 *              All Rights Reserved.               *
 *              Do Not Distribute!                 *
 *                δ�������ֹ����                   *
 ***************************************************/
 //ע�⣺ VS ��Ŀ

//#define USE_CONTROLLER
#define PRODUCT_NAME "��ΰ���ҡ����"
#define MV_SCRIPT_PATH  ("../" PRODUCT_NAME "/Assets/Main.mvs")
#include "../Common/mv_core.h"
#define MOST_RELAXED_ANUS_PATH (ASSETS_DIR+string{"��ΰ���ҡ�������ɳ۵ĸ���.mp3"})
#define MOST_RELAXED_ANUS_DURATION (120000)

void MV_Load()
{
	MV_Load_Base(MOST_RELAXED_ANUS_PATH,
		{ FONTNAME_DEYIHEI, FONTNAME_YANZHENQING, FONTNAME_XIQUEJUZHEN,
		  FONTNAME_JIJIAHEI, FONTNAME_WEILAIHEI, FONTNAME_ZTZCYHSDS },
		move(GetDirFilesR(COMMON_DIR, "*.png2")));
}
void MV_Unload()
{
	MV_Unload_Base();
}
void MV_Draw_Before()
{
	cleardevice();

	setfont(60, 0, FONTNAME_XIQUEJUZHEN);
	setcolor(FadeInOutColor(WHITE, DELTA_MS, g_beforeTime, 800, 800));
	midprintf(uiy / 2 - 80, "MV C++ Performer Framework");
	setcolor(FadeInOutColor(RainbowColor(), DELTA_MS, g_beforeTime, 800, 800));
	midprintf(uiy / 2 + 50, "by Wormwaker");

	delay_fps(60);
}
void MV_Draw_After()
{
	cleardevice();

	setfont(60, 0, FONTNAME_XIQUEJUZHEN);
	setcolor(FadeInOutColor(LIGHTCYAN, DELTA_MS, g_afterTime, 800, 800));
	centerprintf("Produced by Wormwaker");

	delay_fps(60);
}

void MV_Start_Actions()
{
	
}
///////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
#ifdef USE_CONTROLLER
	if (argc == 1)
	{
		WinExec(("\"" + MV_CONTROLLER_PATH + "\" "s + argv[0]).c_str(), SW_SHOWNORMAL);
		//return 0;
	}
#endif
	MV_Init("��ΰ���ҡ�������ɳ۵ĸ��� MV - by Wormwaker");

	MV_Load();
	MV_SetStageTimes(3000, MOST_RELAXED_ANUS_DURATION, 3000);

	MV_Before();
	MV_Start();
	MV_After();

	MV_Unload();

	DebugLog("�˳�...");
	closegraph();
	return 0;
}