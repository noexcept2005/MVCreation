#pragma once
////////////////////////////////////////////////
//         MV C++ Performer ר��ͷ�ļ�         //
//          by Wormwaker, ��ֹ����             //
////////////////////////////////////////////////

using AnimaIn = USHORT;				//�볡����ID
using AnimaOut = USHORT;			//��������ID

#define AIN_NONE					0
#define AIN_FADEIN					1
#define AIN_ENLARGE					2
#define AIN_SHRINK					3
#define AIN_FROM_LEFT_CUBIC			4	//����߽��룬����
#define AIN_FROM_LEFT_EXPO			5	//����߽��룬����
#define AIN_FROM_RIGHT_CUBIC		6	//���ұ߽��룬����
#define AIN_FROM_RIGHT_EXPO			7	//���ұ߽��룬����
#define AIN_FROM_UP_CUBIC			8	//���ϱ߽��룬����
#define AIN_FROM_UP_EXPO			9	//���ϱ߽��룬����
#define AIN_FROM_DOWN_CUBIC			10	//���±߽��룬����
#define AIN_FROM_DOWN_EXPO			11	//���±߽��룬����
#define AIN_FROM_LEFTDOWN_CUBIC		12	//�����·����룬����
#define AIN_FROM_LEFTDOWN_EXPO		13	//�����·����룬����
#define AIN_FROM_LEFTUP_CUBIC		14	//�����Ϸ����룬����
#define AIN_FROM_LEFTUP_EXPO		15	//�����Ϸ����룬����
#define AIN_FROM_RIGHTUP_CUBIC		16	//�����Ϸ����룬����
#define AIN_FROM_RIGHTUP_EXPO		17	//�����Ϸ����룬����
#define AIN_FROM_RIGHTDOWN_CUBIC	18	//�����·����룬����
#define AIN_FROM_RIGHTDOWN_EXPO		19	//�����·����룬����
#define AIN_ROTATION				20	//��������

inline bool AnimaInNeedRotation(const AnimaIn ain)
{
	return (ain == AIN_ROTATION);
}
AnimaIn ParseAnimaIn(const string& s)
{
	if (sequ(s, "none"))
		return AIN_NONE;
	if (sequ(s, "fadein"))
		return AIN_FADEIN;
	if (sequ(s, "enlarge"))
		return AIN_ENLARGE;
	if (sequ(s, "shrink"))
		return AIN_SHRINK;
	if (sequ(s, "from_left_cubic"))
		return AIN_FROM_LEFT_CUBIC;
	if (sequ(s, "from_left_expo"))
		return AIN_FROM_LEFT_EXPO;
	if (sequ(s, "from_right_cubic"))
		return AIN_FROM_RIGHT_CUBIC;
	if (sequ(s, "from_right_expo"))
		return AIN_FROM_RIGHT_EXPO;
	if (sequ(s, "from_up_cubic"))
		return AIN_FROM_UP_CUBIC;
	if (sequ(s, "from_up_expo"))
		return AIN_FROM_UP_EXPO;
	if (sequ(s, "from_down_cubic"))
		return AIN_FROM_DOWN_CUBIC;
	if (sequ(s, "from_down_expo"))
		return AIN_FROM_DOWN_EXPO;
	if (sequ(s, "from_leftdown_cubic"))
		return AIN_FROM_LEFTDOWN_CUBIC;
	if (sequ(s, "from_leftdown_expo"))
		return AIN_FROM_LEFTDOWN_EXPO;
	if (sequ(s, "from_rightdown_cubic"))
		return AIN_FROM_RIGHTDOWN_CUBIC;
	if (sequ(s, "from_rightdown_expo"))
		return AIN_FROM_RIGHTDOWN_EXPO;
	if (sequ(s, "from_rightup_cubic"))
		return AIN_FROM_RIGHTUP_CUBIC;
	if (sequ(s, "from_rightup_expo"))
		return AIN_FROM_RIGHTUP_EXPO;
	if (sequ(s, "from_leftup_cubic"))
		return AIN_FROM_LEFTUP_CUBIC;
	if (sequ(s, "from_leftup_expo"))
		return AIN_FROM_LEFTUP_EXPO;
	if (sequ(s, "rotation"))
		return AIN_ROTATION;

	ErrorLogTip("��Ч���볡��������\"" + s + "\"", "ParseAnimaIn");
	return AIN_NONE;
}

#define AOUT_NONE					0
#define AOUT_FADEOUT				1
#define AOUT_ENLARGE				2
#define AOUT_SHRINK					3
#define AOUT_TO_LEFT_CUBIC			4		//������뿪������
#define AOUT_TO_LEFT_EXPO			5		//������뿪������
#define AOUT_TO_RIGHT_CUBIC			6		//���ұ��뿪������
#define AOUT_TO_RIGHT_EXPO			7		//���ұ��뿪������
#define AOUT_TO_UP_CUBIC			8		//���ϱ��뿪������
#define AOUT_TO_UP_EXPO				9		//���ϱ��뿪������
#define AOUT_TO_DOWN_CUBIC			10		//���±��뿪������
#define AOUT_TO_DOWN_EXPO			11		//���±��뿪������
#define AOUT_TO_LEFTDOWN_CUBIC		12		//�����±��뿪������
#define AOUT_TO_LEFTDOWN_EXPO		13		//�����±��뿪������
#define AOUT_TO_RIGHTDOWN_CUBIC		14		//�����±��뿪������
#define AOUT_TO_RIGHTDOWN_EXPO		15		//�����±��뿪������
#define AOUT_TO_LEFTUP_CUBIC		16		//�����ϱ��뿪������
#define AOUT_TO_LEFTUP_EXPO			17		//�����ϱ��뿪������
#define AOUT_TO_RIGHTUP_CUBIC		18		//�����ϱ��뿪������
#define AOUT_TO_RIGHTUP_EXPO		19		//�����ϱ��뿪������
#define AOUT_ROTATION				20		//�����뿪

inline bool AnimaOutNeedRotation(const AnimaOut aout)
{
	return (aout == AOUT_ROTATION);
}
AnimaOut ParseAnimaOut(const string& s)
{
	if (sequ(s, "none"))
		return AOUT_NONE;
	if (sequ(s, "fadeout"))
		return AOUT_FADEOUT;
	if (sequ(s, "enlarge"))
		return AOUT_ENLARGE;
	if (sequ(s, "shrink"))
		return AOUT_SHRINK;
	if (sequ(s, "to_left_cubic"))
		return AOUT_TO_LEFT_CUBIC;
	if (sequ(s, "to_left_expo"))
		return AOUT_TO_LEFT_EXPO;
	if (sequ(s, "to_right_cubic"))
		return AOUT_TO_RIGHT_CUBIC;
	if (sequ(s, "to_right_expo"))
		return AOUT_TO_RIGHT_EXPO;
	if (sequ(s, "to_up_cubic"))
		return AOUT_TO_UP_CUBIC;
	if (sequ(s, "to_up_expo"))
		return AOUT_TO_UP_EXPO;
	if (sequ(s, "to_down_cubic"))
		return AOUT_TO_DOWN_CUBIC;
	if (sequ(s, "to_down_expo"))
		return AOUT_TO_DOWN_EXPO;
	if (sequ(s, "to_leftdown_cubic"))
		return AOUT_TO_LEFTDOWN_CUBIC;
	if (sequ(s, "to_leftdown_expo"))
		return AOUT_TO_LEFTDOWN_EXPO;
	if (sequ(s, "to_rightdown_cubic"))
		return AOUT_TO_RIGHTDOWN_CUBIC;
	if (sequ(s, "to_rightdown_expo"))
		return AOUT_TO_RIGHTDOWN_EXPO;
	if (sequ(s, "to_leftup_cubic"))
		return AOUT_TO_LEFTUP_CUBIC;
	if (sequ(s, "to_leftup_expo"))
		return AOUT_TO_LEFTUP_EXPO;
	if (sequ(s, "to_rightup_cubic"))
		return AOUT_TO_RIGHTUP_CUBIC;
	if (sequ(s, "to_rightup_expo"))
		return AOUT_TO_RIGHTUP_EXPO;
	if (sequ(s, "rotation"))
		return AOUT_ROTATION;
	ErrorLogTip("��Ч�ĳ�����������\"" + s + "\"", "ParseAnimaOut");
	return AOUT_NONE;
}

using ChangeFunc = USHORT;			//�仯����ID

#define CHGF_LERP					0
#define CHGF_EASE_OUT_CUBIC			1
#define CHGF_EASE_IN_EXPO			2
#define CHGF_EASE_IN_OUT_SINE		3
#define CHGF_EASE_IN_OUT_BACK		4
#define CHGF_EASE_IN_OUT_CUBIC		5
#define CHGF_EASE_IN_OUT_ELASTIC    6
#define CHGF_EASE_IN_OUT_EXPO       7
#define CHGF_EASE_IN_OUT_BOUNCE     8
#define CHGF_EASE_OUT_BOUNCE		9

double(CJZAPI *pchange_functions[ ] ) (double) 
	= { SelfFunc, EaseOutCubic, EaseInExpo, EaseInOutSine, EaseInOutBack,
        EaseInOutCubic, EaseInOutElastic, EaseInOutExpo, EaseInOutBounce,
	    EaseOutBounce,
	  };

decltype(auto) GetChangeFunction(ChangeFunc id)
{
	if (id >= _countof(pchange_functions))
	{
		ErrorLogTip("�仯����ID����Խ�磡", "GetChangeFunction");
		return pchange_functions[0];
	}
	return pchange_functions[id];
}
ChangeFunc ParseChangeFunctionID(const string& s)
{
	if (sequ(s, "lerp"))
		return CHGF_LERP;
	if (sequ(s, "ease_out_cubic"))
		return CHGF_EASE_OUT_CUBIC;
	if (sequ(s, "ease_in_expo"))
		return CHGF_EASE_IN_EXPO;
	if (sequ(s, "ease_in_out_sine"))
		return CHGF_EASE_IN_OUT_SINE;
	if (sequ(s, "ease_in_out_back"))
		return CHGF_EASE_IN_OUT_BACK;
	if (sequ(s, "ease_in_out_cubic"))
		return CHGF_EASE_IN_OUT_CUBIC;
	if (sequ(s, "ease_in_out_elastic"))
		return CHGF_EASE_IN_OUT_ELASTIC;
	if (sequ(s, "ease_in_out_expo"))
		return CHGF_EASE_IN_OUT_EXPO;
	if (sequ(s, "ease_in_out_bounce"))
		return CHGF_EASE_IN_OUT_BOUNCE;
	if (sequ(s, "ease_out_bounce"))
		return CHGF_EASE_OUT_BOUNCE;
	ErrorLogTip("��Ч�ı仯��������\"" + s + "\"��", "ParseChangeFunctionID");
	return CHGF_LERP;
}


struct TextElement					//�ı�Ԫ��
{
	float sx = 100.0f;				//��ʼX����
	float sy = 100.0f;				//��ʼY����
	AnimaIn a_in = AIN_FADEIN;		//�볡Ч��
	string text = "Text";			//�ı�
	color_t s_color = WHITE;			//��ʼ��ɫ
	int s_fs = 70;				//��ʼ�ֺ�
	FontNameID fontid = 0;			//��������ID

	JSON json;						//��������
	clock_t life;					//��ʾ����ʱ��
	clock_t start;					//��ʼ��ʱ���

	TextElement() { 
		sx = sy = 100.0f; start = 0L; BaseScaleHandling();
	}
	TextElement(float _sx, float _sy, clock_t life_ms, AnimaIn ain, const string& _text,
		        color_t scolor, int sfs, const string& fontname,
		        const JSON& _json = JSON()) 
		: sx(_sx), sy(_sy), a_in(ain), life(life_ms), text(_text), s_color(scolor),
		s_fs(sfs), fontid(GetFontNameID(fontname)), json(_json) 
	{
		BaseScaleHandling();
	}
	~TextElement() { json.Clear(); }

	void Start()
	{
		start = clock();
	}
	inline void BaseScaleHandling()
	{
		return;

		/*XCPT_L
		sx *= g_scale / g_base_scale;
		sy *= g_scale / g_base_scale;
		s_fs *= g_scale / g_base_scale;
		if (json.HaveKey("ex"))
			json.SetValueRaw("ex", cstr(ParseNumber(json.GetValueRaw("ex")) * g_scale / g_base_scale));
		if (json.HaveKey("ey"))
			json.SetValueRaw("ey", cstr(ParseNumber(json.GetValueRaw("ey")) * g_scale / g_base_scale));
		if (json.HaveKey("e_fs"))
			json.SetValueRaw("e_fs", cstr(ParseNumber(json.GetValueRaw("e_fs")) * g_scale / g_base_scale));
		XCPT_R*/
	}
#define TEXT_DEF_IN_TIME		500L
#define TEXT_DEF_OUT_TIME		500L
	void Draw(PIMAGE imgBuffer = nullptr)
	{
		XCPT_L
		if (clock() - start > life)
			return;
		float x = sx, y = sy;
		float s_rot = json.HaveKey("s_rot") ? ParseNumber(json.GetValueRaw("s_rot")) : 0.0f;
		float e_rot = json.HaveKey("e_rot") ? ParseNumber(json.GetValueRaw("e_rot")) : s_rot;
		float rot = s_rot;
		color_t color = s_color;
		color_t e_color = json.HaveKey("e_color") ? json.GetColor("e_color") : s_color;
		short fs = s_fs;
		float ex = json.HaveKey("ex") ? ParseNumber(json.GetValueRaw("ex")) : sx;
		float ey = json.HaveKey("ey") ? ParseNumber(json.GetValueRaw("ey")) : sy;
		short e_fs = json.HaveKey("e_fs") ? (short)ParseNumber(json.GetValueRaw("e_fs")) : s_fs;
		clock_t in_time = json.HaveKey("in_time") ? (clock_t)ParseNumber(json.GetValueRaw("in_time")) : TEXT_DEF_IN_TIME;
		if (a_in == AIN_NONE)
			in_time = 0L;
		AnimaOut a_out = json.HaveKey("a_out") ? ParseAnimaOut(json.GetString("a_out")) : AOUT_FADEOUT;
		clock_t out_time = json.HaveKey("out_time") ? (clock_t)ParseNumber(json.GetValueRaw("out_time")) : TEXT_DEF_OUT_TIME;
		if (a_out == AOUT_NONE)
			out_time = 0L;

		float csx=0.0f, csy=0.0f, cex=0.0f, cey=0.0f;
		//if (!fequ(s_rot, 0.0f) || !fequ(e_rot, 0.0f) || AnimaInNeedRotation(a_in) || AnimaOutNeedRotation(a_out))
		//{
			if (!json.HaveKey("csx"))	//��ʼԲ��X����
			{
				int text_w = text.length() * s_fs / 2.0f;
				int text_h = s_fs;
				csx = 
					sx + (text_w / 2.0f)
					     /
					     cos(DegToRad(s_rot * 10.0f));

				csy = 
				sy + sqrt(text_w*text_w / 4.0f + text_h * text_h / 4.0f)
					*
					sin(DegToRad(s_rot * 10.0f) - atan2f(text_h, text_w));
				/*double angle = DegToRad(s_rot);
				csx = x + (text_w / 2.0) * cos(angle) - (text_h / 2.0) * sin(angle);
				csy = y + (text_w / 2.0) * sin(angle) + (text_h / 2.0) * cos(angle);*/

				json.AddItem("csx", str(csx) + "f");
				json.AddItem("csy", str(csy) + "f");
			}
			else {
				csx = json.GetFloat("csx");
				csy = json.GetFloat("csy");
			}

			if (!json.HaveKey("cex"))	//����Բ��X����
			{
				int text_w = text.length() * e_fs / 2.0f;
				int text_h = e_fs;
				cex =	
					ex + (text_w / 2.0f)
					/
					cos(DegToRad(e_rot * 10.0f));

				cey =
					ey + sqrt(text_w*text_w / 4.0f + text_h * text_h / 4.0f)
					*
					sin(DegToRad(e_rot * 10.0f) - atan2f(text_h, text_w));
				/*double angle = DegToRad(e_rot);
				cex = x + (text_w / 2.0) * cos(angle) - (text_h / 2.0) * sin(angle);
				cey = y + (text_w / 2.0) * sin(angle) + (text_h / 2.0) * cos(angle);

				json.AddItem("cex", str(cex) + "f");
				json.AddItem("cey", str(cey) + "f");*/
			}
			else {
				cex = json.GetFloat("cex");
				cey = json.GetFloat("cey");
			}
		//}

		if (in_time > 0L && clock() - start < in_time)
		{	//�볡
			double in_ratio = (clock() - start) / double(in_time);
			rot = s_rot;

			switch (a_in)
			{
			case AIN_FADEIN:
			{
				color = StepColor(bgMgr.GetBackColor(), s_color, in_ratio);
				break;
			}
			case AIN_ENLARGE:
			{
				color = StepColor(bgMgr.GetBackColor(), s_color, in_ratio);
				fs = LerpClamp<short>(fs * 0.02, fs, EaseOutCubic(in_ratio));

				//x = csx - fs * text.length() / 4.0f;
				//y = csy - fs / 2.0f;
				x = csx
					- (fs * text.length() / 4.0f)
					/
					cos(DegToRad(rot * 10.0f));
				y = csy
					- sqrt(pow(text.length()*fs / 2.0f, 2) / 4.0f +
						pow(fs, 2) / 4.0f)
					*
					sin(DegToRad(s_rot * 10.0f) - atan2f(fs, text.length()*fs / 2.0f));

				break;
			}
			case AIN_SHRINK: {
				color = StepColor(bgMgr.GetBackColor(), s_color, in_ratio);
				fs = LerpClamp<short>(fs * 30, fs, EaseOutCubic(in_ratio));

				//x = csx - fs * text.length() / 4.0f;
				//y = csy - fs / 2.0f;
				x = csx
					- (fs * text.length() / 4.0f)
					/
					cos(DegToRad(rot * 10.0f));
				y = csy
					- sqrt(pow(text.length()*fs / 2.0f, 2) / 4.0f +
						pow(fs, 2) / 4.0f)
					*
					sin(DegToRad(s_rot * 10.0f) - atan2f(fs, text.length()*fs / 2.0f));

				break;
			}
			case AIN_FROM_LEFT_CUBIC:
			{
				x = LerpClamp<float>(-100.0f, sx, EaseOutCubic(in_ratio));
				y = sy;
				break;
			}
			case AIN_FROM_LEFT_EXPO:
			{
				x = LerpClamp<float>(-100.0f, sx, EaseInExpo(in_ratio));
				y = sy;
				break;
			}
			case AIN_FROM_RIGHT_CUBIC:
			{
				x = LerpClamp<float>(uix, sx, EaseOutCubic(in_ratio));
				y = sy;
				break;
			}
			case AIN_FROM_RIGHT_EXPO:
			{
				x = LerpClamp<float>(uix, sx, EaseInExpo(in_ratio));
				y = sy;
				break;
			}
			case AIN_FROM_UP_CUBIC:
			{
				y = LerpClamp<float>(-80.0f, sy, EaseOutCubic(in_ratio));
				x = sx;
				break;
			}
			case AIN_FROM_UP_EXPO:
			{
				y = LerpClamp<float>(-80.0f, sy, EaseInExpo(in_ratio));
				x = sx;
				break;
			}
			case AIN_FROM_DOWN_CUBIC:
			{
				y = LerpClamp<float>(uiy, sy, EaseOutCubic(in_ratio));
				x = sx;
				break;
			}
			case AIN_FROM_DOWN_EXPO:
			{
				y = LerpClamp<float>(uiy, sy, EaseInExpo(in_ratio));
				x = sx;
				break;
			}
			case AIN_FROM_LEFTDOWN_CUBIC: {
				x = LerpClamp<float>(-100, sx, EaseOutCubic(in_ratio));
				y = LerpClamp<float>(uiy, sy, EaseOutCubic(in_ratio));
				break;
			}
			case AIN_FROM_LEFTDOWN_EXPO: {
				x = LerpClamp<float>(-100, sx, EaseInExpo(in_ratio));
				y = LerpClamp<float>(uiy, sy, EaseInExpo(in_ratio));
				break;
			}
			case AIN_FROM_RIGHTDOWN_CUBIC: {
				x = LerpClamp<float>(uix, sx, EaseOutCubic(in_ratio));
				y = LerpClamp<float>(uiy, sy, EaseOutCubic(in_ratio));
				break;
			}
			case AIN_FROM_RIGHTDOWN_EXPO: {
				x = LerpClamp<float>(uix, sx, EaseInExpo(in_ratio));
				y = LerpClamp<float>(uiy, sy, EaseInExpo(in_ratio));
				break;
			}
			case AIN_FROM_LEFTUP_CUBIC: {
				x = LerpClamp<float>(-100, sx, EaseOutCubic(in_ratio));
				y = LerpClamp<float>(-100, sy, EaseOutCubic(in_ratio));
				break;
			}
			case AIN_FROM_LEFTUP_EXPO: {
				x = LerpClamp<float>(-100, sx, EaseInExpo(in_ratio));
				y = LerpClamp<float>(-100, sy, EaseInExpo(in_ratio));
				break;
			}
			case AIN_FROM_RIGHTUP_CUBIC: {
				x = LerpClamp<float>(uix, sx, EaseOutCubic(in_ratio));
				y = LerpClamp<float>(-100, sy, EaseOutCubic(in_ratio));
				break;
			}
			case AIN_FROM_RIGHTUP_EXPO: {
				x = LerpClamp<float>(uix, sx, EaseInExpo(in_ratio));
				y = LerpClamp<float>(-100, sy, EaseInExpo(in_ratio));
				break;
			}
			case AIN_ROTATION: {
				rot = LerpClamp<float>(s_rot - 7200.0f, s_rot, EaseOutCubic(in_ratio));
				fs = LerpClamp<float>(s_fs * 0.02f, s_fs, in_ratio);

				/*x = csx 
					- (fs * text.length() / 4.0f)
					/
					cos(DegToRad(rot * 10.0f));
				y = csy
					- sqrt(pow(text.length()*fs / 2.0f, 2) / 4.0f+
						pow(fs, 2) / 4.0f)
					*
					sin(DegToRad(s_rot * 10.0f) - atan2f(fs, text.length()*fs / 2.0f));
					*/
				break;
			}
			default:
				break;
			}
			if (fequ(rot, 0.0f))
				setfont(fs, 0, fontnames[fontid], imgBuffer);
			else
				setfont(fs, 0, fontnames[fontid], rot, rot, 0, 0, 0, 0, imgBuffer);
			setcolor(color, imgBuffer);
			outtextxy(x, y, text.c_str(), imgBuffer);
		}
		else if (out_time >= 0L && clock() - start >= life - out_time)
		{	//����
			double out_ratio = (clock() - start - (life - out_time)) / double(out_time);
			fs = e_fs;
			color = e_color;
			x = ex, y = ey;
			rot = e_rot;

			switch (a_out)
			{
			case AOUT_FADEOUT:
			{
				if (e_color == bgMgr.GetBackColor() || e_color == bgMgr.GetBackColor())
					break;
				color = StepColor(e_color, bgMgr.GetBackColor(), out_ratio);
				break;
			}
			case AOUT_ENLARGE: {
				if (e_color != bgMgr.GetBackColor() && e_color != bgMgr.GetBackColor())
					color = StepColor(e_color, bgMgr.GetBackColor(), out_ratio);
				fs = LerpClamp<short>(fs, fs * 30.0, EaseInExpo(out_ratio));
				break;
			}
			case AOUT_SHRINK: {
				if (e_color != bgMgr.GetBackColor() && e_color != bgMgr.GetBackColor())
					color = StepColor(e_color, bgMgr.GetBackColor(), out_ratio);
				fs = LerpClamp<short>(fs, fs * 0.02, EaseInExpo(out_ratio));
				break;
			}
			case AOUT_TO_LEFT_CUBIC: {
				x = LerpClamp<float>(ex, -100.0f, EaseOutCubic(out_ratio));
				y = ey;
				break;
			}
			case AOUT_TO_LEFT_EXPO: {
				x = LerpClamp<float>(ex, -100.0f, EaseInExpo(out_ratio));
				y = ey;
				break;
			}			
			case AOUT_TO_RIGHT_CUBIC: {
				x = LerpClamp<float>(ex, uix, EaseOutCubic(out_ratio));
				y = ey;
				break;
			}
			case AOUT_TO_RIGHT_EXPO: {
				x = LerpClamp<float>(ex, uix, EaseInExpo(out_ratio));
				y = ey;
				break;
			}
			case AOUT_TO_UP_CUBIC: {
				y = LerpClamp<float>(ey, -100.0f, EaseOutCubic(out_ratio));
				x = ex;
				break;
			}
			case AOUT_TO_UP_EXPO: {
				y = LerpClamp<float>(ey, -100.0f, EaseInExpo(out_ratio));
				x = ex;
				break;
			}
			case AOUT_TO_DOWN_CUBIC: {
				y = LerpClamp<float>(ey, uiy, EaseOutCubic(out_ratio));
				x = ex;
				break;
			}
			case AOUT_TO_DOWN_EXPO: {
				y = LerpClamp<float>(ey, uiy, EaseInExpo(out_ratio));
				x = ex;
				break;
			}
			case AOUT_TO_LEFTDOWN_CUBIC: {
				x = LerpClamp<float>(ex, -100.0f, EaseOutCubic(out_ratio));
				y = LerpClamp<float>(ey, uiy, EaseOutCubic(out_ratio));
				break;
			}
			case AOUT_TO_LEFTDOWN_EXPO: {
				x = LerpClamp<float>(ex, -100.0f, EaseInExpo(out_ratio));
				y = LerpClamp<float>(ey, uiy, EaseInExpo(out_ratio));
				break;
			}
			case AOUT_TO_RIGHTDOWN_CUBIC: {
				x = LerpClamp<float>(ex, uix, EaseOutCubic(out_ratio));
				y = LerpClamp<float>(ey, uiy, EaseOutCubic(out_ratio));
				break;
			}
			case AOUT_TO_RIGHTDOWN_EXPO: {
				x = LerpClamp<float>(ex, uix, EaseInExpo(out_ratio));
				y = LerpClamp<float>(ey, uiy, EaseInExpo(out_ratio));
				break;
			}
			case AOUT_TO_LEFTUP_CUBIC: {
				x = LerpClamp<float>(ex, -100.0f, EaseOutCubic(out_ratio));
				y = LerpClamp<float>(ey, -100.0f, EaseOutCubic(out_ratio));
				break;
			}
			case AOUT_TO_LEFTUP_EXPO: {
				x = LerpClamp<float>(ex, -100.0f, EaseInExpo(out_ratio));
				y = LerpClamp<float>(ey, -100.0f, EaseInExpo(out_ratio));
				break;
			}
			case AOUT_TO_RIGHTUP_CUBIC: {
				x = LerpClamp<float>(ex, uix, EaseOutCubic(out_ratio));
				y = LerpClamp<float>(ey, -100.0f, EaseOutCubic(out_ratio));
				break;
			}
			case AOUT_TO_RIGHTUP_EXPO: {
				x = LerpClamp<float>(ex, uix, EaseInExpo(out_ratio));
				y = LerpClamp<float>(ey, -100.0f, EaseInExpo(out_ratio));
				break;
			}
			case AOUT_ROTATION: {
				rot = LerpClamp<float>(e_rot, e_rot + 7200.0f, EaseInExpo(out_ratio));
				fs = LerpClamp<float>(e_fs, e_fs * 0.02f, out_ratio);
				break;
			}
			default:
				break;
			}
			if (fequ(rot, 0.0f))
				setfont(fs, 0, fontnames[fontid], imgBuffer);
			else
				setfont(fs, 0, fontnames[fontid], rot, rot, 0, 0, 0, 0, imgBuffer);
			setcolor(color, imgBuffer);
			outtextxy(x, y, text.c_str(), imgBuffer);
		}
		else  //�г����� 
		{
			clock_t motion_delay = json.HaveKey("motion_delay") ? json.GetLong("motion_delay") : 0L;
			clock_t motion_time = json.HaveKey("motion_time") ? json.GetLong("motion_time") : life - in_time - out_time - motion_delay;

			double _ratio = (clock() - start - in_time - motion_delay) / double(motion_time);
			if (clock() - start - in_time - motion_delay < 0L)
				_ratio = 0.0f;

			ChangeFunc chgf_id = json.HaveKey("change_func") ? ParseChangeFunctionID(json.GetString("change_func")) : CHGF_LERP;
			auto change_func = GetChangeFunction(chgf_id);
			x = Lerp<float>(sx, ex, change_func(_ratio));
			y = Lerp<float>(sy, ey, change_func(_ratio));
			if (!fequ(s_rot, e_rot))
				rot = Lerp<float>(s_rot, e_rot, change_func(_ratio));
			if(s_fs != e_fs)
				fs = Lerp<float>(s_fs, e_fs, change_func(_ratio));
			if (s_color != e_color)
				color = StepColor(s_color, e_color, change_func(_ratio));
			else
				color = s_color;

			if (fequ(rot, 0.0f))
				setfont(fs, 0, fontnames[fontid], imgBuffer);
			else
				setfont(fs, 0, fontnames[fontid], rot, rot, 0, 0, 0, 0, imgBuffer);
			setcolor(color, imgBuffer);
			outtextxy(x, y, text.c_str(), imgBuffer);
		}
		XCPT_R
	}
	inline bool IsActive() const
	{
		return (clock() - start <= life);
	}
};

class TextPerformer {
public:
	TextPerformer(){}
	virtual ~TextPerformer()
	{
		m_texts.clear();
	}

	void Perform(PIMAGE imgBuffer)
	{
		for (auto& ele : m_texts)
			ele.Draw(imgBuffer);
	}

	void AddText(TextElement&& tele)
	{
		XCPT_L
		//DebugLogFormat("TextPerformer::AddText: �ı�=%s JSON=%s", tele.text.c_str(), tele.json.ToString().c_str());
		m_texts.push_back(tele);
		m_texts.at(m_texts.size() - 1).Start();
		XCPT_R
	}
	void AddText(float _sx, float _sy, clock_t life_ms, AnimaIn ain, const string& _text,
		color_t scolor, int sfs, const string& fontname,
		const JSON& _json = JSON())
	{
		XCPT_L
		DebugLogFormat("TextPerformer::AddText: �ı�=%s JSON=%s", _text.c_str(), _json.ToString().c_str());
		m_texts.emplace_back(_sx, _sy, life_ms, ain, _text, scolor, sfs, fontname, _json);
		m_texts.at(m_texts.size() - 1).Start();
		XCPT_R
	}
	void CheckTextLives()
	{
		for (size_t i = 0; i < m_texts.size(); ++i)
		{
			if (!m_texts.at(i).IsActive())
			{
				auto iter = m_texts.begin();
				int j = 0;
				while (iter != m_texts.end() && j != i)
				{
					iter++;
					j++;
				}
				iter = m_texts.erase(iter);
			}
		}
	}

	void Clear()
	{
		m_texts.clear();
	}

private:
	vector<TextElement> m_texts;

}textPfmr;