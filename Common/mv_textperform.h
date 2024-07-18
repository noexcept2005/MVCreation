#pragma once
////////////////////////////////////////////////
//         MV C++ Performer 专属头文件         //
//          by Wormwaker, 禁止盗用             //
////////////////////////////////////////////////

class TextElement : public PerformElement			//文本元素
{
public:
	string text = "Text";			//文本
	color_t s_color = WHITE;			//起始颜色
	int s_fs = 70;				//起始字号
	FontNameID fontid = 0;			//字体名称ID

	TextElement() { 
		sx = sy = 100.0f; start = 0L; BaseScaleHandling();
	}
	TextElement(float _sx, float _sy, clock_t life_ms, AnimaIn ain, const string& _text,
		        color_t scolor, int sfs, const string& fontname,
		        const JSON& _json = JSON()) 
		: text(_text), s_color(scolor),
		s_fs(sfs), fontid(GetFontNameID(fontname))
	{
		sx = _sx;
		sy = _sy;
		a_in = ain;
		life = life_ms;
		json = _json;
		BaseScaleHandling();
	}
	~TextElement() { json.Clear(); }
#define TEXT_DEF_IN_TIME		500L
#define TEXT_DEF_OUT_TIME		500L
	void Draw(PIMAGE imgBuffer = nullptr) override
	{
		XCPT_L
		
#include "mv_z_ele_draw_common_head.h"	//片段插入，不要当成完整头文件

		color_t color = s_color;
		color_t e_color = json.HaveKey("e_color") ? json.GetColor("e_color") : s_color;
		short fs = s_fs;
		short e_fs = json.HaveKey("e_fs") ? (short)ParseNumber(json.GetValueRaw("e_fs")) : s_fs;

		float csx=0.0f, csy=0.0f, cex=0.0f, cey=0.0f;
		//if (!fequ(s_rot, 0.0f) || !fequ(e_rot, 0.0f) || AnimaInNeedRotation(a_in) || AnimaOutNeedRotation(a_out))
		//{
			if (!json.HaveKey("csx"))	//起始圆心X坐标
			{
				int text_w = text.length() * s_fs / 2.0f;
				int text_h = s_fs;
				csx = 
					sx + (text_w / 2.0f)
					     /
					     cos(DegToRad(s_rot * 10.0f));

				csy = 
				sy + sqrt(text_w * text_w / 4.0f + text_h * text_h / 4.0f)
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

			if (!json.HaveKey("cex"))	//最终圆心X坐标
			{
				int text_w = text.length() * e_fs / 2.0f;
				int text_h = e_fs;
				cex =	
					ex + (text_w / 2.0f)
					/
					cos(DegToRad(e_rot * 10.0f));

				cey =
					ey + sqrt(text_w * text_w / 4.0f + text_h * text_h / 4.0f)
					*
					sin(DegToRad(e_rot * 10.0f) - atan2f(text_h, text_w));
				/*double angle = DegToRad(e_rot);
				cex = x + (text_w / 2.0) * cos(angle) - (text_h / 2.0) * sin(angle);
				cey = y + (text_w / 2.0) * sin(angle) + (text_h / 2.0) * cos(angle);
				*/
				json.AddItem("cex", str(cex) + "f");
				json.AddItem("cey", str(cey) + "f");
			}
			else {
				cex = json.GetFloat("cex");
				cey = json.GetFloat("cey");
			}
		//}

		if (in_time > 0L && clock() - start < in_time)
		{	//入场
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
					sin(DegToRad(rot * 10.0f) - atan2f(fs, text.length()*fs / 2.0f));

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
					sin(DegToRad(rot * 10.0f) - atan2f(fs, text.length()*fs / 2.0f));

				break;
			}
			
#include "mv_z_ain_common_cases.h"		//片段插入，不要当成完整的头文件

			case AIN_ROTATION: {
				rot = LerpClamp<float>(s_rot - 7200.0f, s_rot, EaseOutCubic(in_ratio));
				fs = LerpClamp<float>(s_fs * 0.02f, s_fs, in_ratio);

				x = csx 
					- (fs * text.length() / 4.0f)
					/
					cos(DegToRad(rot * 10.0f));
				y = csy
					- sqrt(pow(text.length()*fs / 2.0f, 2) / 4.0f+
						pow(fs, 2) / 4.0f)
					*
					sin(DegToRad(rot * 10.0f) - atan2f(fs, text.length()*fs / 2.0f));
					
				break;
			}
			default:
				break;
			}
			if (rel_to_camera)
				camera.MakeRelativeData(x, y, fs, rot);
		//	DebugLogFormat("fs = %d", fs);
			if (fequ(rot, 0.0f))
				setfont(fs, 0, fontnames[fontid], imgBuffer);
			else
				setfont(fs, 0, fontnames[fontid], rot, rot, 0, 0, 0, 0, imgBuffer);
			setcolor(color, imgBuffer);
			outtextxy(X_OFFSET(x), Y_OFFSET(y), text.c_str(), imgBuffer);
		}
		else if (out_time >= 0L && clock() - start >= life - out_time)
		{	//出场
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

				x = cex
					- (fs * text.length() / 4.0f)
					/
					cos(DegToRad(rot * 10.0f));
				y = cey
					- sqrt(pow(text.length()*fs / 2.0f, 2) / 4.0f +
						pow(fs, 2) / 4.0f)
					*
					sin(DegToRad(rot * 10.0f) - atan2f(fs, text.length()*fs / 2.0f));
				break;
			}
			case AOUT_SHRINK: {
				if (e_color != bgMgr.GetBackColor() && e_color != bgMgr.GetBackColor())
					color = StepColor(e_color, bgMgr.GetBackColor(), out_ratio);
				fs = LerpClamp<short>(fs, fs * 0.02, EaseInExpo(out_ratio));

				x = cex
					- (fs * text.length() / 4.0f)
					/
					cos(DegToRad(rot * 10.0f));
				y = cey
					- sqrt(pow(text.length()*fs / 2.0f, 2) / 4.0f +
						pow(fs, 2) / 4.0f)
					*
					sin(DegToRad(rot * 10.0f) - atan2f(fs, text.length()*fs / 2.0f));
				break;
			}
			
#include "mv_z_aout_common_cases.h"	//片段插入，不要当成完整头文件

			case AOUT_ROTATION: {
				rot = LerpClamp<float>(e_rot, e_rot + 7200.0f, EaseInExpo(out_ratio));
				fs = LerpClamp<float>(e_fs, e_fs * 0.02f, out_ratio);

				x = cex
					- (fs * text.length() / 4.0f)
					/
					cos(DegToRad(rot * 10.0f));
				y = cey
					- sqrt(pow(text.length()*fs / 2.0f, 2) / 4.0f +
						pow(fs, 2) / 4.0f)
					*
					sin(DegToRad(rot * 10.0f) - atan2f(fs, text.length()*fs / 2.0f));
				break;
			}
			default:
				break;
			}
			if(rel_to_camera)
				camera.MakeRelativeData(x, y, fs, rot);
			if (fequ(rot, 0.0f))
				setfont(fs, 0, fontnames[fontid], imgBuffer);
			else
				setfont(fs, 0, fontnames[fontid], rot, rot, 0, 0, 0, 0, imgBuffer);
			setcolor(color, imgBuffer);
			outtextxy(X_OFFSET(x), Y_OFFSET(y), text.c_str(), imgBuffer);
		}
		else  //中场动画 
		{
#include "mv_z_amid_common.h"	//片段插入，不要当成完整的头文件
			if(s_fs != e_fs)
				fs = Lerp<float>(s_fs, e_fs, change_func(_ratio));
			if (s_color != e_color)
				color = StepColor(s_color, e_color, change_func(_ratio));
			else
				color = s_color;

			if (rel_to_camera)
				camera.MakeRelativeData(x, y, fs, rot);
			if (fequ(rot, 0.0f))
				setfont(fs, 0, fontnames[fontid], imgBuffer);
			else
				setfont(fs, 0, fontnames[fontid], rot, rot, 0, 0, 0, 0, imgBuffer);
			setcolor(color, imgBuffer);
			outtextxy(X_OFFSET(x), Y_OFFSET(y), text.c_str(), imgBuffer);
		}
		XCPT_R
	}
};
