#pragma once
////////////////////////////////////////////////
//         MV C++ Performer 专属头文件         //
//          by Wormwaker, 禁止盗用             //
////////////////////////////////////////////////

using EFF_ID = USHORT;

#define EFF_NONE		0
#define EFF_BLUR		1		//模糊
#define EFF_SPECL       2		//毛玻璃
#define EFF_COLOR		3		//颜色淡入淡出
#define EFF_GLOW		4		//发光
#define EFF_DARK		5		//变暗
#define EFF_INVERT		6		//反色
#define EFF_SHARPEN		7		//锐化
#define EFF_DRAG		8		//曳尾式模糊
#define EFF_SHAKE		9		//镜头抖动

#define EFF_SHAKE_AMP 25
#define EFF_SHAKE_OMEGA 0.05
#define EFF_SHAKE_PHASE (PI/2.0)
#define EFF_SHAKE_TAU 150.0

EFF_ID ParseEffectID(const string& s)	//无引号
{
	if (sequ(s, "none"))
		return EFF_NONE;
	if (sequ(s, "blur"))
		return EFF_BLUR;
	if (sequ(s, "specl"))
		return EFF_SPECL;
	if (sequ(s, "color"))
		return EFF_COLOR;
	if (sequ(s, "glow"))
		return EFF_GLOW;
	if (sequ(s, "dark"))
		return EFF_DARK;
	if (sequ(s, "sharpen"))
		return EFF_SHARPEN;
	if (sequ(s, "invert"))
		return EFF_INVERT;
	if (sequ(s, "drag"))
		return EFF_DRAG;
	if (sequ(s, "shake"))
		return EFF_SHAKE;
	ErrorLogTip("无效的特效名称：\"" + s + "\"", "ParseEffectID");
	return EFF_NONE;
}

map<color_t, PIMAGE> pureColorImages;	//纯色图片
#define EFFIO_CLASSIC_PROPORTION 0.2

class Effect					//舞台效果
{
public:
	friend class Camera;
	friend class ElementPerformer;

	Effect(){}
	Effect(EFF_ID _id) : id(_id) {}
	inline EFF_ID GetID(void) const
	{
		return id;
	}
	inline bool Empty(void) const
	{
		return id == EFF_NONE;
	}
	inline bool IsActive(void) const
	{
		return !Empty() && duration > 0L && (clock() - start <= duration);
	}
	inline void SetClassic(EFF_ID _id, clock_t _duration, const JSON& _json = JSON())
	{
		Set(_id, _duration, _duration * EFFIO_CLASSIC_PROPORTION, _duration * EFFIO_CLASSIC_PROPORTION, _json);
	}
	void Set(EFF_ID _id, clock_t _duration, clock_t _inTime = 0L, clock_t _outTime = 0L, const JSON& _json = JSON())
	{
		id = _id;
		if (id == EFF_NONE)
		{
			Clear();
			return;
		}
		duration = _duration;
		in_time = _inTime;
		out_time = _outTime;
		start = clock();
	}
	inline void Clear()
	{
		id = EFF_NONE;
		duration = in_time = out_time = 0L;
	}
	PIMAGE AttainPureColorImage(color_t color)
	{
		for (const auto& pr : pureColorImages)
		{
			if (pr.first == color)
				return pr.second;
		}
		PIMAGE pimg = newimage(getwidth(imgBuffer), getheight(imgBuffer));
		memset(getbuffer(pimg), color, sizeof(color_t) * getwidth(pimg) * getheight(pimg));
		pureColorImages.insert(make_pair(color, pimg));
		return pimg;
	}
	void Paint(PIMAGE img)
	{
		if (!IsActive() || id == EFF_SHAKE)
			return;
		color_t _color = json.HaveKey("color") ? json.GetColor("color") : BLACK;
		double strength = json.HaveKey("strength") ? ParseNumber(json.GetValueRaw("strength")) : 1.0;
		double _ratio = 0.0;

		if (clock() - start < in_time)
			_ratio = Lerp(0.0, strength, (clock() - start) / double(in_time));
		else if (clock() - start - (duration - out_time) >= 0)
			_ratio = Lerp(strength, 0.0, (clock() - start - (duration - out_time)) / double(out_time));
		else
			_ratio = strength;
		switch (id)
		{
		case EFF_BLUR: {
			imagefilter_blurring(img, 0xA0 * _ratio, 0xFF, 0, 0, 0, 0);
			//GaussianBlurA(img, _ratio);
			break;
		}
		case EFF_DRAG: {
			//imagefilter_blurring(img, 0x60 * _ratio, 0xff, 0, 0, 0, 0);
			imagefilter_blurring(img, 0xA0 * _ratio, 0xff, 0, 0, 0, 0);
			//GaussianBlurA(img, _ratio);
			break;
		}
		case EFF_COLOR: {
			putimage_alphablend(img, AttainPureColorImage(_color), 0, 0, 255 * _ratio);
			break;
		}
		case EFF_SPECL: {
			img = Specl(img, _ratio);
			break;
		}
		case EFF_GLOW: {
			GlowA(img, _ratio);
			break;
		}
		case EFF_DARK: {
			imagefilter_blurring(img, 0, Clamp<int>(0xFF * (1.0 - _ratio), 0x01, 0xFF));
			break;
		}
		case EFF_SHARPEN: {
			SharpenA(img, _ratio);
			break;
		}
		case EFF_INVERT: {
			InvertA(img, _ratio);
			break;
		}
		}
	}

private:
	EFF_ID id = EFF_NONE;
	clock_t start = 0L;
	clock_t duration = 0L;
	clock_t in_time = 0L;
	clock_t out_time = 0L;
	JSON json;

};


long thr_paintfx_cnt = 0L;
void PaintEffectsProc(vector<Effect>& fx, PIMAGE pimg)
{
	thr_paintfx_cnt++;
	for (auto& eff : fx)
		eff.Paint(pimg);
	thr_paintfx_cnt--;
}

class Camera		//摄像机
{
public:
	friend class Effect;
	friend class ElementPerformer;

	vector<Effect> fx;
	static int LeftSpace;
	static int TopSpace;
	static int RightSpace;
	static int BottomSpace;

	Camera()
	{
		s_cx = s_cy = 0;
	}
	~Camera()
	{
		if (!pureColorImages.empty())
			DeletePureColorImages();
	}
	inline void MoveTo(int _cx, int _cy)
	{
		s_cx = _cx, s_cy = _cy;
	}
	inline void MoveToCenter(int left, int top, int right, int bottom)
	{
		s_cx = (left + right) / 2;
		s_cy = (top + bottom) / 2;
	}
	inline void MoveToWindowCenter()
	{
		MoveToCenter(0, 0, uix, uiy);
	}
	inline void NormalZoom()
	{
		s_zoom = 1.0f;
	}
	inline void SetZoom(float newScale)
	{
		s_zoom = newScale;
	}
	inline float GetZoom(void) const
	{
		return s_zoom;
	}
	void Clear()
	{	//还原
		MoveToWindowCenter();
		e_cx = s_cx;
		e_cy = s_cy;
		s_rot = e_rot = 0.0f;
		s_alpha = e_alpha = 255;
		s_zoom = e_zoom = 1.0f;
		motion_duration = 0L;
	}
	void SetData(const string& key, const string& value)
	{
		if (sequ(key, "s_cx") || sequ(key, "cx") || sequ(key,"sx"))
			s_cx = ParseNumber(value);
		else if (sequ(key, "s_cy") || sequ(key, "cy") || sequ(key,"sy"))
			s_cy = ParseNumber(value);
		else if (sequ(key, "e_cx") || sequ(key, "ex"))
		{
			//<!> s_cx会被替代
			s_cx = actual_x;
			e_cx = ParseNumber(value);
		}
		else if (sequ(key, "e_cy") || sequ(key, "ey"))
		{
			//<!> s_cy会被替代
			s_cy = actual_y;
			e_cy = ParseNumber(value);
		}
		else if (sequ(key, "s_rot") || sequ(key, "rot"))
			s_rot = ParseNumber(value);
		else if (sequ(key, "e_rot"))
		{
			//<!> s_rot会被替代
			s_rot = actual_rot;
			e_rot = ParseNumber(value);
		}
		else if (sequ(key, "s_alpha") || sequ(key, "alpha"))
			s_alpha = ParseNumber(value);
		else if (sequ(key, "e_alpha"))
		{
			s_alpha = actual_alpha;
			e_alpha = ParseNumber(value);
		}
		else if (sequ(key, "s_zoom") || sequ(key, "zoom"))
			s_zoom = ParseNumber(value);
		else if (sequ(key, "e_zoom"))
		{
			s_zoom = actual_zoom;
			e_zoom = ParseNumber(value);
		}
		else if (sequ(key, "duration") || sequ(key, "motion_duration"))
			motion_duration = ParseNumber(value);
		else if (sequ(key, "change_func"))
			change_func = GetChangeFunction(ParseChangeFunctionID(unquote(value)));
		else {
			ErrorLogTip("无效的相机参数：" + key, "Camera::SetData");
		}
	}
	void SetData(JSON&& json)
	{
		size_t cnt = json.ItemCount();
		for (size_t i = 0; i < cnt; ++i)
			SetData(json.GetNthItem(i).first, json.GetNthItem(i).second);
	}
	void SetData(const JSON& json)
	{
		size_t cnt = json.ItemCount();
		for (size_t i = 0; i < cnt; ++i)
			SetData(json.GetNthItem(i).first, json.GetNthItem(i).second);
	}
#define CAM_ANIMA_RATIO Clamp((clock() - motion_start) / double(motion_duration), 0.0, 1.0)
	void DrawScene(PIMAGE imgBuffer)
	{
		XCPT_L
		PIMAGE img = imgBuffer;
		actual_x = GetNowCenterX();
		actual_y = GetNowCenterY();
		actual_zoom = GetNowZoom();

		if (!fequ(actual_zoom, 1.0f))
		{
			img = newimage();
			getimage(img, imgBuffer, 0, 0, getwidth(imgBuffer), getheight(imgBuffer));
			_resize(img, getwidth(imgBuffer) * actual_zoom, getheight(imgBuffer) * actual_zoom);
		}
		actual_rot = GetNowRotation();
		actual_alpha = GetNowAlpha();

		int x_offset{ 0 }, y_offset{ 0 };
		if (HaveEffect(EFF_SHAKE))
		{
			Effect* peff = nullptr;
			for (auto& eff : fx)
				if (eff.id == EFF_SHAKE)
					peff = &eff;
			if (nullptr != peff)
			{
				double _x = (clock() - peff->start);
				double _amp = peff->json.HaveKey("amp") ? ParseNumber(peff->json.GetValueRaw("amp")) : EFF_SHAKE_AMP;
				double _tau = peff->json.HaveKey("tau") ? ParseNumber(peff->json.GetValueRaw("tau")) : EFF_SHAKE_TAU;
				double _omega = peff->json.HaveKey("omega") ? ParseNumber(peff->json.GetValueRaw("omega")) : EFF_SHAKE_OMEGA;
				double _phase = peff->json.HaveKey("phase") ? ParseNumber(peff->json.GetValueRaw("phase")) : EFF_SHAKE_PHASE;
				x_offset = _amp * exp(-_x / _tau) * sin(_omega * _x);
				y_offset = _amp * exp(-_x / _tau) * sin(_phase + _omega * _x);
			}
		}
		//putimage(NULL, s_cx - w * s_zoom / 2.0f, s_cy - h * s_zoom / 2.0f, img, SRCCOPY);
		putimage_rotate(NULL, img,
			//(actual_x = GetNowCenterX()) - uix/2 + w * actual_zoom / 2.0f,
			//(actual_y = GetNowCenterY()) - uiy/2 + h * actual_zoom / 2.0f,

			x_offset + (w * actual_zoom / 2 - ((actual_x) - w / actual_zoom / 2.0f) * actual_zoom),
			y_offset + (h * actual_zoom / 2 - ((actual_y) - h / actual_zoom / 2.0f) * actual_zoom),

			0.5f, 0.5f, DegToRad(-actual_rot / 10.0f), 1, actual_alpha, 1);

		if (!fequ(actual_zoom, 1.0f))
			delimage(img);

		PaintEffects(nullptr);

		/*setfont(40, 0, "Consolas");
		setcolor(InvertedColor(bgMgr.GetBackColor()));
		xyprintf(10, 10, "ZOOM=%.3f [%.3f -> %.3f]", actual_zoom, s_zoom, e_zoom);
		xyprintf(10, 50, "DURATION=%ld", motion_duration);
		xyprintf(10, 90, "MOTION_START=%ld", motion_start);
		xyprintf(10, 130, "CAM_ANIMA_RATIO=%.2f", CAM_ANIMA_RATIO);*/

		/*setfont(20, 0, "Consolas");
		setcolor(InvertedColor(bgMgr.GetBackColor()));
		xyprintf(uix - 50, 3, "%.0f", getfps());*/

		XCPT_R
	}

	inline bool InAnimation(void) const
	{
		return motion_duration > 0L;
		//return (
			//motion_duration > 0L &&
			  //clock() - motion_start <= motion_duration);
	}
	inline void MotionStart()
	{
		motion_start = clock();
	}
	float GetNowZoom() const
	{
		if (!InAnimation())	return s_zoom;
		return Lerp<float>(s_zoom, e_zoom, change_func(CAM_ANIMA_RATIO));
	}
	float GetNowRotation() const
	{
		if (!InAnimation())	return s_rot;
		return Lerp<float>(s_rot, e_rot, change_func(CAM_ANIMA_RATIO));
	}
	short GetNowAlpha() const
	{
		if (!InAnimation())	return s_alpha;
		return Lerp<short>(s_alpha, e_alpha, change_func(CAM_ANIMA_RATIO));
	}
	int GetNowCenterX() const
	{
		if (!InAnimation())	return s_cx;
		return Lerp<int>(s_cx, e_cx, change_func(CAM_ANIMA_RATIO));
	}
	int GetNowCenterY() const
	{
		if (!InAnimation())	return s_cy;
		return Lerp<int>(s_cy, e_cy, change_func(CAM_ANIMA_RATIO));
	}
	void MakeRelativeData(float& x, float& y, short& fs, float& rot)
	{	
		double theta = atan2f(h * actual_zoom / 2.0f - y, w * actual_zoom / 2.0f - x) - DegToRad(actual_rot / 10.0f);
		double dist = sqrtf(pow(w * actual_zoom / 2.0f - x, 2) + pow(h * actual_zoom / 2.0f - y, 2));
		x = actual_x - dist * cos(theta);
		y = actual_y - dist * sin(theta);
		fs = fs / actual_zoom;
		//DebugLogFormat("fs = %hd theta=%.1f° dist=%.1f delta_x = %.1f delta_y = %.1f x=%.1f y=%.1f (cam_ax=%d cam_ay=%d)", fs, RadToDeg(theta), dist, cos(theta) * dist, sin(theta) * dist, x, y, actual_x, actual_y);
		//x += cos(DegToRad((rot + actual_rot) / 10.0f)) * (x - actual_x) * actual_zoom;
		//y += sin(DegToRad((rot + actual_rot) / 10.0f)) * (y - actual_y) * actual_zoom;
		rot += actual_rot;
	}

	void DeletePureColorImages()
	{
		for (auto& pr : pureColorImages)
		{
			if(nullptr != pr.second)
				delimage(pr.second);
		}
		pureColorImages.clear();
	}
	void CheckEffectsLives(void)
	{
		for (size_t i = 0; i < fx.size(); ++i)
		{
			if (!fx.at(i).IsActive())
			{
				auto iter = fx.begin();
				int j = 0;
				while (iter != fx.end() && j != i)
				{
					iter++;
					j++;
				}
				iter = fx.erase(iter);
			}
		}
	}
	inline bool HaveEffect(void) const
	{
		return !fx.empty();
	}
	inline bool HaveEffect(EFF_ID effid) const
	{
		for (const auto& eff : fx)
			if (eff.GetID() == effid)
				return true;
		return false;
	}
	inline void AddEffect(const Effect& eff)
	{
		DebugLogFormat("AddEffect id=%d", eff.id);
		fx.push_back(eff);
	}
	inline void AddEffect(Effect&& eff)
	{
		fx.push_back(eff);
	}
	void PaintEffects(PIMAGE pimg)
	{
		XCPT_L
		PaintEffectsProc(fx, pimg);
		//if (thr_paintfx_cnt > 3)	//避免卡死
		//	return;
		//thread pe(PaintEffectsProc, ref(fx), pimg);
		//pe.detach();
		XCPT_R
	}
private:
	//此刻的真实数据
	int actual_x = 1;
	int actual_y = 1;
	float actual_rot = 0.0f;
	short actual_alpha = 255;
	float actual_zoom = 1.0f;
protected:
	//中心点坐标
	int s_cx = 0;
	int s_cy = 0;
	//旋转角度
	float s_rot = 0.0f;
	//不透明度
	short s_alpha = 255;
	//相机缩放比例
	float s_zoom = 1.0f;
	//尺寸
	const int& w = uix;
	const int& h = uiy;

	//相机动画的最终状态
	int e_cx = 0;
	int e_cy = 0;
	float e_rot = 0.0f;
	short e_alpha = 255;
	float e_zoom = 1.0f;
	clock_t motion_start = 0L;
	clock_t motion_duration = 0L;
	double(__stdcall *change_func)(double) = EaseInOutSine;

}camera;

int Camera::LeftSpace = 0;
int Camera::RightSpace = 0;
int Camera::TopSpace = 0;
int Camera::BottomSpace = 0;

#define X_OFFSET(x)		((x) + Camera::LeftSpace)
#define Y_OFFSET(y)		((y) + Camera::TopSpace)
#define IMGBUFFER_WIDTH (uix + Camera::LeftSpace + Camera::RightSpace)
#define IMGBUFFER_HEIGHT (uiy + Camera::TopSpace + Camera::BottomSpace)