#pragma once
////////////////////////////////////////////////
//         MV C++ Performer ר��ͷ�ļ�         //
//          by Wormwaker, ��ֹ����             //
////////////////////////////////////////////////

#ifdef USING_TRACK
#define TrackLog DebugLog
#else
#define TrackLog(...)
#endif

color_t ParseColor(string s) {
	//������ɫ
	if (s.empty()) {
		ErrorLogTip("������ɫ�ַ����������󣺿մ�", "ParseColor");
		return WHITE;
	}
	if (s[0] == '#')
		s = strxhead(s);
	if (s[0] == '&') {	//16ɫ
		UINT uClr = Convert<string, UINT>(strxhead(s, 1));
		return Color16ToRGB(uClr);
	}
	vector<string> rgb = CutLine(s, ';');
	if (rgb.size() < 3) {
		ErrorLogTip("������ɫ�ַ�����������RGB���뺬3����", "ParseColor");
		return WHITE;
	}
	UINT r = Convert<string, UINT>(rgb.at(0));
	UINT g = Convert<string, UINT>(rgb.at(1));
	UINT b = Convert<string, UINT>(rgb.at(2));
	return EGERGB(r, g, b);
}

string UncoverValue(const string& value, const string& type, const char* callTag=nullptr) {
	if (type == "" || type == "unknown") {
		ErrorLogTip("����������Ч:\n" + type +" callTag="+(callTag!=nullptr?str(callTag):string("")), "UncoverValue");
		return value;
	}
	if (type == "string")
		return strxtail(strxhead(value));
	/*else if(type == "long long" || type == "double" || type == "unsigned long")
		return strxtail(value,2);*/
	else if (type == "color")	//#��ͷ e.g.  #0;0;0
		return strxhead(value, 1);
	else
		return strxtail(value, 1);
}
string GetValueType(const string& s)
{
	if (strtail(s) == "\"" && strhead(s) == "\""
		|| strtail(s) == "\'" && strhead(s) == "\'")
		return "string";
	if (strtail(s) == "]" && strhead(s) == "[")
		return "list";
	if (strtail(s) == "}" && strhead(s) == "{")
		return "json";
	if (strhead(s) == "#")
		return "color";
	if (strhead(s) != "[" && strhead(s) != "{" && strhead(s) != "\"" && strhead(s) != "\'") {
		string tail = strtail(s);
		//				DebugLog("tail="+tail);
				/*if(sequ(tail,"b"))
					return "byte";*/
		if (sequ(tail, "s"))
			return "short";
		if (sequ(tail, "f"))
			return "float";
		if (sequ(tail, "l"))
			return "long";
	}
	return "unknown";	//δ֪
}

class JSON;
JSON ParseJSON(const string& src, const char* tag = nullptr);
class JSON	//��������֯������
{
protected:
	vector<pair<string, string>> _data;
public:
	JSON() {
	}
	JSON(const string& _src)
	{
		*this = ParseJSON(_src, "JSON::JSON");
	}
	JSON(string&& _src)
	{
		*this = ParseJSON(_src, "JSON::JSON");
	}

	void Clear() {
		_data.clear();
	}
	bool Empty()	const {
		return _data.empty();
	}
	bool HaveKey(const char* key) const {
		XCPT_L
			if (_data.empty())	return false;
		for (short i = 0; i < _data.size(); ++i)
			if (_data.at(i).first == key)
				return true;
		return false;
		XCPT_R
	}
	void ToLog(void)	const {
		DebugLogA("JSON ToLog: " + ToString());
	}
	inline size_t ItemCount(void) const
	{
		return _data.size();
	}
	pair<string, string>& GetNthItem(size_t n)
	{
		if (n >= _data.size())
			throw out_of_range{ "JSON::GetNthItem: �±�Խ�磡" };
		return _data.at(n);
	}
	const pair<string, string>& GetNthItem(size_t n) const
	{
		if (n >= _data.size())
			throw out_of_range{ "JSON::GetNthItem: �±�Խ�磡" };
		return _data.at(n);
	}
	string GetValueRaw(const char* key) const {
		//			TrackLog("...");
		for (short i = 0; i < _data.size(); ++i)
			if (_data.at(i).first == key)
				return _data.at(i).second;
		return "";
	}
	bool SetValueRaw(const char* key, const char* newValueRaw) {
		XCPT_L
			//			TrackLog("...");
			for (short i = 0; i < _data.size(); ++i)
				if (_data.at(i).first == key) {
					_data.at(i).second = newValueRaw;
					return true;
				}
		XCPT_R
			return false;
	}
	bool SetShort(const char* key, short value) {
		if (!HaveKey(key) || GetValueType(key, "JSON::SetShort") != "short")
			return false;
		TrackLog("���ö�����");
		SetValueRaw(key, (str(value) + "s").c_str());
		return true;
	}
	short GetShort(const char * key)	const
	{	//������������򱨴�
		if (!HaveKey(key) || GetValueType(key, "JSON::GetShort") != "short")
		{
			ErrorLogTip("�Ҳ���������" +  str(key), "JSON::GetShort");
			return 0;
		}
		short res = 0;
		GetSimpleValue<short>(key, &res);
		return res;
	}
	bool SetLong(const char* key, long value) {
		if (!HaveKey(key) || GetValueType(key, "JSON::SetLong") != "long")
			return false;
		TrackLog("���ó�����");
		SetValueRaw(key, (str(value) + "L").c_str());
		return true;
	}
	long GetLong(const char * key)	const
	{	//������������򱨴�
		if (!HaveKey(key) || GetValueType(key, "JSON::GetLong") != "long")
		{
			ErrorLogTip("�Ҳ���������" + str(key), "JSON::GetLong");
			return 0;
		}
		long res = 0;
		GetSimpleValue<long>(key, &res);
		return res;
	}
	bool SetFloat(const char* key, float value) {
		if (!HaveKey(key) || GetValueType(key, "JSON::SetFloat") != "float")
			return false;
		TrackLog("���ø�����");
		SetValueRaw(key, (str(value) + "f").c_str());
		return true;
	}
	float GetFloat(const char * key)	const
	{	//������������򱨴�
		if (!HaveKey(key) || GetValueType(key, "JSON::GetFloat") != "float")
		{
			ErrorLogTip("�Ҳ���������" + str(key), "JSON::GetFloat");
			return 0;
		}
		float res = 0;
		GetSimpleValue<float>(key, &res);
		return res;
	}
	bool SetString(const char* key, const string& value) {
		if (!HaveKey(key))
		{
			AddItem(key, "\"" + str(value) + "\"");
			return true;
		}
		TrackLog("�����ַ���");
		SetValueRaw(key, ("\"" + str(value) + "\"").c_str());
		return true;
	}
	string GetString(const char * key)	const
	{	//������������򱨴�
		if (!HaveKey(key) || GetValueType(key, "JSON::GetString") != "string")
		{
			ErrorLogTip("�Ҳ����ַ���" + str(key), "JSON::GetString");
			return 0;
		}
		string res;
		GetSimpleValue<string>(key, &res);
		return res;
	}
	bool SetColor(const char* key, color_t value) {
		if (!HaveKey(key))
		{
			AddItem(key, "#" + str(EGEGET_R(value)) + ";" + str(EGEGET_G(value)) + ";" + str(EGEGET_B(value)));
			return true;
		}
		TrackLog("������ɫֵ");
		SetValueRaw(key, ("#" + str(EGEGET_R(value)) + ";" + str(EGEGET_G(value)) + ";" + str(EGEGET_B(value))).c_str());
		return true;
	}
	color_t GetColor(const char * key)	const
	{	//������������򱨴�
		if (!HaveKey(key) || GetValueType(key, "JSON::GetColor") != "color")
		{
			ErrorLogTip("�Ҳ�����ɫֵ" + str(key), "JSON::GetColor");
			return 0;
		}
		color_t res;
		GetComplexValue(key, &res);
		return res;
	}
	bool SetList(const char* key, const vector<string>& _list) {
		if (!HaveKey(key) || GetValueType(key, "JSON::SetList") != "list")
			return false;
		TrackLog("�����б�");
		SetValueRaw(key, str(_list).c_str());
		return true;
	}
	string GetValueType(const char* key, const char* tag = nullptr) const {
		string s = GetValueRaw(key);
		//			DebugLog("GetValueType tag="+str(tag)+" keyraw="+s);
		if (s.empty())	return "";	//not found
		return ::GetValueType(s);
	}
	template <typename _T>
	bool GetSimpleValue(const char* key, _T* result)	const;

	bool GetComplexValue(const char* key, void* result)	const;

	void AddItem(const string& key, const string& value) {
		XCPT_L
			//			DebugLog("JSON::Additem key="+key+" value="+value );
		_data.push_back(make_pair(key, value));
		XCPT_R
	}
	bool RemoveItem(const string& key)
	{
		auto iter = begin(_data);
		for (short j = 0; j < _data.size(); ++j, ++iter)
			if (_data.at(j).first == key)
			{
				_data.erase(iter);
				return true;
			}
		return false;
	}
	string ToString(void)	const {
		string ret = "{";
		for (short i = 0; i < _data.size(); ++i) {
			ret += _data.at(i).first;
			ret += ":";
			ret += _data.at(i).second;
			if (i != _data.size() - 1)
				ret += ",";
		}
		ret += "}";
		return ret;
	}
};

#define PJERR(msg) ErrorLogTip("��Ч��JSON��\n"+src+"\nԭ��"+str(msg),"ParseJSON"+(tag?" tag="+str(tag):string("")))
JSON ParseJSON(const string& src, const char* tag /*= nullptr*/) 
{
	XCPT_L

	//	DebugLog("ParseJSON len="+str(src.size())+" src="+src);
	if (src.empty() || strhead(src) != "{" || strtail(src) != "}") {
		PJERR("�޻����ṹ");
		return JSON();
	}
	if (src == "{}")
		return JSON();
	JSON res;
	stack<char> brackets;
	bool quote = false, midDone = false;
	short beg = 1, mid = -1;
	for (short i = 1; i < src.size(); ++i) {
		//0123456 len=7
		//{K:Val}
		//{A:123,B:"456",C:[1,2,3],D:{DEE:3}}
		char c = src.at(i);
		if (brackets.empty()) {
			if (c == ':') {
				if (midDone) {
					PJERR("�����ð��");
					return JSON();
				}
				mid = i;
				midDone = true;
			}
			else if (i == src.size() - 1 || c == ',') {
				string kv = src.substr(beg, i - beg);
				if (kv.empty()) {
					PJERR("���ֿ���");
					return JSON();
				}
				else if (!midDone) {
					PJERR("������ð��");
					return JSON();
				}
				string key = kv.substr(0, mid - beg);
				string value = kv.substr(mid - beg + 1, kv.size() + beg - mid - 1);
				res.AddItem(key.c_str(), value.c_str());
				//				DebugLog("����¼�ֵ key="+key+" value="+value);
				if (res.GetValueType(key.c_str(), ("ParseJSON tag=" + str(tag)).c_str()) == "unknown") {
					PJERR("��Ч��ֵ=" + value);
					return JSON();
				}
				beg = i + 1;
				mid = -1;
				midDone = false;
			}
			else if (c == '(' || c == ')') {
				PJERR("���������С����");
				return JSON();
			}
		}
		if (!quote && (c == '[' || c == '{')) {
			brackets.push(c);
		}
		else if (!quote && (c == ']' || c == '}')) {
			if (c == '}' && i == src.size() - 1)
				continue;	//end ignore
			if (brackets.empty() || brackets.top() != c - 2) {
				PJERR("���Ų�ƥ�䡣��������Ұ벿��");
				return JSON();
			}
			brackets.pop();
		}
		else if (c == '"' || c == '\'') {
			if (quote) {
				if (brackets.top() != c) {
					continue;
				}
				brackets.pop();
				quote = false;
			}
			else {
				brackets.push(c);
				quote = true;
			}
		}
	}
	if (!brackets.empty()) {
		PJERR("���Ų�ƥ�䡣���������벿��");
		return JSON();
	}
	return res;
	XCPT_R
}
#define PLERR(msg) ErrorLogTip("��Ч���б�\n"+src+"\nԭ��"+str(msg),"ParseList"+(tag?" tag="+str(tag):string("")))
vector<string> ParseList(const string& src, const char* tag = "") {
	XCPT_L
		if (src.empty() || strhead(src) != "[" || strtail(src) != "]") {
			PLERR("�޻����ṹ");
			return vector<string>();
		}
	if (src == "[]")
		return vector<string>();
	vector<string> res;
	stack<char> brackets;
	bool quote = false;
	short beg = 1;
	for (short i = 1; i < src.size(); ++i) {
		char c = src.at(i);
		if (brackets.empty()) {
			if (i == src.size() - 1 || c == ',') {
				string item = src.substr(beg, i - beg);
				if (item.empty()) {
					PLERR("���ֿ���");
					return vector<string>();
				}
				res.push_back(item);
				beg = i + 1;
			}
			else if (c == '(' || c == ')') {
				PLERR("���������С����");
				return vector<string>();
			}
		}
		if (!quote && (c == '[' || c == '{')) {
			brackets.push(c);
		}
		else if (!quote && (c == ']' || c == '}')) {
			if (c == ']' && i == src.size() - 1)
				continue;	//end ignore
			if (brackets.empty() || brackets.top() != c - 2) {
				PLERR("���Ų�ƥ�䡣��������Ұ벿��");
				return vector<string>();
			}
			brackets.pop();
		}
		else if (c == '"' || c == '\'') {
			if (quote) {
				if (brackets.top() != c) {
					continue;
				}
				brackets.pop();
				quote = false;
			}
			else {
				brackets.push(c);
				quote = true;
			}
		}
	}
	if (!brackets.empty()) {
		PLERR("���Ų�ƥ�䡣���������벿��");
		return vector<string>();
	}
	//	TrackLog("long list, size="+str(res.size()));
	return res;
	XCPT_R
}

template <typename _T>
bool JSON::GetSimpleValue(const char* key, _T* result)	const {
	//������ֱ��ʹ��ģ�庯��ת��
	string raw = GetValueRaw(key);
	if (raw.empty()) {
		ErrorLogTip("û���ҵ�ָ������" + str(key), "JSON::GetSimpleValue");
		return false;
	}
	string type = GetValueType(key, "JSON::GetSimpleValue");
	if (sequ(type, "json") || sequ(type, "list")) {
		ErrorLogTip("�������Ͳ����Ǽ����� ����" + type, "JSON::GetSimpleValue");
		return false;
	}
	//	TrackLog(".");
	raw = UncoverValue(raw, type, key);
	//		DebugLog("GetSimpleValue raw="+raw);
	*result = Convert<string, _T>(raw);
	return true;
}
bool JSON::GetComplexValue(const char* key, void* result)	const {
	//�������͵�������
	string raw = GetValueRaw(key);
	if (raw.empty()) {
		ErrorLogTip("û���ҵ�ָ������" + str(key), "JSON::GetComplexValue");
		return false;
	}
	string type = GetValueType(key, "JSON::GetComplexValue");
	//	TrackLog(".");
	if (sequ(type, "json")) {
		*((JSON*)result) = ParseJSON(raw, "JSON::GetComplexValue");
		return true;
	}
	if (sequ(type, "list")) {
		*((vector<string>*)result) = ParseList(raw);
		return true;
	}
	if (sequ(type, "color")) {
		*((color_t*)result) = ParseColor(strxhead(raw, 1));
		return true;
	}
	ErrorLogTip("�������Ͳ����Ǹ������� ����" + type, "JSON::GetComplexValue");
	//		result = nullptr;
	return false;
}

//by Wormwaker