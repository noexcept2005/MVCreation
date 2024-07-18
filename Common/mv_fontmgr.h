#pragma once
////////////////////////////////////////////////
//         MV C++ Performer 专属头文件         //
//          by Wormwaker, 禁止盗用             //
////////////////////////////////////////////////

#define FONT_DIR "../Common/"

using FontNameID = USHORT;
extern const char* fontnames[] =
{   "文悦新青年体 (非商用) W8" ,		//0
    "颜真卿多宝塔碑" ,					//1
    "得意黑",						//2
	"XQjuzhentiZJSY",				//3
	"Aa机甲黑",						//4
	"Aa未来黑 75",					//5
	"字跳字唱硬核-闪 电闪",			//6
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
	ErrorLogTip("无法找到名为\"" + fontname + "\"的字体！", "GetFontNameID");
	return 0;
}

class FontManager {		//字体管理器
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
			ErrorLogTip("加载字体 " + name + " 失败！路径为：" + path, "FontManager::AddFontFamily");
			return false;
		}
		DebugLogFormat("成功加载字体：%s", name.c_str());
		m_registered_families.push_back(name);
		return true;
	}

	void AddFontFamilies(initializer_list<string> families)
	{
		if (families.size() == 0)	return;
		size_t suc_cnt{ 0 };
		for (const auto& name : families)
			suc_cnt += AddFontFamily(name)?1:0;
		DebugLogFormat("FontManager::AddFontFamilies:  加载字体结果： %zu / %zu", suc_cnt, families.size());
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
		DebugLogFormat("FontManager::Dispose:  卸载字体结果： %zu / %zu", suc_cnt, m_registered_families.size());
	}
}fontMgr;