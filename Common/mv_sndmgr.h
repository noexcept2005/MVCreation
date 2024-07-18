#pragma once
////////////////////////////////////////////////
//         MV C++ Performer ר��ͷ�ļ�         //
//          by Wormwaker, ��ֹ����             //
////////////////////////////////////////////////

void SoundThreadProc(const string& fullpath)
{
	CPlayer cp;
	if (!cp.Open(fullpath.c_str()))
	{
		ErrorLogTip("����Ƶ�ļ� \"" + fullpath + "\" ʧ�ܣ�", "SoundThreadProc");
		return;
	}
	cp.Play();
	DWORD dwLen = cp.GetLength();
	clock_t start = clock();
	//DebugLog("SoundThreadProc: ������Ƶ��");
	//while (cp.GetPos() <= dwLen)
	while ((clock() - start) / (double)CLOCKS_PER_SEC * 1000 < dwLen)
		this_thread::sleep_for(100ms);
	//DebugLog("SoundThreadProc: �ر���Ƶ��");
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
		ErrorLogTip("�޷���ȡ��Ƶȫ·��, �ļ���Ϊ \"" + filename + "\"", "SoundManager::GetSoundFullPath");
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