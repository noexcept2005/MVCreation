#pragma once
////////////////////////////////////////////////
//         MV C++ Performer ר��ͷ�ļ�         //
//          by Wormwaker, ��ֹ����             //
////////////////////////////////////////////////

struct Command							//��������
{
	string command;

	clock_t start = 0L;
	short _perform_times = 0;

	Command(const string& s) : command(s)
	{
		start = clock();
	}
	inline bool Empty() const
	{
		return command.empty();
	}
	string GetMajor() const
	{
		for (int i = 0; i < command.size(); ++i)
		{
			if (command.at(i) == ' ')
				return command.substr(0, i);
			else if (i == command.size() - 1)
				return command;
		}
	}
	bool Perform()
	{
		XCPT_L
		++_perform_times;
		string major = GetMajor();
		if (command.empty() || major.empty())	return false;
		vector<string> a = CutLine(command, ' ');

		if (sequ(major, "text"))
		{
			if (a.size() < 2)
			{
				ErrorLogTip("text����������㣡", "Command::Perform");
				return true;
			}
			string minor = a.at(1);
			if (sequ(minor, "add"))
			{
				if (a.size() < 3)
				{
					ErrorLogTip("text add ����������㣡", "Command::Perform");
					return true;
				}
				TextElement tele;
				for (size_t i = 0; i < a.size() - 2; ++i)
				{
					if (strip(a.at(i)).empty()) continue;
					vector<string> itemcut = CutLine(a.at(i + 2), '=');
					if (itemcut.size() < 2)
					{
						ErrorLogTip("text add �������\""+a.at(i+2)+"\"��Ч��û�еȺţ�!", "Command::Perform");
						return true;
					}

					string skey = itemcut[0];
					string svalue = itemcut[1];
					//DebugLogFormat("skey=%s  svalue=%s", skey.c_str(), svalue.c_str());

					if (sequ(skey, "sx"))
						tele.sx = ParseNumber(svalue);
					else if (sequ(skey, "sy"))
						tele.sy = ParseNumber(svalue);
					else if (sequ(skey, "text"))
						tele.text = strrpc((char*)(unquote(svalue).c_str()), "`", " ");
					else if (sequ(skey, "s_color"))
						tele.s_color = ParseColor(strxhead(svalue));
					else if (sequ(skey, "a_in"))
						tele.a_in = ParseAnimaIn(unquote(svalue));
					else if (sequ(skey, "s_fs"))
						tele.s_fs = ParseNumber(svalue);
					else if (sequ(skey, "font") || sequ(skey, "fontname"))
						tele.fontid = GetFontNameID(unquote(svalue));
					else if (sequ(skey, "life"))
						tele.life = ParseNumber(svalue);
					else {
						tele.json.AddItem(skey, svalue);
					}
				}
				tele.BaseScaleHandling();
				elePfmr.AddText(move(tele));
			}
			else if (sequ(minor, "clear"))
			{
				elePfmr.ClearDerived<TextElement>();
			}
		}
		else if (sequ(major, "sleep"))
		{
			if (a.size() == 1)
			{
				ErrorLogTip("sleep����������㣡", "Command::Perform");
				return true;
			}
			clock_t ms = ParseNumber(a[1]);
			if (_perform_times == 1)
			{
				start = clock();
				return false;
			}
			else {
				return (clock() - start >= ms);
			}
		}
		else if (sequ(major, "sound"))
		{
			if (a.size() == 1)
			{
				ErrorLogTip("sound����������㣺����ָ�������", "Command::Perform");
				return true;
			}
			if (sequ(a[1], "quickplay"))
			{
				if (a.size() == 2)
				{
					ErrorLogTip("sound quickplay����������㣺����ָ���ļ�����", "Command::Perform");
					return true;
				}
				string filename = GetQuotedString(command, 2);
				sndMgr.QuickPlay(filename);
			}
			else {
				ErrorLogTip("sound: ��Ч�������� \"" + a[1] + "\"", "Command::Perform");
				return true;
			}
		}
		else if (sequ(major, "rect"))
		{
			if (a.size() == 1)
			{
				ErrorLogTip("rect����������㣺����ָ�������", "Command::Perform");
				return true;
			}
			if (sequ(a[1], "add"))
			{
				if (a.size() < 3)
				{
					ErrorLogTip("rect add ����������㣡", "Command::Perform");
					return true;
				}
				RectElement rele;
				for (size_t i = 0; i < a.size() - 2; ++i)
				{
					if (strip(a.at(i)).empty()) continue;
					vector<string> itemcut = CutLine(a.at(i + 2), '=');
					if (itemcut.size() < 2)
					{
						ErrorLogTip("rect add �������\"" + a.at(i + 2) + "\"��Ч��û�еȺţ�!", "Command::Perform");
						return true;
					}

					string skey = itemcut[0];
					string svalue = itemcut[1];
					//DebugLogFormat("skey=%s  svalue=%s", skey.c_str(), svalue.c_str());

					if(sequ(skey, "sx"))
						rele.sx = ParseNumber(svalue);
					else if (sequ(skey, "sy"))
						rele.sy = ParseNumber(svalue);
					else if (sequ(skey, "a_in"))
						rele.a_in = ParseAnimaIn(unquote(svalue));
					else if (sequ(skey, "life"))
						rele.life = ParseNumber(svalue);
					else {
						rele.json.AddItem(skey, svalue);
					}
				}
				elePfmr.AddRect(rele);
			}
			else if (sequ(a[1], "clear"))
			{
				elePfmr.ClearDerived<RectElement>();
			}
		}
		else if (sequ(major, "clear"))
		{
			elePfmr.Clear();
		}
		else if (sequ(major, "background"))
		{
			if (a.size() == 1)
			{
				ErrorLogTip("background����������㣺����ָ�������", "Command::Perform");
				return true;
			}
			if (sequ(a[1], "color"))
			{
				if (a.size() == 2)
				{
					ErrorLogTip("background color ����������㣺����ָ����ɫ��", "Command::Perform");
					return true;
				}
				bgMgr.SetBackColor(ParseColor(a[2]));
			}
			else if (sequ(a[1], "fade") || sequ(a[1], "fading"))
			{
				if (a.size() == 2)
				{
					ErrorLogTip("background fade ����������㣺����ָ��������", "Command::Perform");
					return true;
				}

				color_t from = bgMgr.GetBackColor();
				color_t to = BLACK;
				clock_t duration = 1000L;

				for (size_t i = 0; i < a.size() - 2; ++i)
				{
					if (strip(a.at(i)).empty()) continue;
					vector<string> itemcut = CutLine(a.at(i + 2), '=');
					if (itemcut.size() < 2)
					{
						ErrorLogTip("background fade �������\"" + a.at(i + 2) + "\"��Ч��û�еȺţ�!", "Command::Perform");
						return true;
					}

					string skey = itemcut[0];
					string svalue = itemcut[1];
					//DebugLogFormat("skey=%s  svalue=%s", skey.c_str(), svalue.c_str());
					if (sequ(skey, "from"))
						from = ParseColor(svalue);
					else if (sequ(skey, "to"))
						to = ParseColor(svalue);
					else if (sequ(skey, "duration") || sequ(skey, "time"))
						duration = ParseNumber(svalue);
					else {
						ErrorLogTip("background fade �������\"" + a.at(i + 2) + "\"��Ч��δ֪������!", "Command::Perform");
						return true;
					}
				}
				bgMgr.StartBackColorFading(from, to, duration);
			}
			else {
				ErrorLogTip("background: ��Ч��������\"" + a[1] + "\"", "Command::Perform");
				return true;
			}
		}
		else if (sequ(major, "camera"))
		{
			if (a.size() == 1)
			{
				ErrorLogTip("camera ����������㣺����ָ��������", "Command::Perform");
				return true;
			}
			if (sequ(a[1], "clear"))
			{	//˲���λ
				camera.Clear();
				camera.MotionStart();
			}
			else if (sequ(a[1], "set")	  //���ø������
				  || sequ(a[1], "return") //�����²����ص�ԭ��
				    )
			{	
				if (a.size() == 2)
				{
					ErrorLogTip("camera " + a[1] + " ����������㣺����ָ��������", "Command::Perform");
					return true;
				}
				for (size_t i = 0; i < a.size() - 2; ++i)
				{
					if (strip(a.at(i)).empty()) continue;
					vector<string> itemcut = CutLine(a.at(i + 2), '=');
					if (itemcut.size() < 2)
					{
						ErrorLogTip("camera " + a[1] + " �������\"" + a.at(i + 2) + "\"��Ч��û�еȺţ�!", "Command::Perform");
						return true;
					}

					string skey = itemcut[0];
					string svalue = itemcut[1];

					camera.SetData(skey, svalue);
				}
				if (sequ(a[1], "return"))
				{
					camera.SetData("ex", "uix/2");
					camera.SetData("ey", "uiy/2");
					camera.SetData("e_zoom", "1.0f");
					camera.SetData("e_alpha", "255s");
					camera.SetData("e_rot", "0.0f");
				}
				camera.MotionStart();
			}
		}
		else if (sequ(major, "region"))
		{
			if (a.size() == 1)
			{
				ErrorLogTip("region ����������㣺����ָ��������", "Command::Perform");
				return true;
			}
			if (sequ(a[1], "end") || sequ(a[1], "clear"))
			{
				regCtrl.DisableRegionDuration();
			}
			else if (sequ(a[1], "duration"))
			{
				if (a.size() == 2)
				{
					ErrorLogTip("region duration ����������㣺����ָ����������", "Command::Perform");
					return true;
				}
				regCtrl.SetRegionDuration(ParseNumber(a[2]));
			}
			else if (sequ(a[1], "wait"))
			{
				regCtrl.WaitForRegionDuration();
			}
			else if (sequ(a[1], "freeze_wait"))
			{
				regCtrl.WaitForRegionDuration(true);
			}
			else {
				ErrorLogTip("region ���������Ч��������\"" + a[1] + "\"", "Command::Perform");
				return true;
			}
        }
		else if (sequ(major, "effect"))
		{
			if (a.size() == 1)
			{
				ErrorLogTip("effect ����������㣺����ָ�������", "Command::Perform");
				return true;
			}
			if (sequ(a[1], "clear"))
			{
				camera.fx.clear();
			}
			else if (sequ(a[1], "add"))
			{
				if (a.size() == 2)
				{
					ErrorLogTip("camera " + a[1] + " ����������㣺����ָ��������", "Command::Perform");
					return true;
				}
				EFF_ID id = EFF_NONE;
				clock_t duration = 3000L;
				clock_t in_time = -1L;
				clock_t out_time = -1L;
				JSON json{};
				for (size_t i = 0; i < a.size() - 2; ++i)
				{
					if (strip(a.at(i)).empty()) continue;
					vector<string> itemcut = CutLine(a.at(i + 2), '=');
					if (itemcut.size() < 2)
					{
						ErrorLogTip("camera " + a[1] + " �������\"" + a.at(i + 2) + "\"��Ч��û�еȺţ�!", "Command::Perform");
						return true;
					}

					string skey = itemcut[0];
					string svalue = itemcut[1];

					if (sequ(skey, "id"))
						//id = ParseNumber(svalue);
						id = ParseEffectID(unquote(svalue));
					else if (sequ(skey, "duration"))
						duration = ParseNumber(svalue);
					else if (sequ(skey, "in_time"))
						in_time = ParseNumber(svalue);
					else if (sequ(skey, "out_time"))
						out_time = ParseNumber(svalue);
					else {
						json.AddItem(skey, svalue);
					}
				}
				Effect eff;
				if (in_time == -1L)
				{
					if (out_time == -1L)
						eff.SetClassic(id, duration, json);
					else {
						in_time = 0L;
						eff.Set(id, duration, in_time, out_time, json);
					}
				}
				else if (out_time == -1L)
				{
					out_time = 0L;
					eff.Set(id, duration, in_time, out_time, json);
				}
				else {
					eff.Set(id, duration, in_time, out_time, json);
				}
				camera.AddEffect(eff);
			}
			else {
				ErrorLogTip("effect ���������Ч��������\"" + a[1] + "\"!", "Command::Perform");
				return true;
			}
		}
		else if (sequ(major, "base_screen_scale"))
		{
			float scale = 1.0f;
			if (a.size() > 1)
				scale = ParseNumber(a[1]);
			g_base_scale = scale;
		}
		else {
			ErrorLogTip("��Ч�����������" + major, "Command::Perform");
		}
		return true;
		XCPT_R
		return true;
	}
};

class ScriptRunner {					//�ű�������
public:
	friend class ElementPerformer;

	ScriptRunner(){}
	~ScriptRunner(){}

	inline size_t RemainingCommandCount() const
	{
		return cmds.size();
	}
	Command& FrontCommand(void)
	{
		if (cmds.empty())
			throw out_of_range("�������Ϊ�գ�");
		return cmds.front();
	}
	void PushCommand(Command&& cmd)
	{
		if (cmd.Empty())	return;
		cmds.push(cmd);
	}
	void PopCommand()
	{
		cmds.pop();
	}

	void UpdateCommands()
	{
		if (cmds.empty())	return;
		bool bRet = cmds.front().Perform();
		if (bRet)	//����true�͵�����ָ�������
		{
			PopCommand();
		}			//����false���ָ���ִ�У�ֱ������true
	}
private:
	queue<Command> cmds;
}scriptRunner;

void ElementPerformer::AddDeltaTime(clock_t delta)
{
	for (auto& ele : m_elements)
		ele->start += delta;
	for (auto& ele : camera.fx)
		ele.start += delta;

	camera.motion_start += delta;

	if(scriptRunner.RemainingCommandCount() > 0U)
		scriptRunner.cmds.front().start += delta;
}

vector<string> ReadCommandStrings(const string& path)
{	//���ᴦ��ע�ͺ�Ԥ�������
	XCPT_L
	string filedir = GetFileDirectory(path);
	vector<string> res;
	vector<string> lines = ReadFileLines(path);
	for (int i = 0; i < lines.size(); ++i)
	{
		string line = lines.at(i);
		strip(line);
		//��������ע��
		if (line.empty() //|| line[0] == '#'
			|| line.size() >= 2 && strhead(line, 2) == "//")
		{
			continue;
		}
		//�ض�����ע��
		for (int j = 0; j < line.size(); ++j)
		{
			if (//line.at(j) == '#' ||
				j < line.size() - 1
				&& line.substr(j, 2) == "//")
			{
				line = line.substr(0, j);
				break;
			}
		}
		if (line.at(0) == '#')
		{	//Ԥ�������
			vector<string> _cut = CutLine(strxhead(line), ' ');
			if (sequ(_cut[0], "include"))
			{
				if (_cut.size() == 1)
				{
					ErrorLogTip("Ԥ�������#include ���󣺱���ָ���ļ�·����", "ReadCommandStrings");
					throw logic_error{ "#include ȱʧ����·��" };
				}
				string filename = GetQuotedString(line, 1, ' ');
				if (!ExistFile(filename))
				{
					if (ExistFile(filedir + filename))	//���·��
						filename = filedir + filename;
					else {
						ErrorLogTip("Ԥ�������#include �����ļ�·����Ч��", "ReadCommandStrings");
						throw logic_error{ "#include ·����Ч" };
					}
				}
				vector<string> _addition = ReadCommandStrings(filename);	//�ݹ����
				for (const auto& ln : _addition)
					res.push_back(ln);
			}
			else {
				ErrorLogTip("��Ч��Ԥ������䣺#" + _cut[0], "ReadCommandStrings");
				throw logic_error{ "��Ч��Ԥ�������" };
			}
		}
		else
		{	//����Ԥ������䲻�������нű���
			res.push_back(line);
		}
	}
	return res;
	XCPT_R
	return vector<string>();
}
queue<Command> ReadCommands(const string& path)
{
	queue<Command> cmds;
	vector<string> lines = ReadCommandStrings(path);
	for (auto& line : lines)
	{
		Command c(line);
		c.start = clock();
		cmds.push(c);
	}
	return cmds;
}
void AddCommands(const string& path)
{
	XCPT_L
	if (!ExistFile(path))
	{
		ErrorLogTip("�Ҳ����ű��ļ�: " + path, "AddCommands");
		return;
	}
	vector<string> lines = ReadCommandStrings(path);
	for (auto& line : lines)
	{
		scriptRunner.PushCommand(line);
	}
	XCPT_R
}