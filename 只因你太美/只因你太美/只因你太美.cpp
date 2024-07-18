/***************************************************
 *                 只因你太美.cpp                   *
 *                用于实现鸽鸽的MV                   *
 *              Author: Wormwaker                  *
 *            StartDate: 2023/12/17                *
 *              All Rights Reserved.               *
 *              Do Not Distribute!                 *
 *                未经允许禁止传播                   *
 ***************************************************/
//注意： VS 项目

#define PRODUCT_NAME "只因你太美"
#define MV_SCRIPT_PATH  ("../" PRODUCT_NAME "/Assets/Main.mvs")
#include "../../Common/mv_core.h"
//#define BECAUSE_YOU_ARE_TOO_BEAUTIFUL_PATH (ASSETS_DIR+string{"只因你太美（后半部分）.mp3"})
#define BECAUSE_YOU_ARE_TOO_BEAUTIFUL_PATH (ASSETS_DIR+string{"只因你太美 - SWIN-S.mp3"})
#define BECAUSE_YOU_ARE_TOO_BEAUTIFUL_DURATION (225000)

void MV_Load()
{
	MV_Load_Base(BECAUSE_YOU_ARE_TOO_BEAUTIFUL_PATH, 
		{ FONTNAME_DEYIHEI, FONTNAME_YANZHENQING, FONTNAME_XIQUEJUZHEN,
		  FONTNAME_JIJIAHEI, FONTNAME_WEILAIHEI, FONTNAME_ZTZCYHSDS},
		move(GetDirFilesR(COMMON_DIR, "*.png")));
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
	//elePfmr.AddText(100, 100, 6000, AIN_ENLARGE, "鸡你胎没", WHITE, 80, string{ FONTNAME_ZTZCYHSDS },
	//	"{ex:1000.0f,ey:400.0f,e_fs:240s,in_time:1000L,out_time:1000L,change_func:\"ease_in_expo\",motion_delay:940L,e_color:#&0}"s);
}
///////////////////////////////////////////////////////////////
int main()
{
	MV_Init("只因你太美 C++ MV - by Wormwaker");

	MV_Load();
	MV_SetStageTimes(3000, BECAUSE_YOU_ARE_TOO_BEAUTIFUL_DURATION, 3000);

	MV_Before();
	MV_Start();
	MV_After();

	MV_Unload();

	DebugLog("退出...");
	closegraph();
	return 0;
}