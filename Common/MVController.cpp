#include <Windows.h>
#include <graphics.h>
#include <io.h>
#include <tlhelp32.h>
#include <sstream>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
#define CJZAPI __stdcall
#define fequ(f1, f2) (abs((f1) - (f2)) < 0.001)

#define WM_MUSIC_PAUSE (WM_USER + 1)
#define WM_MUSIC_RESUME (WM_USER + 2)
#define WM_MUSIC_STOP (WM_USER + 3)

void SetMessage(const string& s);

template <typename T>
string CJZAPI str(const T& value)
{
	stringstream ss;
	ss << value;
	string s;
	ss >> s;
	return s;
}

string CJZAPI strtail(const string& s, int cnt = 1) {
	//012 len=3
	//abc   s.substr(2,1)
	if (cnt > s.size())
		return s;
	return s.substr(s.size() - cnt, cnt);
}
string CJZAPI strhead(const string& s, int cnt = 1) {
	if (cnt > s.size())
		return s;
	return s.substr(0, cnt);
}
string CJZAPI strxtail(const string& s, int cnt = 1) {
	if (cnt > s.size())
		return "";
	return s.substr(0, s.size() - cnt);
}
string CJZAPI strxhead(const string& s, int cnt = 1) {
	if (cnt > s.size())
		return "";
	return s.substr(cnt, s.size() - cnt);
}
string CJZAPI unquote(const string& s)
{
	if (s.length() < 2 || s[0] != s[s.length() - 1])
		return s;
	return strxhead(strxtail(s));
}
inline string CJZAPI quote(const string& s)
{
	return "\"" + s + "\"";
}
string CJZAPI strip(const string& s)
{
	string res = s;
	while (!res.empty() && (res.at(0) == '\r' || res.at(0) == '\n' || res.at(0) == '\0'))
		res = res.substr(1, res.size() - 1);
	while (!res.empty() && (res.at(res.size() - 1) == '\r' || res.at(res.size() - 1) == '\n' || res.at(0) == '\0'))
		res = res.substr(0, res.size() - 1);
	return res;
}
bool CJZAPI ExistFile(const char* path)
{
	return !_access(path, S_OK);
}
inline int CJZAPI GetScreenHeight(void) //获取屏幕高度
{
	return GetSystemMetrics(SM_CYSCREEN);
}
inline int CJZAPI GetScreenWidth(void) //获取屏幕宽度
{
	return GetSystemMetrics(SM_CXSCREEN);
}
RECT CJZAPI GetSystemWorkAreaRect(void) //获取工作区矩形 
{
	RECT rt;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rt, 0);    // 获得工作区大小
	return rt;
}
LONG CJZAPI GetTaskbarHeight(void) 		//获取任务栏高度 
{
	INT cyScreen = GetScreenHeight();
	RECT rt = GetSystemWorkAreaRect();
	return (cyScreen - (rt.bottom - rt.top));
}
HANDLE CJZAPI GetProcessHandle(DWORD pid)	//通过进程ID获取进程句柄
{
	return OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
}HANDLE CJZAPI GetProcessHandle(LPCSTR lpName)	//通过进程名获取进程句柄
{	//******警告！区分大小写！！！！******// 
	//*****警告！必须加扩展名！！！！*****// 
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnapshot)
	{
		return NULL;
	}
	PROCESSENTRY32 pe = { sizeof(pe) };
	BOOL fOk;
	for (fOk = Process32First(hSnapshot, &pe); fOk; fOk = Process32Next(hSnapshot, &pe))
	{
		//cout << "\n进程：" << pe.szExeFile;
		if (!_stricmp(pe.szExeFile, lpName))
		{
			CloseHandle(hSnapshot);
			return GetProcessHandle(pe.th32ProcessID);
		}
	}
	return NULL;
}
//from  https://blog.csdn.net/fzuim/article/details/60954959
bool CJZAPI HaveProcess(DWORD pid)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnapshot)
		return false;
	PROCESSENTRY32 pe = { sizeof(pe) };
	BOOL fOk;
	for (fOk = Process32First(hSnapshot, &pe); fOk; fOk = Process32Next(hSnapshot, &pe))
		if (pe.th32ProcessID == pid)
		{
			CloseHandle(hSnapshot);
			return true;
		}
	CloseHandle(hSnapshot);
	return false;
}
BOOL CJZAPI HaveProcess(LPCSTR lpName)
{	//******警告！区分大小写！！！！******// 
	//*****警告！必须加扩展名！！！！*****// 
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnapshot)
	{
		return NULL;
	}
	PROCESSENTRY32 pe = { sizeof(pe) };
	BOOL fOk;
	for (fOk = Process32First(hSnapshot, &pe); fOk; fOk = Process32Next(hSnapshot, &pe))
		if (!_stricmp(pe.szExeFile, lpName))	//相同名称 忽略大小写
		{
			CloseHandle(hSnapshot);
			return true;
		}
	CloseHandle(hSnapshot);
	return false;
}
DWORD GetWindowPID(HWND hwnd)
{
	DWORD dwPid = 0;
	GetWindowThreadProcessId(hwnd, &dwPid);
	return dwPid;
}
string GetProcessName(DWORD pid)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnapshot)
	{
		return string("");
	}
	PROCESSENTRY32 pe = { sizeof(pe) };
	BOOL fOk;
	for (fOk = Process32First(hSnapshot, &pe); fOk; fOk = Process32Next(hSnapshot, &pe))
	{
		if (pe.th32ProcessID == pid)
		{
			CloseHandle(hSnapshot);
			//			  cout<<"text="<<pe.szExeFile;	
			//					pname=pe.szExeFile;	
			//			  return (LPSTR)pe.szExeFile;	
			return (string)pe.szExeFile;
		}
	}
	return string("");
}
bool FreezeProcess(HANDLE hProc)	//冻结进程
{
	int pid = GetProcessId(hProc);
	THREADENTRY32 th32;
	th32.dwSize = sizeof(th32);
	
	HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hThreadSnap == INVALID_HANDLE_VALUE)
	{
		SetMessage("CreateToolhelp32Snapshot Call Failure");
		return false;
	}
	
	bool b;
	b = Thread32First(hThreadSnap, &th32);
	while (b)
	{
		if (th32.th32OwnerProcessID == pid)
		{
			HANDLE oth = OpenThread(THREAD_ALL_ACCESS, FALSE, th32.th32ThreadID);
			if (!(SuspendThread(oth)))
			{
//				SetColor(11, 0);
//				printf("\n已冻结线程ID: %d", th32.th32ThreadID);
//				printf("\n已冻结进程ID: %d", th32.th32OwnerProcessID);
			}
			CloseHandle(oth);
			break;
		}
		Thread32Next(hThreadSnap, &th32);
	}
	CloseHandle(hThreadSnap);
	SetMessage("Freeze Success");
	return true;
}
bool UnfreezeProcess(HANDLE hProc)	//解冻进程
{
	int pid = GetProcessId(hProc);
	THREADENTRY32 th32;
	th32.dwSize = sizeof(th32);
	
	HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hThreadSnap == INVALID_HANDLE_VALUE)
	{
		SetMessage("CreateToolhelp32Snapshot Call Failure");
		return false;
	}
	
	bool b;
	b = Thread32First(hThreadSnap, &th32);
	while (b)
	{
		if (th32.th32OwnerProcessID == pid)
		{
			HANDLE oth = OpenThread(THREAD_ALL_ACCESS, FALSE, th32.th32ThreadID);
			if (!(ResumeThread(oth)))
			{
//				printf("\n已解冻线程ID: %d", th32.th32ThreadID);
//				printf("\n已解冻进程ID: %d", th32.th32OwnerProcessID);
			}
			CloseHandle(oth);
			break;
		}
		Thread32Next(hThreadSnap, &th32);
	}
	CloseHandle(hThreadSnap);
	SetMessage("Unfreeze Success");
	return true;
}
bool FreezeProcessByPid(int pid)
{
	HANDLE hProc = GetProcessHandle(pid);
	if (hProc == nullptr || hProc == INVALID_HANDLE_VALUE)
	{
		SetMessage("Cannot Get the Process Handle");
		return false;
	}
	bool ret = FreezeProcess(hProc);
	CloseHandle(hProc);
	return ret;
}
bool UnfreezeProcessByPid(int pid)
{
	HANDLE hProc = GetProcessHandle(pid);
	if (hProc == nullptr || hProc == INVALID_HANDLE_VALUE)
	{
		SetMessage("Cannot Get the Process Handle");
		return false;
	}
	bool ret = UnfreezeProcess(hProc);
	CloseHandle(hProc);
	return ret;
}

template <typename _T>
inline _T CJZAPI ClampA(_T& val, _T min = 0, _T max = 2147483647) {	//限定范围
	if (val < min) val = min;
	else if (val > max) val = max;
	return val;
}
template <typename _T>
inline _T CJZAPI Clamp(_T val, _T min = 0, _T max = 2147483647) {	//限定范围
	if (val < min) val = min;
	else if (val > max) val = max;
	return val;
}
color_t CJZAPI StepColor0(color_t startColor, color_t endColor, double rate) {
	if (fequ(rate, 0.0))	return startColor;
	if (fequ(rate, 1.0))	return endColor;
	//颜色的渐变
	int r = (EGEGET_R(endColor) - EGEGET_R(startColor));
	int g = (EGEGET_G(endColor) - EGEGET_G(startColor));
	int b = (EGEGET_B(endColor) - EGEGET_B(startColor));
	
	int nSteps = max(abs(r), max(abs(g), abs(b)));
	if (nSteps < 1) nSteps = 1;
	
	// Calculate the step size for each color
	float rStep = r / (float)nSteps;
	float gStep = g / (float)nSteps;
	float bStep = b / (float)nSteps;
	
	// Reset the colors to the starting position
	float fr = EGEGET_R(startColor);
	float fg = EGEGET_G(startColor);
	float fb = EGEGET_B(startColor);
	
	color_t color = startColor;
	for (int i = 0; i < int(nSteps * rate); i++) {
		fr += rStep;
		fg += gStep;
		fb += bStep;
		color = RGB((int)(fr + 0.5), (int)(fg + 0.5), (int)(fb + 0.5));
		//color 即为重建颜色
	}
	return color;
}//from https://bbs.csdn.net/topics/240006897 , owner: zgl7903

color_t CJZAPI StepColor(color_t startColor, color_t endColor, double rate) {
	// 获取起始颜色分量
	int startR = EGEGET_R(startColor);
	int startG = EGEGET_G(startColor);
	int startB = EGEGET_B(startColor);
	
	// 获取结束颜色分量
	int endR = EGEGET_R(endColor);
	int endG = EGEGET_G(endColor);
	int endB = EGEGET_B(endColor);
	
	// 计算过渡颜色分量
	int newR = static_cast<int>(startR + (endR - startR) * rate);
	int newG = static_cast<int>(startG + (endG - startG) * rate);
	int newB = static_cast<int>(startB + (endB - startB) * rate);
	
	// 构造过渡颜色
	color_t resultColor = EGERGB(newR, newG, newB);
	return resultColor;
}

inline COLORREF CJZAPI WinColor(color_t clr) {
	//EGERGB -> RGB
	return RGB(EGEGET_R(clr), EGEGET_G(clr), EGEGET_B(clr));
}
inline color_t CJZAPI EgeColor(COLORREF clr) {
	//RGB -> EGERGB
	return EGERGB(GetRValue(clr), GetGValue(clr), GetBValue(clr));
}
inline color_t CJZAPI InvertedColor(color_t clr) {
	return EGERGB(255 - EGEGET_R(clr), 255 - EGEGET_G(clr), 255 - EGEGET_B(clr));
}

#define WVC_AMP 12
#define WVC_OMEGA 13.0
#define WVC_PHASE0 0
clock_t lastWvBeg = 0;
inline COLORREF WaveColor0(COLORREF originClr, float phi = 0.0f) {	//originClr将成为最大值
	//闪烁的颜色 赋予游戏文字灵性
	short val = WVC_AMP * sin(WVC_OMEGA*((clock() - lastWvBeg) / 1000.0) + WVC_PHASE0 + phi) - WVC_AMP * 2;
	short r = GetRValue(originClr) + val, g = GetGValue(originClr) + val, b = GetBValue(originClr) + val;
	ClampA<short>(r, 2, 255);
	ClampA<short>(g, 2, 255);
	ClampA<short>(b, 2, 255);
	return RGB(r, g, b);
}
inline color_t WaveColor(color_t originClr, float phi = 0.0f)
{
	return EgeColor(WaveColor0(WinColor(originClr), phi));
}
// 辅助函数：RGB到HSV颜色转换
void RGBtoHSV(COLORREF rgb, double& h, double& s, double& v) {
	double r = GetRValue(rgb) / 255.0;
	double g = GetGValue(rgb) / 255.0;
	double b = GetBValue(rgb) / 255.0;
	
	double minVal = min(min(r, g), b);
	double maxVal = max(max(r, g), b);
	double delta = maxVal - minVal;
	
	// 计算色相
	if (delta > 0) {
		if (maxVal == r)
			h = 60.0 * fmod((g - b) / delta, 6.0);
		else if (maxVal == g)
			h = 60.0 * ((b - r) / delta + 2.0);
		else if (maxVal == b)
			h = 60.0 * ((r - g) / delta + 4.0);
	}
	else {
		h = 0.0;
	}
	
	// 计算饱和度和亮度
	s = (maxVal > 0) ? (delta / maxVal) : 0.0;
	v = maxVal;
}

// 辅助函数：HSV到RGB颜色转换
COLORREF HSVtoRGB(double h, double s, double v) {
	int hi = static_cast<int>(floor(h / 60.0)) % 6;
	double f = h / 60.0 - floor(h / 60.0);
	double p = v * (1.0 - s);
	double q = v * (1.0 - f * s);
	double t = v * (1.0 - (1.0 - f) * s);
	
	switch (hi) {
		case 0: return RGB(static_cast<int>(v * 255), static_cast<int>(t * 255), static_cast<int>(p * 255));
		case 1: return RGB(static_cast<int>(q * 255), static_cast<int>(v * 255), static_cast<int>(p * 255));
		case 2: return RGB(static_cast<int>(p * 255), static_cast<int>(v * 255), static_cast<int>(t * 255));
		case 3: return RGB(static_cast<int>(p * 255), static_cast<int>(q * 255), static_cast<int>(v * 255));
		case 4: return RGB(static_cast<int>(t * 255), static_cast<int>(p * 255), static_cast<int>(v * 255));
		case 5: return RGB(static_cast<int>(v * 255), static_cast<int>(p * 255), static_cast<int>(q * 255));
		default: return RGB(0, 0, 0);  // Shouldn't reach here
	}
}

// 主函数：返回随时间变化的彩虹色
color_t RainbowColor() {
	// 假设时间按秒计算，这里使用系统时间或其他适当的时间源
	double timeInSeconds = GetTickCount() / 1000.0;
	
	// 色相按时间变化
	double hue = fmod(timeInSeconds * 30.0, 360.0);  // 假设每秒变化30度
	
	// 饱和度和亮度保持不变
	double saturation = 1.0;
	double value = 1.0;
	
	// 将HSV颜色转换为RGB并返回
	return EgeColor(HSVtoRGB(hue, saturation, value));
}

string exepath{};
HWND hwnd_target{nullptr};
HWND hwnd_self{nullptr};
DWORD pid = 0L;
string procName{};
bool paused {false};

constexpr int uix = 200;
constexpr int uiy = 200;
constexpr int alpha = 200;
int scr_w, scr_h, taskbar_h;
string msg {};
clock_t lastMsg = 0L;
bool shown {true};

#define KEY_DOWN(vk)	(GetAsyncKeyState(vk)&0x8000?1:0)
#define K(vk)			(KEY_DOWN(vk) && GetForegroundWindow()==hwnd_self)

#define MSG_SHOWN_TIME 5000
void Draw(clock_t start)
{
	cleardevice();
	
	if(!shown)
	{
		delay_fps(60);
		return;
	}
	setfont(25, 0, "Consolas");
	setcolor(paused?ORANGE:RED);
	
	char buffer[256]{0};
	GetWindowTextA(hwnd_self, buffer, 256);
	
	string caption {buffer};
	xyprintf(0, 0, caption.c_str());
	
	setfont(10, 0, "Lucida Console");
	setcolor(StepColor(RainbowColor(), EGERGB(30, 30, 30), 0.85));
	rectprintf(3, 88, uix - 6, uiy, exepath.c_str());
	
	if(!msg.empty() && clock() - lastMsg < MSG_SHOWN_TIME)
	{
		setfont(20, 0, "Consolas");
		setcolor(LIGHTRED);
		xyprintf(3, uiy - 50, msg.c_str());
	}
	
	setfont(18, 0, "Consolas");
	setcolor(CYAN);
	xyprintf(3, 28, "Timer: %.3f", (clock() - start) / (float)CLOCKS_PER_SEC);
	setcolor(PURPLE);
	xyprintf(3, 46, "PID: %ld", pid);
	xyprintf(3, 64, "Proc: %s", procName.c_str());
	
	setcolor(WaveColor(LIGHTGRAY));
	rectprintf(3, 80, uix-6, uiy, "Esc: Quit\n"
								  "Delete: Terminate\n"
								  "Space: Pause\n"
								  "\n\n@Wormwaker");
	
	delay_fps(60);
}
void SetMessage(const string& s)
{
	msg = s;
	lastMsg = clock();
}
#define DRAW_CD 100
#define FIND_CD 200
void Wait()
{
	clock_t lastFind {clock()};
	clock_t lastDraw{clock()};
	while(1)
	{
		if(clock() - lastDraw >= DRAW_CD)
		{
			cleardevice();
			setfont(30, 0, "Consolas");
			setcolor(LIGHTGREEN);
			rectprintf(10, 10, uix-20, uiy, "Waiting For Target Window...");
			delay_fps(60);
			lastDraw = clock();
		}
		
		if(clock() - lastFind >= FIND_CD)
		{
			POINT pt{10, 10};
			HWND hwnd = WindowFromPoint(pt);
			if (GetWindowPID(hwnd) == pid)
			{
				hwnd_target = hwnd;
				break;
			}
			lastFind = clock();
		}
	}
}
void Start()
{	
	clock_t start{clock()};
	clock_t lastDraw { clock() }; 
	
	while (is_run())
	{
		if (!HaveProcess(pid))
		{
			break;
		}
		if (KEY_DOWN(VK_ESCAPE))
		{
			while (KEY_DOWN(VK_ESCAPE));
			if (paused)
			{
				UnfreezeProcessByPid(pid);
				delay(500);
			}
			SendMessageA(hwnd_target, WM_CHAR, VK_ESCAPE, 0);
			SetMessage("Close Window");
			while (HaveProcess(pid))
				delay(300);
			break;
		}
		else if (KEY_DOWN(VK_DELETE))
		{
			while (KEY_DOWN(VK_DELETE));
			if (paused)
			{
				UnfreezeProcessByPid(pid);
				delay(500);
			}
			HANDLE hProc = GetProcessHandle(pid);
			if (!hProc || hProc == INVALID_HANDLE_VALUE)
			{
				SetMessage("Cannot open the process\n ERR=" + str(GetLastError()));
			}else{
				BOOL bRet = TerminateProcess(hProc, 1);
				if (!bRet)
				{
					SetMessage("Cannot terminate the process\n ERR=" + str(GetLastError()));
				}else{
					CloseHandle(hProc);
					SetMessage("Termination Success");
					delay(1000);
					break;
				}
				CloseHandle(hProc);
			}
		}else if (KEY_DOWN(VK_SPACE) && !KEY_DOWN(VK_LWIN) && !KEY_DOWN(VK_RWIN))
		{
			while (KEY_DOWN(VK_SPACE));
			if (!paused)
			{
				setcaption("Pause");
				delay(100);
//					SendMessage(hwnd_target, WM_MUSIC_PAUSE, 0, 0);
				paused = FreezeProcessByPid(pid);
				if (!paused)
					SendMessage(hwnd_target, WM_MUSIC_RESUME, 0, 0);
//				paused = true;
			}
			else
			{
				setcaption("Resume");
//					SendMessage(hwnd_target, WM_MUSIC_RESUME, 0, 0);
				paused = !UnfreezeProcessByPid(pid);
				if (paused)
					SendMessage(hwnd_target, WM_MUSIC_PAUSE, 0, 0);
//				paused = false;
			}
				
		}else if(KEY_DOWN('H'))
		{
			while(KEY_DOWN('H'));
			shown = !shown;
		}
		
		if (clock() - lastDraw >= DRAW_CD)
		{
			Draw(start);
			lastDraw = clock();
		}
	}
}

int main(int argc, char *argv[])
{
	if(argc == 1)
	{
		MessageBoxA(nullptr, "Usage:  MVController <path> ", "MV Controller", MB_OK);
		return 2;
	}
	exepath = strip(strxhead(GetCommandLineA(), strlen(argv[0]) + 3));
	if(!exepath.empty() && exepath[0] == '\"' && exepath[exepath.length()-1] == '\"')
		exepath = unquote(exepath);
	cout << "Exepath: \"" << exepath << "\"\n";
	
	if (!ExistFile(exepath.c_str()))
	{
		MessageBoxA(nullptr, ("Invalid EXE path:\n" + exepath + "\n"s + str(exepath[0]) + "\n"s + str(exepath[exepath.size()-1])).c_str(), "MV Controller", MB_ICONERROR);
		return 1;
	}
	for(int i = exepath.size() - 1; i >= 0; --i)
	{
		if(exepath.at(i) == '\\')
		{
			procName = strtail(exepath, exepath.size() - i - 1);
			break;
		}
	}
	
	if(procName.empty())
		procName = exepath;
	cout << "Process Name: " << procName << endl;
	
	string cmdline	{exepath + " --run"};
	//MessageBoxA(nullptr, cmdline.c_str(), "MV Controller", MB_OK);
	if (!HaveProcess(procName.c_str()))
		WinExec(cmdline.c_str(), SW_SHOWMAXIMIZED);
	
	scr_w = GetScreenWidth();
	scr_h = GetScreenHeight();
	taskbar_h = GetTaskbarHeight();
	initgraph(uix, uiy);
	setcaption("MV Controller");
	setbkcolor(BLACK);
	setrendermode(RENDER_MANUAL);
	setbkmode(TRANSPARENT);
	
	hwnd_self = getHWnd();
	SetWindowLong(hwnd_self, GWL_STYLE, GetWindowLong(hwnd_self, GWL_STYLE) & (~(WS_CAPTION | WS_SYSMENU | WS_SIZEBOX)));
	SetWindowLong(hwnd_self, GWL_EXSTYLE, GetWindowLong(hwnd_self, GWL_EXSTYLE) & (~(WS_EX_WINDOWEDGE | WS_EX_DLGMODALFRAME)) | WS_EX_LAYERED | WS_EX_TOOLWINDOW);
	SetWindowPos(hwnd_self, HWND_TOPMOST, scr_w - uix, scr_h - taskbar_h - uiy, uix, uiy, 
				SWP_NOSIZE | SWP_FRAMECHANGED | SWP_SHOWWINDOW | SWP_DRAWFRAME);
	SetLayeredWindowAttributes(hwnd_self, 0x000000, alpha, LWA_COLORKEY);
	
	setfont(20, 0, "Consolas");
	setcolor(RainbowColor());
	rectprintf(10, 10, uix - 20, uiy, "Process Name: %s", procName.c_str());
	delay_fps(60);
	
	while(!HaveProcess(procName.c_str()))
	{
		if(KEY_DOWN(VK_ESCAPE))
		{
			closegraph();
			return 1;
		}
		delay(10);
	}
	HANDLE hProc = GetProcessHandle(procName.c_str());
	if (!hProc || hProc == INVALID_HANDLE_VALUE)
	{
		MessageBoxA(nullptr, ("Process Handle Cannot Got!\n ERR="+str(GetLastError())).c_str(), "MV Controller", MB_ICONERROR);
		closegraph();
		return 1;
	}
	pid = GetProcessId(hProc);
	CloseHandle(hProc);
	
	Wait();
	Start();
	
	closegraph();
	return 0;
}
