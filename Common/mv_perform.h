#pragma once
////////////////////////////////////////////////
//         MV C++ Performer 专属头文件         //
//          by Wormwaker, 禁止盗用             //
////////////////////////////////////////////////

using AnimaIn = USHORT;				//入场动画ID
using AnimaOut = USHORT;			//出场动画ID

#define AIN_NONE					0
#define AIN_FADEIN					1
#define AIN_ENLARGE					2
#define AIN_SHRINK					3
#define AIN_FROM_LEFT_CUBIC			4	//从左边进入，减速
#define AIN_FROM_LEFT_EXPO			5	//从左边进入，加速
#define AIN_FROM_RIGHT_CUBIC		6	//从右边进入，减速
#define AIN_FROM_RIGHT_EXPO			7	//从右边进入，加速
#define AIN_FROM_UP_CUBIC			8	//从上边进入，减速
#define AIN_FROM_UP_EXPO			9	//从上边进入，加速
#define AIN_FROM_DOWN_CUBIC			10	//从下边进入，减速
#define AIN_FROM_DOWN_EXPO			11	//从下边进入，加速
#define AIN_FROM_LEFTDOWN_CUBIC		12	//从左下方进入，减速
#define AIN_FROM_LEFTDOWN_EXPO		13	//从左下方进入，加速
#define AIN_FROM_LEFTUP_CUBIC		14	//从左上方进入，减速
#define AIN_FROM_LEFTUP_EXPO		15	//从左上方进入，加速
#define AIN_FROM_RIGHTUP_CUBIC		16	//从右上方进入，减速
#define AIN_FROM_RIGHTUP_EXPO		17	//从右上方进入，加速
#define AIN_FROM_RIGHTDOWN_CUBIC	18	//从右下方进入，减速
#define AIN_FROM_RIGHTDOWN_EXPO		19	//从右下方进入，加速
#define AIN_ROTATION				20	//回旋进入

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

	ErrorLogTip("无效的入场动画名称\"" + s + "\"", "ParseAnimaIn");
	return AIN_NONE;
}

#define AOUT_NONE					0
#define AOUT_FADEOUT				1
#define AOUT_ENLARGE				2
#define AOUT_SHRINK					3
#define AOUT_TO_LEFT_CUBIC			4		//从左边离开，减速
#define AOUT_TO_LEFT_EXPO			5		//从左边离开，加速
#define AOUT_TO_RIGHT_CUBIC			6		//从右边离开，减速
#define AOUT_TO_RIGHT_EXPO			7		//从右边离开，加速
#define AOUT_TO_UP_CUBIC			8		//从上边离开，减速
#define AOUT_TO_UP_EXPO				9		//从上边离开，加速
#define AOUT_TO_DOWN_CUBIC			10		//从下边离开，减速
#define AOUT_TO_DOWN_EXPO			11		//从下边离开，加速
#define AOUT_TO_LEFTDOWN_CUBIC		12		//从左下边离开，减速
#define AOUT_TO_LEFTDOWN_EXPO		13		//从左下边离开，加速
#define AOUT_TO_RIGHTDOWN_CUBIC		14		//从右下边离开，减速
#define AOUT_TO_RIGHTDOWN_EXPO		15		//从右下边离开，加速
#define AOUT_TO_LEFTUP_CUBIC		16		//从左上边离开，减速
#define AOUT_TO_LEFTUP_EXPO			17		//从左上边离开，加速
#define AOUT_TO_RIGHTUP_CUBIC		18		//从右上边离开，减速
#define AOUT_TO_RIGHTUP_EXPO		19		//从右上边离开，加速
#define AOUT_ROTATION				20		//回旋离开

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
	ErrorLogTip("无效的出场动画名称\"" + s + "\"", "ParseAnimaOut");
	return AOUT_NONE;
}

using ChangeFunc = USHORT;			//变化函数ID

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
#define CHGF_EASE_OUT_SINE			10
#define CHGF_EASE_IN_CUBIC			11

double(CJZAPI *pchange_functions[]) (double)
= { SelfFunc, EaseOutCubic, EaseInExpo, EaseInOutSine, EaseInOutBack,
	EaseInOutCubic, EaseInOutElastic, EaseInOutExpo, EaseInOutBounce,
	EaseOutBounce, EaseOutSine, EaseInCubic,
};

decltype(auto) GetChangeFunction(ChangeFunc id)
{
	if (id >= _countof(pchange_functions))
	{
		ErrorLogTip("变化函数ID访问越界！", "GetChangeFunction");
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
	if (sequ(s, "ease_out_sine"))
		return CHGF_EASE_OUT_SINE;
	if (sequ(s, "ease_in_cubic"))
		return CHGF_EASE_IN_CUBIC;
	ErrorLogTip("无效的变化函数名称\"" + s + "\"！", "ParseChangeFunctionID");
	return CHGF_LERP;
}

class PerformElement {				//(一个基类)
public:
	float sx = 100.0f;				//起始X坐标
	float sy = 100.0f;				//起始Y坐标
	AnimaIn a_in = AIN_FADEIN;		//入场效果

	JSON json;						//其他数据
	clock_t life;					//显示的总时间
	clock_t start;					//开始的时间戳

	virtual ~PerformElement(){}
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
	inline bool IsActive() const
	{
		return (clock() - start <= life);
	}
	inline bool IsRelativeToCamera(void) const
	{
		return json.HaveKey("rel_data") && ParseNumber(json.GetValueRaw("rel_data")) != 0;
	}
	virtual void Draw(PIMAGE imgBuffer = nullptr) 	//please override
	{
		setfont(40, 0, "Consolas", imgBuffer);
		setcolor(WaveColor((color_t)GREEN), imgBuffer);
		setbkmode(TRANSPARENT);
		outtextxy(sx, sy, "[PerformElement]", imgBuffer);
	}
};

#include "mv_camera.h"				//相机
//子嗣
#include "mv_textperform.h"
#include "mv_rectperform.h"

//播放器
class ElementPerformer {
public:
	ElementPerformer() {}
	virtual ~ElementPerformer()
	{
		Clear();
	}

	void Perform(PIMAGE imgBuffer
					//, bool pre0_after1
				)
	{
		TextElement* teptr{ nullptr };
		RectElement* reptr{ nullptr };
		for (auto& ele : m_elements)
		{
			if (nullptr != (teptr = dynamic_cast<TextElement*>(ele))
				//&& pre0_after1 == teptr->IsRelativeToCamera()
				)
				teptr->Draw(imgBuffer);
			else if (nullptr != (reptr = dynamic_cast<RectElement*>(ele))
				//&& pre0_after1 == reptr->IsRelativeToCamera()
				)
				reptr->Draw(imgBuffer);
			else //if(pre0_after1 == ele->IsRelativeToCamera())
				ele->Draw(imgBuffer);		//最后保底是基类方法
			//ele->Draw(imgBuffer);
		}
	}

	void AddText(TextElement&& tele)
	{
		XCPT_L
		//DebugLogFormat("ElementPerformer::AddText: 文本=%s JSON=%s", tele.text.c_str(), tele.json.ToString().c_str());
		m_elements.push_back(new TextElement(tele));
		m_elements.at(m_elements.size() - 1)->Start();
		XCPT_R
	}
	void AddText(float _sx, float _sy, clock_t life_ms, AnimaIn ain, const string& _text,
		color_t scolor, int sfs, const string& fontname,
		const JSON& _json = JSON())
	{
		XCPT_L
		DebugLogFormat("ElementPerformer::AddText: 文本=%s JSON=%s", _text.c_str(), _json.ToString().c_str());
		m_elements.push_back(new TextElement(_sx, _sy, life_ms, ain, _text, scolor, sfs, fontname, _json));
		m_elements.at(m_elements.size() - 1)->Start();
		XCPT_R
	}
	void AddRect(const RectElement& rele)
	{
		XCPT_L
		m_elements.push_back(new RectElement(rele));
		m_elements.at(m_elements.size() - 1)->Start();
		DebugLog("JSON = " + m_elements.at(m_elements.size() - 1)->json.ToString());
		XCPT_R
	}
	void AddRect(RectElement&& rele)
	{
		XCPT_L
		m_elements.push_back(new RectElement(rele));
		m_elements.at(m_elements.size() - 1)->Start();
		XCPT_R
	}
	void CheckElementLives()
	{
		for (size_t i = 0; i < m_elements.size(); ++i)
		{
			if (!m_elements.at(i)->IsActive())
			{
				auto iter = m_elements.begin();
				int j = 0;
				while (iter != m_elements.end() && j != i)
				{
					iter++;
					j++;
				}
				iter = m_elements.erase(iter);
			}
		}
	}
	void Clear()
	{
		DebugLog("ElementPerformer: 清除所有元素");
		for (auto& ptr : m_elements)
			delete ptr;
		m_elements.clear();
	}
	void AddDeltaTime(clock_t delta);
	template <typename _T>
	void ClearDerived()		//删除指定派生类型的元素
	{
		for (size_t i = 0; i < m_elements.size(); ++i)
		{
			if (nullptr != dynamic_cast<_T*>(m_elements.at(i)))
			{
				auto iter = m_elements.begin();
				int j = 0;
				while (iter != m_elements.end() && j != i)
				{
					iter++;
					j++;
				}
				delete *iter;
				iter = m_elements.erase(iter);
			}
		}
	}
//#define DEFINE_CLEAR_DERIVED_ELEMENT_METHOD(Object) \
//    void Clear##Object##s()		\
//	{												\
//		ClearDerived<Object##Element*>();				\
//	}
//	DEFINE_CLEAR_DERIVED_ELEMENT_METHOD(Text)
//	DEFINE_CLEAR_DERIVED_ELEMENT_METHOD(Rect)

private:
	vector<PerformElement*> m_elements;

}elePfmr;

class RegionController
{
public:

	bool waiting = false;
	bool region_duration_limit = false;
	clock_t region_duration = 0L;
	clock_t region_start = 0L;

	void SetRegionDuration(clock_t duration_ms)
	{
		region_duration_limit = true;
		region_duration = duration_ms;
		region_start = clock();
		waiting = false;
	}
	inline void DisableRegionDuration()
	{
		region_duration_limit = false;
		waiting = false;
	}
	void WaitForRegionDuration(bool freeze = false)
	{
		if (!region_duration_limit)
		{
			waiting = false;
			return;
		}
		waiting = true;
		if (freeze)
		{
			while (PassedMilliSeconds() <= region_duration)
				delay(50);
			waiting = false;
		}
	}
	inline bool ShouldWait() const
	{
		return region_duration_limit && (PassedMilliSeconds() <= region_duration);
	}
	inline void UpdateShouldWait()
	{
		waiting = ShouldWait();
	}
	inline clock_t PassedMilliSeconds() const
	{
		return (clock() - region_start);
	}
}regCtrl;


void DrawDebug()
{
	setcolor(RED);
	setlinewidth(2);
	line(camera.GetNowCenterX(), 0, camera.GetNowCenterX(), uiy);
	line(0, camera.GetNowCenterY(), uix, camera.GetNowCenterY());
	
	/*float theta = atan2(camera.GetNowZoom() * uiy, camera.GetNowZoom() * uix) - DegToRad(camera.GetNowRotation() / 10.0f);
	float dist = sqrt(pow(camera.GetNowZoom() * uix, 2) + pow(camera.GetNowZoom() * uiy, 2));
	setcolor(MAGENTA);
	line(camera.GetNowCenterX() - dist * cos(theta), 
		 camera.GetNowCenterY() - dist * sin(theta), 
		 camera.GetNowCenterX() + dist * cos(theta),
		 camera.GetNowCenterY() + dist * sin(theta));
	line(camera.GetNowCenterX() - dist * cos(theta),
		camera.GetNowCenterY() - dist * sin(theta),
		camera.GetNowCenterX() + dist * cos(theta),
		camera.GetNowCenterY() + dist * sin(theta));
	line(camera.GetNowCenterX() - dist * cos(theta),
		camera.GetNowCenterY() - dist * sin(theta),
		camera.GetNowCenterX() + dist * cos(theta),
		camera.GetNowCenterY() + dist * sin(theta));
	line(camera.GetNowCenterX() - dist * cos(theta),
		camera.GetNowCenterY() - dist * sin(theta),
		camera.GetNowCenterX() + dist * cos(theta),
		camera.GetNowCenterY() + dist * sin(theta));*/

	setfont(30, 0, "Consolas");
	setcolor(InvertedColor(bgMgr.GetBackColor()));
	xyprintf(10, 10, "FPS: %.0f", getfps());
	//xyprintf(10, 40, "TID: %d", GetCurrentThreadId());
}