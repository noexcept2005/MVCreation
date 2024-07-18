#pragma once
////////////////////////////////////////////////
//         MV C++ Performer 专属头文件         //
//          by Wormwaker, 禁止盗用             //
////////////////////////////////////////////////

#define KEY_DOWN(vk)	(GetAsyncKeyState(vk)&0x8000?1:0)
#define K(vk)			(KEY_DOWN(vk) && GetForegroundWindow()==hwnd)

///////////////////////////////////////////////////////////
//                 Window 窗口系列                        //
///////////////////////////////////////////////////////////

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
inline LONG CJZAPI GetTitleHeight(HWND hwnd) {
	//RECT rect, rectClient;
	//GetWindowRect(hwnd, &rect);//-得到窗口矩形大小
	//-rect.bottom ：窗口的高度，rect.right ： 窗口的宽度
	//GetClientRect(hwnd, &rectClient);//-得到客户区矩形大小
	//-rectClient.bottom ：客户区的高度，rectClient.right ： 客户区的宽度
	return GetSystemMetrics(SM_CYCAPTION)
		//+(rect.right-rectClient.right)/2	//不要用这个←，它会把滚动条算上的！！ 
		;
	//从窗口顶部到客户区开始之间的区域高度，是标题栏高度+上边框高度.
}//from http://www.cjjjs.com/article/2015121905342361

float GetScreenScaleFactor()
{
	// 获取窗口当前显示的监视器
	// 使用桌面的句柄.
	HWND hWnd = GetForegroundWindow();
	HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

	// 获取监视器逻辑宽度与高度
	MONITORINFOEX miex;
	miex.cbSize = sizeof(miex);
	GetMonitorInfo(hMonitor, &miex);
	int cxLogical = (miex.rcMonitor.right - miex.rcMonitor.left);
	//int cyLogical = (miex.rcMonitor.bottom - miex.rcMonitor.top);

	// 获取监视器物理宽度与高度
	DEVMODE dm;
	dm.dmSize = sizeof(dm);
	dm.dmDriverExtra = 0;
	EnumDisplaySettings(miex.szDevice, ENUM_CURRENT_SETTINGS, &dm);
	int cxPhysical = dm.dmPelsWidth;
	//int cyPhysical = dm.dmPelsHeight;
	// 缩放比例计算  实际上使用任何一个即可
	double horzScale = ((double)cxPhysical / (double)cxLogical);
	//double vertScale = ((double)cyPhysical / (double)cyLogical);
	return horzScale;
}

///////////////////////////////////////////////////////////
//                   File 文件系列                        //
///////////////////////////////////////////////////////////

inline bool CJZAPI ExistFile(const string& path)
{
	return !_access(path.c_str(), S_OK);
}
vector<string> CJZAPI ReadFileLines(const string& filePath) {
	//读取文件每一行
	vector<string> ret{};
	const int lineMaxCharCnt = 32767;
	fstream fin(filePath, ios::in);
	if (fin.fail())
		return ret;
	while (1) {
		CHAR s[lineMaxCharCnt];

		if (fin.eof())
			break;

		fin.getline(s, lineMaxCharCnt);
		ret.push_back(string(s));
	}
	fin.close();
	return ret;
}

void CJZAPI DebugLog(const char* s)
{
	FILE* fp = fopen(log_path.c_str(), "a");
	if (!fp)
		return;
	fprintf(fp, "%s\n", s);
	fclose(fp);
}
void CJZAPI DebugLog(const string& s)
{
	FILE* fp = fopen(log_path.c_str(), "a");
	if (!fp)
		return;
	fprintf(fp, "%s\n", s.c_str());
	fclose(fp);
}
template <typename _T>
/*inline */void CJZAPI DebugLogA(const _T& value)
{
	DebugLog(cstr(value));
}
int CJZAPI DebugLogFormat(const char* szFormat, ...)
{
	va_list va;
	va_start(va, szFormat);
	FILE *fp = fopen(log_path.c_str(), "a");
	if (!fp)
	{
		va_end(va);
		return 0;
	}
	char buffer[1024] = "\0";
	int res = _vsnprintf(buffer, 1024, szFormat, va);
	fprintf(fp, "%s\n", buffer);
	va_end(va);
	fclose(fp);
	return res;
}

BOOL CJZAPI IsDir(const string& lpPath)
{	//是否是文件夹 
	int res;
	struct _stat64i32 buf;
	res = _stat64i32(lpPath.c_str(), &buf);
	return (buf.st_mode & _S_IFDIR);
}
BOOL CJZAPI IsFile(const string& lpPath)
{	//是否是文件 
	int res;
	struct _stat64i32 buf;
	res = _stat64i32(lpPath.c_str(), &buf);
	return (buf.st_mode & _S_IFREG);
}
string CJZAPI GetFileDirectory(string path)
{	//返回的最后会有斜线
	if (path.empty())
		return string{};
	if (IsDir(path))
	{
		if (strtail(path) != "/")
			path += "/";
		return path;
	}
	string ret = "";
	bool suc = false;
	for (int i = path.size() - 1; i >= 0; i--)
	{
		if (path.at(i) == '\\' || path.at(i) == '/')
		{
			ret = path.substr(0, i + 1);
			suc = true;
			break;
		}
	}
	if (!suc)
		SetLastError(3L);	//还是要return的
	if (strtail(ret) != "/")
		ret += "/";
	return ret;
}
vector<string> CJZAPI GetDirFiles(const string& dir, const string& filter = "*.*")
{
	if (dir.empty() || (filter != "" && !ExistFile(dir)))
	{
		return vector<string>();
	}
	_finddata_t fileDir;
	intptr_t lfDir;
	vector<string> files{};
	string dirp = dir + filter;	//它是查找式的

	if ((lfDir = _findfirst(dirp.c_str(), &fileDir)) == -1l)
		return vector<string>();
	do {	//遍历目录
		if (!strequ(fileDir.name, ".") && !strequ(fileDir.name, ".."))	//排除这两个狗东西
			files.push_back(string(fileDir.name));
	} while (_findnext(lfDir, &fileDir) == 0L);
	_findclose(lfDir);
	return files;
}
void GetDirFilesR_Proc(vector<string>* result, const string& odir /*backslashed*/, const string& childDir, const string& filter)
{
	vector<string> matchedFiles = GetDirFiles(odir + childDir, filter);
	for (auto& f : matchedFiles)
		if (IsFile(odir + childDir + f))
		{
			result->push_back(childDir + f);
		}
	matchedFiles.clear();
	vector<string> all = GetDirFiles(odir + childDir, "*");
	for (auto& ele : all)
		if (IsDir(odir + childDir + ele))
		{
			GetDirFilesR_Proc(result, odir, childDir + ele + "\\", filter);
		}

}
vector<string> CJZAPI GetDirFilesR(const string& dir /*backslashed*/, const string& filter = "*.*")
{
	vector<string> result;
	GetDirFilesR_Proc(&result, dir, "", filter);
	return result;
}

///////////////////////////////////////////////////////////
//                Notification 通知系列                   //
///////////////////////////////////////////////////////////

inline int CJZAPI ErrorTip(const string& text, const string& moduleName)
{
	return MessageBoxA(hwnd, text.c_str(), ("MV " + moduleName + " ERROR").c_str(), MB_ICONERROR | MB_OK);
}
inline int CJZAPI WarnTip(const string& text, const string& moduleName)
{
	return MessageBoxA(hwnd, text.c_str(), ("MV " + moduleName + " WARNING").c_str(), MB_ICONWARNING | MB_OK);
}
inline int CJZAPI InfoTip(const string& text, const string& moduleName)
{
	return MessageBoxA(hwnd, text.c_str(), ("MV " + moduleName + " INFO").c_str(), MB_ICONINFORMATION | MB_OK);
}

/*inline*/ int CJZAPI ErrorLogTip(const string& text, const string& moduleName)
{
	DebugLogFormat("[ERROR in %s] %s", moduleName.c_str(), text.c_str());
	return MessageBoxA(hwnd, text.c_str(), ("MV " + moduleName + " ERROR").c_str(), MB_ICONERROR | MB_OK);
}
inline int CJZAPI WarnLogTip(const string& text, const string& moduleName)
{
	DebugLogFormat("[WARNING in %s] %s", moduleName.c_str(), text.c_str());
	return MessageBoxA(hwnd, text.c_str(), ("MV " + moduleName + " WARNING").c_str(), MB_ICONWARNING | MB_OK);
}
inline int CJZAPI InfoLogTip(const string& text, const string& moduleName)
{
	DebugLogFormat("[INFO in %s] %s", moduleName.c_str(), text.c_str());
	return MessageBoxA(hwnd, text.c_str(), ("MV " + moduleName + " INFO").c_str(), MB_ICONINFORMATION | MB_OK);
}