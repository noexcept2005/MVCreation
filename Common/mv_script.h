#pragma once
////////////////////////////////////////////////
//         MV C++ Performer 专属头文件         //
//          by Wormwaker, 禁止盗用             //
////////////////////////////////////////////////

struct Command							//单条命令
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
				ErrorLogTip("text命令参数不足！", "Command::Perform");
				return true;
			}
			string minor = a.at(1);
			if (sequ(minor, "add"))
			{
				if (a.size() < 3)
				{
					ErrorLogTip("text add 命令参数不足！", "Command::Perform");
					return true;
				}
				TextElement tele;
				for (size_t i = 0; i < a.size() - 2; ++i)
				{
					if (strip(a.at(i)).empty()) continue;
					vector<string> itemcut = CutLine(a.at(i + 2), '=');
					if (itemcut.size() < 2)
					{
						ErrorLogTip("text add 命令参数\""+a.at(i+2)+"\"无效（没有等号）!", "Command::Perform");
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
				ErrorLogTip("sleep命令参数不足！", "Command::Perform");
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
				ErrorLogTip("sound命令参数不足：必须指定子命令。", "Command::Perform");
				return true;
			}
			if (sequ(a[1], "quickplay"))
			{
				if (a.size() == 2)
				{
					ErrorLogTip("sound quickplay命令参数不足：必须指定文件名。", "Command::Perform");
					return true;
				}
				string filename = GetQuotedString(command, 2);
				sndMgr.QuickPlay(filename);
			}
			else {
				ErrorLogTip("sound: 无效的子命令 \"" + a[1] + "\"", "Command::Perform");
				return true;
			}
		}
		else if (sequ(major, "rect"))
		{
			if (a.size() == 1)
			{
				ErrorLogTip("rect命令参数不足：必须指定子命令。", "Command::Perform");
				return true;
			}
			if (sequ(a[1], "add"))
			{
				if (a.size() < 3)
				{
					ErrorLogTip("rect add 命令参数不足！", "Command::Perform");
					return true;
				}
				RectElement rele;
				for (size_t i = 0; i < a.size() - 2; ++i)
				{
					if (strip(a.at(i)).empty()) continue;
					vector<string> itemcut = CutLine(a.at(i + 2), '=');
					if (itemcut.size() < 2)
					{
						ErrorLogTip("rect add 命令参数\"" + a.at(i + 2) + "\"无效（没有等号）!", "Command::Perform");
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
				ErrorLogTip("background命令参数不足：必须指定子命令。", "Command::Perform");
				return true;
			}
			if (sequ(a[1], "color"))
			{
				if (a.size() == 2)
				{
					ErrorLogTip("background color 命令参数不足：必须指定颜色。", "Command::Perform");
					return true;
				}
				bgMgr.SetBackColor(ParseColor(a[2]));
			}
			else if (sequ(a[1], "fade") || sequ(a[1], "fading"))
			{
				if (a.size() == 2)
				{
					ErrorLogTip("background fade 命令参数不足：必须指定参数。", "Command::Perform");
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
						ErrorLogTip("background fade 命令参数\"" + a.at(i + 2) + "\"无效（没有等号）!", "Command::Perform");
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
						ErrorLogTip("background fade 命令参数\"" + a.at(i + 2) + "\"无效（未知参数）!", "Command::Perform");
						return true;
					}
				}
				bgMgr.StartBackColorFading(from, to, duration);
			}
			else {
				ErrorLogTip("background: 无效的子命令\"" + a[1] + "\"", "Command::Perform");
				return true;
			}
		}
		else if (sequ(major, "camera"))
		{
			if (a.size() == 1)
			{
				ErrorLogTip("camera 命令参数不足：必须指定参数。", "Command::Perform");
				return true;
			}
			if (sequ(a[1], "clear"))
			{	//瞬间归位
				camera.Clear();
				camera.MotionStart();
			}
			else if (sequ(a[1], "set")	  //设置各项参数
				  || sequ(a[1], "return") //以以下参数回到原点
				    )
			{	
				if (a.size() == 2)
				{
					ErrorLogTip("camera " + a[1] + " 命令参数不足：必须指定参数。", "Command::Perform");
					return true;
				}
				for (size_t i = 0; i < a.size() - 2; ++i)
				{
					if (strip(a.at(i)).empty()) continue;
					vector<string> itemcut = CutLine(a.at(i + 2), '=');
					if (itemcut.size() < 2)
					{
						ErrorLogTip("camera " + a[1] + " 命令参数\"" + a.at(i + 2) + "\"无效（没有等号）!", "Command::Perform");
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
				ErrorLogTip("region 命令参数不足：必须指定参数。", "Command::Perform");
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
					ErrorLogTip("region duration 命令参数不足：必须指定毫秒数。", "Command::Perform");
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
				ErrorLogTip("region 命令错误：无效的子命令\"" + a[1] + "\"", "Command::Perform");
				return true;
			}
        }
		else if (sequ(major, "effect"))
		{
			if (a.size() == 1)
			{
				ErrorLogTip("effect 命令参数不足：必须指定子命令。", "Command::Perform");
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
					ErrorLogTip("camera " + a[1] + " 命令参数不足：必须指定参数。", "Command::Perform");
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
						ErrorLogTip("camera " + a[1] + " 命令参数\"" + a.at(i + 2) + "\"无效（没有等号）!", "Command::Perform");
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
				ErrorLogTip("effect 命令错误：无效的子命令\"" + a[1] + "\"!", "Command::Perform");
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
			ErrorLogTip("无效或不完整的命令：" + major, "Command::Perform");
		}
		return true;
		XCPT_R
		return true;
	}
};

class ScriptRunner {					//脚本解释器
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
			throw out_of_range("命令队列为空！");
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
		if (bRet)	//返回true就弹出该指令（多数）
		{
			PopCommand();
		}			//返回false则该指令反复执行，直到返回true
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
{	//将会处理注释和预处理语句
	XCPT_L
	string filedir = GetFileDirectory(path);
	vector<string> res;
	vector<string> lines = ReadFileLines(path);
	for (int i = 0; i < lines.size(); ++i)
	{
		string line = lines.at(i);
		strip(line);
		//舍弃整行注释
		if (line.empty() //|| line[0] == '#'
			|| line.size() >= 2 && strhead(line, 2) == "//")
		{
			continue;
		}
		//截断行内注释
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
		{	//预处理语句
			vector<string> _cut = CutLine(strxhead(line), ' ');
			if (sequ(_cut[0], "include"))
			{
				if (_cut.size() == 1)
				{
					ErrorLogTip("预处理语句#include 错误：必须指定文件路径。", "ReadCommandStrings");
					throw logic_error{ "#include 缺失参数路径" };
				}
				string filename = GetQuotedString(line, 1, ' ');
				if (!ExistFile(filename))
				{
					if (ExistFile(filedir + filename))	//相对路径
						filename = filedir + filename;
					else {
						ErrorLogTip("预处理语句#include 错误：文件路径无效。", "ReadCommandStrings");
						throw logic_error{ "#include 路径无效" };
					}
				}
				vector<string> _addition = ReadCommandStrings(filename);	//递归调用
				for (const auto& ln : _addition)
					res.push_back(ln);
			}
			else {
				ErrorLogTip("无效的预处理语句：#" + _cut[0], "ReadCommandStrings");
				throw logic_error{ "无效的预处理语句" };
			}
		}
		else
		{	//上述预处理语句不放在运行脚本中
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
		ErrorLogTip("找不到脚本文件: " + path, "AddCommands");
		return;
	}
	vector<string> lines = ReadCommandStrings(path);
	for (auto& line : lines)
	{
		scriptRunner.PushCommand(line);
	}
	XCPT_R
}