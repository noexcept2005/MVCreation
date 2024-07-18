#pragma once
////////////////////////////////////////////////
//         MV C++ Performer 专属头文件         //
//          by Wormwaker, 禁止盗用             //
////////////////////////////////////////////////

void SoundThreadProc(const string& fullpath)
{
	CPlayer cp;
	if (!cp.Open(fullpath.c_str()))
	{
		ErrorLogTip("打开音频文件 \"" + fullpath + "\" 失败！", "SoundThreadProc");
		return;
	}
	cp.Play();
	DWORD dwLen = cp.GetLength();
	clock_t start = clock();
	//DebugLog("SoundThreadProc: 播放音频！");
	//while (cp.GetPos() <= dwLen)
	while ((clock() - start) / (double)CLOCKS_PER_SEC * 1000 < dwLen)
		this_thread::sleep_for(100ms);
	//DebugLog("SoundThreadProc: 关闭音频！");
	cp.Stop();
	cp.Close();
}

class SoundManager {
public:

	SoundManager()
	{

	}
	~SoundManager()
	{

	}
	static string GetSoundFullPath(const string& filename)
	{
		string path;
		if (ExistFile(path = ASSETS_DIR + filename))
			return path;
		if (ExistFile(path = COMMON_DIR + filename))
			return path;
		if (ExistFile(filename))
			return filename;
		ErrorLogTip("无法获取音频全路径, 文件名为 \"" + filename + "\"", "SoundManager::GetSoundFullPath");
		return "";
	}
	void QuickPlay(const string& filename)
	{					//e.g.   Shock.wav
		string fullpath = GetSoundFullPath(filename);
		if (fullpath.empty())
			return;
		thread thr(SoundThreadProc, fullpath);
		thr.detach();
	}

private:
	
}sndMgr;