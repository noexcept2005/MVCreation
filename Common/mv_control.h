#pragma once
////////////////////////////////////////////////
//         MV C++ Performer ר��ͷ�ļ�         //
//          by Wormwaker, ��ֹ����             //
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

    //ʱ�䲹��
    clock_t delta = clock() - lastPause;
    lastWvBeg += delta;
    drawStart += delta;
    regCtrl.region_start += delta;
    elePfmr.AddDeltaTime(delta);
}
void __stdcall OnMusicStop()
{
   // sndMgr.QuickPlay("�����~.mp3");
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
        DebugLog("ThrControlInteraction: ���ھ����Ч���޷�����������ͨ��ϵͳ");
        return 0L;
    }
    DebugLog("ThrControlInteraction: ����������ͨ��ϵͳ");
    while (is_run() && g_playing)
    {
        char buffer[128]{ 0 };
        GetWindowTextA(hwnd_controller, buffer, 128);

        controller_caption = string(buffer);
    }
    DebugLog("ThrControlInteraction: �رտ�����ͨ��ϵͳ");
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

//// ȫ�ֱ������ڱ���ԭʼ����Ϣ������ָ��
//WNDPROC g_OldWindowProc = NULL;
//
//// �Զ�����Ϣ������
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
//        // ����ԭʼ����Ϣ������������Ϣ                                   
//                                            //return g_OldWindowProc(NULL, uMsg, wParam, lParam);
//                                            //DebugLog("2");
//        return CallNextHookEx(NULL, uMsg, wParam, lParam);
//    }
//    return 0;
//}
//
//// ��װ��Ϣ�ҹ�
//void InstallHook() {
//    // ��ȡEGEͼ�ο��ṩ����Ϣ������ָ��
//    g_OldWindowProc = (WNDPROC)getProcfunc();
//
//    DWORD tid{ 0L };
//    GetWindowThreadProcessId(hwnd, &tid);
//
//    // ��װ��Ϣ�ҹ���������Ϣ�������Զ������Ϣ������
//    SetWindowsHookExA(WH_CALLWNDPROC, (HOOKPROC)CustomWindowProc, NULL, tid);
//}
//
//// ж����Ϣ�ҹ�
//void UninstallHook() {
//    // ж����Ϣ�ҹ�
//    UnhookWindowsHookEx((HHOOK)CustomWindowProc);
//}
