#pragma once
////////////////////////////////////////////////
//         MV C++ Performer ר��ͷ�ļ�         //
//          by Wormwaker, ��ֹ����             //
////////////////////////////////////////////////

#define KEY_DOWN(vk)	(GetAsyncKeyState(vk)&0x8000?1:0)
#define K(vk)			(KEY_DOWN(vk) && GetForegroundWindow()==hwnd)

///////////////////////////////////////////////////////////
//                 Window ����ϵ��                        //
///////////////////////////////////////////////////////////

inline int CJZAPI GetScreenHeight(void) //��ȡ��Ļ�߶�
{
	return GetSystemMetrics(SM_CYSCREEN);
}
inline int CJZAPI GetScreenWidth(void) //��ȡ��Ļ���
{
	return GetSystemMetrics(SM_CXSCREEN);
}
RECT CJZAPI GetSystemWorkAreaRect(void) //��ȡ���������� 
{
	RECT rt;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rt, 0);    // ��ù�������С
	return rt;
}
LONG CJZAPI GetTaskbarHeight(void) 		//��ȡ�������߶� 
{
	INT cyScreen = GetScreenHeight();
	RECT rt = GetSystemWorkAreaRect();
	return (cyScreen - (rt.bottom - rt.top));
}
inline LONG CJZAPI GetTitleHeight(HWND hwnd) {
	//RECT rect, rectClient;
	//GetWindowRect(hwnd, &rect);//-�õ����ھ��δ�С
	//-rect.bottom �����ڵĸ߶ȣ�rect.right �� ���ڵĿ��
	//GetClientRect(hwnd, &rectClient);//-�õ��ͻ������δ�С
	//-rectClient.bottom ���ͻ����ĸ߶ȣ�rectClient.right �� �ͻ����Ŀ��
	return GetSystemMetrics(SM_CYCAPTION)
		//+(rect.right-rectClient.right)/2	//��Ҫ�������������ѹ��������ϵģ��� 
		;
	//�Ӵ��ڶ������ͻ�����ʼ֮�������߶ȣ��Ǳ������߶�+�ϱ߿�߶�.
}//from http://www.cjjjs.com/article/2015121905342361

float GetScreenScaleFactor()
{
	// ��ȡ���ڵ�ǰ��ʾ�ļ�����
	// ʹ������ľ��.
	HWND hWnd = GetForegroundWindow();
	HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

	// ��ȡ�������߼������߶�
	MONITORINFOEX miex;
	miex.cbSize = sizeof(miex);
	GetMonitorInfo(hMonitor, &miex);
	int cxLogical = (miex.rcMonitor.right - miex.rcMonitor.left);
	//int cyLogical = (miex.rcMonitor.bottom - miex.rcMonitor.top);

	// ��ȡ��������������߶�
	DEVMODE dm;
	dm.dmSize = sizeof(dm);
	dm.dmDriverExtra = 0;
	EnumDisplaySettings(miex.szDevice, ENUM_CURRENT_SETTINGS, &dm);
	int cxPhysical = dm.dmPelsWidth;
	//int cyPhysical = dm.dmPelsHeight;
	// ���ű�������  ʵ����ʹ���κ�һ������
	double horzScale = ((double)cxPhysical / (double)cxLogical);
	//double vertScale = ((double)cyPhysical / (double)cyLogical);
	return horzScale;
}

///////////////////////////////////////////////////////////
//                   File �ļ�ϵ��                        //
///////////////////////////////////////////////////////////

inline bool CJZAPI ExistFile(const string& path)
{
	return !_access(path.c_str(), S_OK);
}
vector<string> CJZAPI ReadFileLines(const string& filePath) {
	//��ȡ�ļ�ÿһ��
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
{	//�Ƿ����ļ��� 
	int res;
	struct _stat64i32 buf;
	res = _stat64i32(lpPath.c_str(), &buf);
	return (buf.st_mode & _S_IFDIR);
}
BOOL CJZAPI IsFile(const string& lpPath)
{	//�Ƿ����ļ� 
	int res;
	struct _stat64i32 buf;
	res = _stat64i32(lpPath.c_str(), &buf);
	return (buf.st_mode & _S_IFREG);
}
string CJZAPI GetFileDirectory(string path)
{	//���ص�������б��
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
		SetLastError(3L);	//����Ҫreturn��
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
	string dirp = dir + filter;	//���ǲ���ʽ��

	if ((lfDir = _findfirst(dirp.c_str(), &fileDir)) == -1l)
		return vector<string>();
	do {	//����Ŀ¼
		if (!strequ(fileDir.name, ".") && !strequ(fileDir.name, ".."))	//�ų�������������
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
//                Notification ֪ͨϵ��                   //
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