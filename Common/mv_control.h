#pragma once
////////////////////////////////////////////////
//         MV C++ Performer 专属头文件         //
//          by Wormwaker, 禁止盗用             //
////////////////////////////////////////////////

//#define WM_MUSIC_PAUSE (WM_USER + 1)
//#define WM_MUSIC_RESUME (WM_USER + 2)
//#define WM_MUSIC_STOP (WM_USER + 3)

clock_t lastPause{ 0L };
void __stdcall OnMusicPause()
{
    //sndMgr.QuickPlay("Explosion.wav");
    cplayer.Pause();
    lastPause = clock();
}
void __stdcall OnMusicResume()
{
    //sndMgr.QuickPlay("Water1.wav");
    cplayer.Continue();

    //时间补偿
    clock_t delta = clock() - lastPause;
    lastWvBeg += delta;
    drawStart += delta;
    regCtrl.region_start += delta;
    elePfmr.AddDeltaTime(delta);
}
void __stdcall OnMusicStop()
{
   // sndMgr.QuickPlay("你干嘛~.mp3");
	cplayer.Stop();
}

HWND hwnd_controller{ nullptr };

string controller_caption{};
void SetControllerDefaultTitle()
{
    controller_caption = "";
    SetWindowTextA(hwnd_controller, "MV Controller");
}
void ControlInteraction()   //only main thread
{
    static int mus_status = 1; //1-playing  0-stopped  2-paused
    if (sequ(controller_caption, "Pause"))
    {
        if (mus_status == 1)
            OnMusicPause(), mus_status = 2;
        SetControllerDefaultTitle();
    }
    else if (sequ(controller_caption, "Resume"))
    {
        if (mus_status == 2)
            OnMusicResume(), mus_status = 1;
        SetControllerDefaultTitle();
    }
    else if (sequ(controller_caption, "Stop"))
    {
        if (mus_status != 0)
            OnMusicStop(), mus_status = 0;
        SetControllerDefaultTitle();
    }
    else if (sequ(controller_caption, "Exit"))
    {
        SetControllerDefaultTitle();
        MV_Unload();
        closegraph();
        exit(0);
    }
}

DWORD ThrControlInteraction(LPVOID args)
{
    if (!hwnd_controller || hwnd_controller == INVALID_HANDLE_VALUE)
    {
        DebugLog("ThrControlInteraction: 窗口句柄无效，无法开启控制器通信系统");
        return 0L;
    }
    DebugLog("ThrControlInteraction: 开启控制器通信系统");
    while (is_run() && g_playing)
    {
        char buffer[128]{ 0 };
        GetWindowTextA(hwnd_controller, buffer, 128);

        controller_caption = string(buffer);
    }
    DebugLog("ThrControlInteraction: 关闭控制器通信系统");
    return 1L;
}

void ConnectToController()
{
    setfont(40, 0, "Consolas");
    setcolor(LIGHTGRAY);
    midprintf(200, "Capturing Controller Window...");
    delay_fps(60);

    while (!hwnd_controller || hwnd_controller == INVALID_HANDLE_VALUE)
    {
        hwnd_controller = FindWindowA("Easy Graphics Engine", "MV Controller");
        delay(250);
    }
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThrControlInteraction, NULL, 0, NULL);
}

//// 全局变量用于保存原始的消息处理函数指针
//WNDPROC g_OldWindowProc = NULL;
//
//// 自定义消息处理函数
//LRESULT CALLBACK CustomWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
//    switch (uMsg) {
//   
//    case WM_MUSIC_PAUSE:
//       OnMusicPause();
//       return 0;
//    case WM_MUSIC_RESUME:
//       OnMusicResume();
//       return 0;
//    case WM_MUSIC_STOP:
//       OnMusicStop();
//       return 0;
//    default:
//        MessageBeep(MB_ICONERROR);
//                                            //DebugLog("1");
//        // 调用原始的消息处理函数处理消息                                   
//                                            //return g_OldWindowProc(NULL, uMsg, wParam, lParam);
//                                            //DebugLog("2");
//        return CallNextHookEx(NULL, uMsg, wParam, lParam);
//    }
//    return 0;
//}
//
//// 安装消息挂钩
//void InstallHook() {
//    // 获取EGE图形库提供的消息处理函数指针
//    g_OldWindowProc = (WNDPROC)getProcfunc();
//
//    DWORD tid{ 0L };
//    GetWindowThreadProcessId(hwnd, &tid);
//
//    // 安装消息挂钩，拦截消息并调用自定义的消息处理函数
//    SetWindowsHookExA(WH_CALLWNDPROC, (HOOKPROC)CustomWindowProc, NULL, tid);
//}
//
//// 卸载消息挂钩
//void UninstallHook() {
//    // 卸载消息挂钩
//    UnhookWindowsHookEx((HHOOK)CustomWindowProc);
//}
