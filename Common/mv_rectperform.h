#pragma once

////////////////////////////////////////////////
//         MV C++ Performer 专属头文件         //
//          by Wormwaker, 禁止盗用             //
////////////////////////////////////////////////

using RectElementType = USHORT;
#define RTET_IMG				0	//预加载图像
#define RTET_BAR				1	//无边框矩形
#define RTET_RECT_OUTLINE		2	//仅边框
#define RTET_RECT				3	//带边框巨响

RectElementType ParseRectElementType(const string& s)
{
	if (sequ(s, "image") || sequ(s, "img"))
		return RTET_IMG;
	if (sequ(s, "bar"))
		return RTET_BAR;
	if (sequ(s, "rect_outline"))
		return RTET_RECT_OUTLINE;
	if (sequ(s, "rect"))
		return RTET_RECT;
	ErrorLogTip("无效的矩形元素类型名称：\"" + s + "\"", "ParseRectElementType");
	return RTET_BAR;
}

class RectElement : public PerformElement
{
public:

	RectElement() = default;
	RectElement(float _sx, float _sy, clock_t life_ms, AnimaIn ain, 
		const JSON& _json = JSON())
	{
		sx = _sx;
		sy = _sy;
		a_in = ain;
		life = life_ms;
		json = _json;
		BaseScaleHandling();
	}
	~RectElement() { json.Clear(); }

	void Draw(PIMAGE imgBuffer = nullptr) override
	{
		XCPT_L
#include "mv_z_ele_draw_common_head.h"
		float rot_xc_ratio = json.HaveKey("rot_xc_ratio") ? ParseNumber(json.GetValueRaw("rot_xc_ratio")) : 0.0f;
		float rot_yc_ratio = json.HaveKey("rot_yc_ratio") ? ParseNumber(json.GetValueRaw("rot_yc_ratio")) : 0.0f;

		float s_zoom = json.HaveKey("s_zoom") ? ParseNumber(json.GetValueRaw("s_zoom")) : 1.0f;
		float e_zoom = json.HaveKey("e_zoom") ? ParseNumber(json.GetValueRaw("e_zoom")) : s_zoom;
		float zoom{ s_zoom };
		short s_w = json.HaveKey("s_w") ? (short)ParseNumber(json.GetValueRaw("s_w")) : 0;
		short s_h = json.HaveKey("s_h") ? (short)ParseNumber(json.GetValueRaw("s_h")) : 0;
		short e_w = json.HaveKey("e_w") ? (short)ParseNumber(json.GetValueRaw("e_w")) : s_w;
		short e_h = json.HaveKey("e_h") ? (short)ParseNumber(json.GetValueRaw("e_h")) : s_h;
		if (s_w != 0 || s_h != 0)	s_zoom = 1.0f;
		if (e_w != 0 || e_h != 0)	e_zoom = 1.0f;
		short w{ s_w }, h{ s_h };

		color_t s_fillcolor = json.HaveKey("s_fillcolor") ? ParseColor(json.GetValueRaw("s_fillcolor")) : WHITE;
		color_t e_fillcolor = json.HaveKey("e_fillcolor") ? ParseColor(json.GetValueRaw("e_fillcolor")) : WHITE;
		color_t s_color = json.HaveKey("s_color") ? ParseColor(json.GetValueRaw("s_color")) : WHITE;
		color_t e_color = json.HaveKey("e_color") ? ParseColor(json.GetValueRaw("e_color")) : WHITE;
		color_t fillcolor{ s_fillcolor }, color{ s_color };
		short s_alpha = json.HaveKey("s_alpha") ? (short)ParseNumber(json.GetValueRaw("s_alpha")) : 255;
		short e_alpha = json.HaveKey("e_alpha") ? (short)ParseNumber(json.GetValueRaw("e_alpha")) : s_alpha;
		short alpha{ s_alpha };

		float csx = 0.0f, csy = 0.0f, cex = 0.0f, cey = 0.0f;
		if (!json.HaveKey("csx"))	//起始圆心X坐标
		{
			csx =
				sx + (e_w / 2.0f)
				/
				cos(DegToRad(s_rot * 10.0f));

			csy =
				sy + sqrt(e_w*e_w / 4.0f + e_h * e_h / 4.0f)
				*
				sin(DegToRad(s_rot * 10.0f) - atan2f(e_h, e_w));
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
			cex =
				ex + (e_w / 2.0f)
				/
				cos(DegToRad(e_rot * 10.0f));

			cey =
				ey + sqrt(e_w*e_w / 4.0f + e_h * e_h / 4.0f)
				*
				sin(DegToRad(e_rot * 10.0f) - atan2f(e_h, e_w));
			json.AddItem("cex", str(cex) + "f");
			json.AddItem("cey", str(cey) + "f");
		}
		else {
			cex = json.GetFloat("cex");
			cey = json.GetFloat("cey");
		}
		
		if (in_time > 0L && clock() - start < in_time)
		{	//入场
			double in_ratio = (clock() - start) / double(in_time);
			rot = s_rot;

			switch (a_in)
			{
			case AIN_FADEIN: {
				alpha = Lerp<float>(0.0f, s_alpha, in_ratio);
				break;
			}
			case AIN_SHRINK: {
				color = StepColor(bgMgr.GetBackColor(), s_color, in_ratio);
				alpha = Lerp<int>(0, s_alpha, in_ratio);
				w = Lerp<int>(s_w*s_zoom * 8, s_w*s_zoom, EaseOutCubic(in_ratio));
				h = Lerp<int>(s_h*s_zoom * 8, s_h*s_zoom, EaseOutCubic(in_ratio));
				if (!fequ(s_zoom, 0.0f))
					zoom = Lerp<float>(s_zoom*8, s_zoom, EaseOutCubic(in_ratio));
				x = csx
					- (w / 2.0)
					/
					cos(DegToRad(rot * 10.0f));
				y = csy
					- sqrt(pow(w, 2) / 4.0f +
						pow(h, 2) / 4.0f)
					*
					sin(DegToRad(rot * 10.0f) - atan2f(h, w));
				break;
			}
			case AIN_ENLARGE: {
				color = StepColor(bgMgr.GetBackColor(), s_color, in_ratio);
				alpha = Lerp<float>(0.0f, s_alpha, in_ratio);
				w = Lerp<int>(s_w*s_zoom * 0.1, s_w*s_zoom, EaseOutCubic(in_ratio));
				h = Lerp<int>(s_h*s_zoom * 0.1, s_h*s_zoom, EaseOutCubic(in_ratio));
				if (!fequ(s_zoom, 0.0f))
					zoom = Lerp<float>(s_zoom*0.1, s_zoom, EaseOutCubic(in_ratio));
				x = csx
					- (w / 2.0)
					/
					cos(DegToRad(rot * 10.0f));
				y = csy
					- sqrt(pow(w, 2) / 4.0f +
						pow(h, 2) / 4.0f)
					*
					sin(DegToRad(rot * 10.0f) - atan2f(h, w));
				break;
			}
#include "mv_z_ain_common_cases.h"
			}
		}
		else if (out_time >= 0L && clock() - start >= life - out_time)
		{	//出场
			zoom = e_zoom;
			alpha = e_alpha;
			color = e_color, fillcolor = e_fillcolor;
			double out_ratio = (clock() - start - (life - out_time)) / double(out_time);
			x = ex, y = ey;
			rot = e_rot;

			switch (a_out)
			{
			case AOUT_FADEOUT: {
				alpha = Lerp<float>(e_alpha, 0.0f, out_ratio);
				break;
			}
			case AOUT_SHRINK: {
				color = StepColor(e_color, bgMgr.GetBackColor(), out_ratio);
				alpha = Lerp<int>(e_alpha, 0, out_ratio);
				w = Lerp<int>(e_w*e_zoom, e_w*e_zoom * 0.1, EaseOutCubic(out_ratio));
				h = Lerp<int>(e_h*e_zoom, e_h*e_zoom * 0.1, EaseOutCubic(out_ratio));
				if (!fequ(e_zoom, 0.0f))
					zoom = Lerp<float>(e_zoom, e_zoom * 0.1, EaseOutCubic(out_ratio));
				x = cex
					- (w / 2.0)
					/
					cos(DegToRad(rot * 10.0f));
				y = cey
					- sqrt(pow(w, 2) / 4.0f +
						pow(h, 2) / 4.0f)
					*
					sin(DegToRad(rot * 10.0f) - atan2f(h, w));
				break;
			}
			case AOUT_ENLARGE: {
				color = StepColor(e_color, bgMgr.GetBackColor(), out_ratio);
				alpha = Lerp<int>(e_alpha, 0, out_ratio);
				w = Lerp<int>(e_w*e_zoom, e_w*e_zoom * 8, EaseOutCubic(out_ratio));
				h = Lerp<int>(e_h*e_zoom, e_h*e_zoom * 8, EaseOutCubic(out_ratio));
				if(!fequ(e_zoom, 0.0f))
					zoom = Lerp<float>(e_zoom, e_zoom * 8, EaseOutCubic(out_ratio));
				x = cex
					- (w / 2.0)
					/
					cos(DegToRad(rot * 10.0f));
				y = cey
					- sqrt(pow(w, 2) / 4.0f +
						pow(h, 2) / 4.0f)
					*
					sin(DegToRad(rot * 10.0f) - atan2f(h, w));
				break;
			}
#include "mv_z_aout_common_cases.h"
			}
		}
		else {	 //中场动画 
#include "mv_z_amid_common.h"	//片段插入，不要当成完整的头文件
			w = Lerp<short>(s_w, e_w, change_func(_ratio));
			h = Lerp<short>(s_h, e_h, change_func(_ratio));
			alpha = Lerp<short>(s_alpha, e_alpha, change_func(_ratio));
			zoom = Lerp<float>(s_zoom, e_zoom, change_func(_ratio));
		}

		DrawRect(imgBuffer, x, y, alpha, rot, rot_xc_ratio, rot_yc_ratio, w, h, zoom, fillcolor, color);

		XCPT_R
	}
	void DrawRect(PIMAGE imgBuffer, float x, float y, 
		          short alpha, float rot, float rot_xc_ratio, float rot_yc_ratio, 
		          short w, short h, float zoom,
		          color_t fillcolor = WHITE, color_t color = WHITE) const
	{
		/*_DrawRectArguments(imgBuffer, x, y,
			alpha, rot, rot_xc_ratio, rot_yc_ratio,
			 w, h, zoom);*/
		PIMAGE pimg = nullptr;
		bool needel = true;
		RectElementType type = GetType();
		if (type == RTET_IMG)
		{	//图像
			if (!json.HaveKey("image"))
			{
				ErrorLogTip("错误：没有指定图片ID", "RectElement::DrawRect");
				return;
			}
			string name{ json.GetString("image") };
			PIMAGE pimg0 = imgMgr.GetImage(name);
			if (pimg0 == nullptr)
			{
				ErrorLogTip("无效图片：" + name, "RectElement::DrawRect");
				return;
			}
			if (w == 0)
			{
				w = getwidth(pimg0);
				w *= zoom;
			}
			if (h == 0)
			{
				h = getheight(pimg0);
				h *= zoom;
			}
			if (w == 0 || h == 0)
			{
				ErrorLogTip("宽或高为0", "RectElement::DrawRect");
				return;
			}
			if (!fequ(zoom, 1.0f) || getwidth(pimg0) != w || getheight(pimg0) != h)
			{
				pimg = newimage();
				getimage(pimg, pimg0, 0, 0, getwidth(pimg0), getheight(pimg0));
				_resize(pimg, w, h);
			}
			else {
				pimg = pimg0;
				needel = false;
			}
			//DebugLogFormat("w=%d,h=%d | pimg0_w=%d h=%d", w, h, getwidth(pimg0), getheight(pimg0));
		}
		else if (type == RTET_BAR || type == RTET_RECT)
		{	//矩形块
			pimg = newimage(w*zoom, h*zoom);
			setfillcolor(fillcolor, pimg);
			bar(X_OFFSET(0), Y_OFFSET(0), X_OFFSET(w*zoom), Y_OFFSET(h*zoom), pimg);
		}
		if (type == RTET_RECT_OUTLINE || type == RTET_RECT
			|| type == RTET_IMG && json.HaveKey("line_w"))
		{	//矩形轮廓 （图像也可以指定轮廓）
			pimg = newimage(w*zoom, h*zoom);
			int lnw = json.HaveKey("line_w") ? ParseNumber(json.GetValueRaw("line_w")) : 1;
			setcolor(color, pimg);
			setlinewidth(lnw, pimg);
			rectangle(X_OFFSET(0), Y_OFFSET(0), X_OFFSET(w*zoom), Y_OFFSET(h*zoom), pimg);
		}
		//输出临时图像至缓冲区
		putimage_rotate(imgBuffer, pimg, X_OFFSET(x), Y_OFFSET(y), rot_xc_ratio, rot_yc_ratio, DegToRad(rot / 10.0f), 1, 
			//-1,
			alpha,
			/*(short)127,*/
			1);

		if(needel)
			delimage(pimg);	//删除临时图像
	}
	void _DrawRectArguments(PIMAGE imgBuffer, float x, float y,
		short alpha, float rot, float rot_xc_ratio, float rot_yc_ratio,
		short w, short h, float zoom) const
	{
		setfont(30, 0, "Consolas", imgBuffer);
		setcolor(RainbowColor(), imgBuffer);
		setbkmode(OPAQUE, imgBuffer);
		outtextrect(X_OFFSET(0), Y_OFFSET(0), uix, uiy, sprintf2(
			"x=%.0f y=%.0f \nalpha=%hd rot=%.0f rxcr=%.2f rycr=%.2f \nw=%d h=%d zoom=%.2f",
			x,y,alpha,rot,rot_xc_ratio,rot_yc_ratio,w,h,zoom
		).c_str(), imgBuffer);
		setbkmode(TRANSPARENT, imgBuffer);
	}
	RectElementType GetType() const
	{
		if (!json.HaveKey("type"))
			return RTET_BAR;
		return ParseRectElementType(json.GetString("type"));
	}
};