#pragma once
////////////////////////////////////////////////
//         MV C++ Performer ר��ͷ�ļ�         //
//          by Wormwaker, ��ֹ����             //
////////////////////////////////////////////////

#define FONT_DIR "../Common/"

using FontNameID = USHORT;
extern const char* fontnames[] =
{   "������������ (������) W8" ,		//0
    "������౦����" ,					//1
    "�����",						//2
	"XQjuzhentiZJSY",				//3
	"Aa���׺�",						//4
	"Aaδ���� 75",					//5
	"�����ֳ�Ӳ��-�� ����",			//6
};
#define FONTNAME_XINQINGNIAN fontnames[0]
#define FONTNAME_YANZHENQING fontnames[1]
#define FONTNAME_DEYIHEI     fontnames[2]
#define FONTNAME_XIQUEJUZHEN fontnames[3]
#define FONTNAME_JIJIAHEI    fontnames[4]
#define FONTNAME_WEILAIHEI   fontnames[5]
#define FONTNAME_ZTZCYHSDS   fontnames[6]

FontNameID GetFontNameID(const string& fontname)
{
	if (fontname == "0" || Convert<string, int>(fontname) != 0)
		return Convert<string, int>(fontname);
	for (size_t i = 0; i < _countof(fontnames); ++i)
		if (sequ(fontnames[i], fontname))
			return (FontNameID)i;
	ErrorLogTip("�޷��ҵ���Ϊ\"" + fontname + "\"�����壡", "GetFontNameID");
	return 0;
}

class FontManager {		//���������
private:
	bool enabled = false;
	vector<string> m_registered_families;

public:

	FontManager() { enabled = true;	 }
	~FontManager() { Dispose(); }

	static string MakeFontPath(const string& name)
	{
		return FONT_DIR + name + ".ttf";
	}
	bool AddFontFamily(const string& name)
	{
		string path = MakeFontPath(name);
		int cnt = AddFontResourceA(path.c_str());
		if (cnt <= 0)
		{
			ErrorLogTip("�������� " + name + " ʧ�ܣ�·��Ϊ��" + path, "FontManager::AddFontFamily");
			return false;
		}
		DebugLogFormat("�ɹ��������壺%s", name.c_str());
		m_registered_families.push_back(name);
		return true;
	}

	void AddFontFamilies(initializer_list<string> families)
	{
		if (families.size() == 0)	return;
		size_t suc_cnt{ 0 };
		for (const auto& name : families)
			suc_cnt += AddFontFamily(name)?1:0;
		DebugLogFormat("FontManager::AddFontFamilies:  ������������ %zu / %zu", suc_cnt, families.size());
	}
	void Dispose()
	{
		if (!enabled)
			return;
		enabled = false;
		size_t suc_cnt{ 0 };
		for (const auto& name : m_registered_families)
		{
			suc_cnt += RemoveFontResourceA(MakeFontPath(name).c_str())?1:0;
		}
		DebugLogFormat("FontManager::Dispose:  ж���������� %zu / %zu", suc_cnt, m_registered_families.size());
	}
}fontMgr;