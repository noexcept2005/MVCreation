#pragma once
////////////////////////////////////////////////
//         MV C++ Performer ר��ͷ�ļ�         //
//          by Wormwaker, ��ֹ����             //
////////////////////////////////////////////////

template <typename _T1, typename _T2>
_T2 CJZAPI Convert(const _T1& src)	//��������ת��
{
	stringstream ss;
	ss << src;
	_T2 res;
	ss >> res;
	return res;
}
template <typename _T>
string CJZAPI str(const _T& value)	//ת�ַ���
{
	stringstream ss;
	ss << value;
	string res;
	ss >> res;
	return res;
}
template <typename _T>	//ģ�嶨�ƣ���Щ�˽�ģ������
string CJZAPI str(const vector<_T>& _list) {
	//�б�ת�ַ���
	string res = "[";
	for (short i = 0; i < _list.size(); ++i) {
		res += str(_list.at(i));
		if (i != _list.size() - 1)
			res += ",";
	}
	res += "]";
	return res;
}
template <typename _T>
inline LPCSTR CJZAPI cstr(const _T& value)
{
	return str(value).c_str();
}
inline bool CJZAPI strequ(char *str, const char *obj)
{	//�Ƚ��Ƿ�һ�� 
	return (strcmp((const char *)str, obj) == 0 ? true : false);
}

inline bool CJZAPI sequ(const string& s1, const string& s2)
{
	return _stricmp(s1.c_str(), s2.c_str())==0;
}
char * CJZAPI strrpc(char *str, const char *oldstr, const char *newstr) {
	//�ַ����滻
	char bstr[65535];//ת��������
	memset(bstr, 0, sizeof(bstr));
	for (size_t i = 0; i < strlen(str); i++) {
		if (!strncmp(str + i, oldstr, strlen(oldstr))) {
			//����Ŀ���ַ���
			strcat(bstr, newstr);
			i += strlen(oldstr) - 1;
		}
		else {
			strncat(bstr, str + i, 1);//����һ�ֽڽ�������
		}
	}
	strcpy(str, bstr);
	return str;
}
//from https://blog.csdn.net/qq_41673920/article/details/81390972
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
string CJZAPI sprintf2(const char* szFormat, ...)
{
	va_list _list;
	va_start(_list, szFormat);
	char szBuffer[1024] = "\0";
	_vsnprintf(szBuffer, 1024, szFormat, _list);
	va_end(_list);
	return string{ szBuffer };
}
// wstring=>string
string WString2String(const wstring &ws)
{
	string strLocale = setlocale(LC_ALL, "");
	const wchar_t *wchSrc = ws.c_str();
	size_t nDestSize = wcstombs(NULL, wchSrc, 0) + 1;
	char *chDest = new char[nDestSize];
	memset(chDest, 0, nDestSize);
	wcstombs(chDest, wchSrc, nDestSize);
	string strResult = chDest;
	delete[] chDest;
	setlocale(LC_ALL, strLocale.c_str());
	return strResult;
}

// string => wstring
wstring String2WString(const string &s)
{
	string strLocale = setlocale(LC_ALL, "");
	const char *chSrc = s.c_str();
	size_t nDestSize = mbstowcs(NULL, chSrc, 0) + 1;
	wchar_t *wchDest = new wchar_t[nDestSize];
	wmemset(wchDest, 0, nDestSize);
	mbstowcs(wchDest, chSrc, nDestSize);
	wstring wstrResult = wchDest;
	delete[] wchDest;
	setlocale(LC_ALL, strLocale.c_str());
	return wstrResult;
}
//from https://blog.csdn.net/qq_30386941/article/details/126814596

vector<string> CJZAPI SplitToLines(string szParagraph, char lineEnding = '\n')
{	//��һ�λ��ֳ�ÿ�� 
	vector<string> ret{};
	int p1 = 0, p2;
	for (int i = 0; i < szParagraph.size(); i++)
	{
		if (szParagraph.at(i) == lineEnding
			|| i == szParagraph.size() - 1)	//��©�����һ������ 
		{
			p2 = i;
			string szNew = szParagraph.substr(p1, p2 - p1 + (i == szParagraph.size() - 1 ? 1 : 0));
			ret.push_back(szNew);
			p1 = i + 1;
		}
	}
	return ret;
}

vector<string> CJZAPI CutLine(const string& line, char sep = ' ') {
	vector<string> ret{};
	if (line.empty()) return ret;
	int p1 = 0, p2 = 0;
	for (int i = 0; i < line.size(); i++) {
		if (line.at(i) == sep
			|| i == line.size() - 1) {
			p2 = i;
			string s = line.substr(p1, p2 - p1 + (i == line.size() - 1 ? 1 : 0));
			ret.push_back(s);
			p1 = i + 1;
		}
	}
	return ret;
}

//ֱ�ӿ����ӣ�
//���� GetQuotedString("test \"123\" sb \"My  Sound/Explosion.wav\"", 3, ' ')
//���� My  Sound/Explosion.wav
string GetQuotedString(const string& command, int begIndex, char sep = ' ') {
	size_t index = 0;
	size_t quoteStart = 0;
	size_t commandLength = command.length();

	// �ҵ�ָ���Ӵ�����ʼλ��
	for (size_t i = 0; i < commandLength; ++i) {
		if (command[i] == sep) {
			if (index == begIndex - 1) {
				quoteStart = i + 1;
				break;
			}
			++index;
		}
	}

	// ���ҵ���λ�ÿ�ʼ���ҵ�һ��˫����
	size_t quoteEnd = command.find('"', quoteStart + 1);

	// ����ҵ��˵�һ��˫���ţ��������Ĳ���
	if (quoteEnd != string::npos) {
		string quotedSubstring = command.substr(quoteStart, quoteEnd - quoteStart + 1);

		// �ж����һ���ַ��Ƿ�Ϊ˫����
		if (quotedSubstring.back() == '"') {
			// ȥ��˫���Ų�����
			return quotedSubstring.substr(1, quotedSubstring.length() - 2);
		}
	}

	return "";
}