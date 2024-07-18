#pragma once
////////////////////////////////////////////////
//         MV C++ Performer 专属头文件         //
//          by Wormwaker, 禁止盗用             //
////////////////////////////////////////////////

#define fequ(f1,f2)	(abs(f1-f2) < 0.001f)

inline float CJZAPI DegToRad(const float deg)
{
	return deg / 180.0f * PI;
}
inline float CJZAPI RadToDeg(const float rad)
{
	return rad / PI * 180.0f;
}
int CJZAPI RandomRange(int Min, int Max, bool rchMin, bool rchMax)
{ //随机数值区间 
	int a;
	a = rand();
	if (rchMin && rchMax)	//[a,b]
		return (a % (Max - Min + 1)) + Min;
	else if (rchMin && !rchMax)		//[a,b)
		return (a % (Max - Min)) + Min;
	else if (!rchMin && rchMax)		//(a,b]
		return (a % (Max - Min)) + Min + 1;
	else							//(a,b)
		return (a % (Max - Min - 1)) + Min + 1;
}
double CJZAPI RandomRangeDouble(double _min, double _max,	//min,max
	bool rchMin = true, bool rchMax = true,	//开/闭 
	UINT uPrec = 2	//精度（位数） 
)
{	//随机小数区间 
	double p_small = pow(10.0f, -int(uPrec));
	int p_big = (int)pow(10, uPrec);
	int l = int(p_big*_min);
	int r = int(p_big*_max);
	int res;
	res = RandomRange(l, r, rchMin, rchMax);
	return (p_small*(double)res);
}
int CJZAPI Randint(int Min, int Max)
{	//闭区间随机值
	return RandomRange(Min, Max, true, true);
}
template <typename _T>
inline _T CJZAPI ClampA(_T& val, _T min = 0, _T max = 2147483647) {	//限定范围
	if (val < min) val = min;
	else if (val > max) val = max;
	return val;
}
template <typename _T>
inline _T CJZAPI Clamp(_T val, _T min = 0, _T max = 2147483647) {	//限定范围
	if (val < min) val = min;
	else if (val > max) val = max;
	return val;
}

double CJZAPI SelfFunc(double _x)
{
	return _x;
}
template <typename _T>
inline double CJZAPI Lerp(_T startValue, _T endValue, double ratio)
{
	return startValue + (endValue - startValue) * ratio;
}
template <typename _T>
inline double CJZAPI LerpClamp(_T startValue, _T endValue, double ratio)
{
	return Clamp<double>(Lerp(startValue, endValue, ratio), min(startValue, endValue), max(endValue, startValue));
}
double CJZAPI EaseInExpo(double _x)
{
	return fequ(_x, 0.0) ? 0 : pow(2, 10 * _x - 10);
}	
double CJZAPI EaseInCubic(double _x)
{
	return _x * _x * _x;
}
double CJZAPI EaseInOutSine(double _x)
{	//retval,_x ∈ [0,1]
	return -(cos(PI * _x) - 1) / 2;
}
double CJZAPI EaseInOutBack(double _x)
{
	const double c1 = 1.70158;
	const double c2 = c1 * 1.525;
	return _x < 0.5
		? (pow(2 * _x, 2) * ((c2 + 1) * 2 * _x - c2)) / 2
		: (pow(2 * _x - 2, 2) * ((c2 + 1) * (_x * 2 - 2) + c2) + 2) / 2;
}
double CJZAPI EaseOutCubic(double _x)
{
	return 1 - pow(1 - _x, 3);
}
double CJZAPI EaseOutSine(double _x)
{
	return sin((_x * PI) / 2.0);
}
double CJZAPI EaseInOutCubic(double _x)
{
	return _x < 0.5 ? 4 * _x * _x * _x : 1 - pow(-2 * _x + 2, 3) / 2;
}
double CJZAPI EaseInOutElastic(double _x)
{
	const double c5 = (2 * PI) / 4.5;
	return fequ(_x, 0.0)
		? 0.0
		: fequ(_x, 1.0)
		? 1.0
		: _x < 0.5
		? -(pow(2, 20 * _x - 10) * sin((20 * _x - 11.125) * c5)) / 2
		: (pow(2, -20 * _x + 10) * sin((20 * _x - 11.125) * c5)) / 2 + 1;
}
double CJZAPI EaseOutBounce(double _x)
{
	const double n1 = 7.5625;
	const double d1 = 2.75;

	if (_x < 1 / d1) {
		return n1 * _x * _x;
	}
	else if (_x < 2 / d1) {
		return n1 * (_x -= 1.5 / d1) * _x + 0.75;
	}
	else if (_x < 2.5 / d1) {
		return n1 * (_x -= 2.25 / d1) * _x + 0.9375;
	}
	else {
		return n1 * (_x -= 2.625 / d1) * _x + 0.984375;
	}
}
double CJZAPI EaseInOutBounce(double _x)
{
	return _x < 0.5
		? (1 - EaseOutBounce(1 - 2 * _x)) / 2
		: (1 + EaseOutBounce(2 * _x - 1)) / 2;
}
double CJZAPI EaseInOutExpo(double _x)
{
	return fequ(_x, 0.0)
		? 0.0
		: fequ(_x, 1.0)
		? 1.0
		: _x < 0.5 ? pow(2, 20 * _x - 10) / 2
		: (2 - pow(2, -20 * _x + 10)) / 2;
}

float GetNamedNumber(const string& s, bool& suc)
{
	suc = true;
	if (sequ(s, "uix"))		return uix;
	if (sequ(s, "uiy"))		return uiy;
	if (sequ(s, "uix_plus_uiy")) return uix + uiy;
	if (sequ(s, "midx"))	return uix / 2.0f;
	if (sequ(s, "midy"))	return uiy / 2.0f;
	if (sequ(s, "midx_plus_midy"))	return uix / 2.0f + uiy / 2.0f;
	if (sequ(s, "scr_w"))	return scr_w;
	if (sequ(s, "scr_h"))	return scr_h;
	if (sequ(s, "taskbar_h")) return taskbar_h;
	if (sequ(s, "caption_h"))	return caption_h;
	if (sequ(s, "pi"))	return PI;
	if (sequ(s, "uniform"))	return RandomRangeDouble(0.0, 1.0, true, true, 2);
	if (sequ(s, "rand_percentage")) return Randint(0, 100);
	if (sequ(s, "rand_deg") || sequ(s, "rand_degree"))	return RandomRangeDouble(0.0, 360.0, true, false, 1);
	if (sequ(s, "rand_rad") || sequ(s, "rand_radian"))	return RandomRangeDouble(0.0, 2 * PI, true, false, 1);
	//不能报错
	suc = false;
	return 0.0f;
}
float CalcNumberExpr(float a, float b, const string& op)
{
	XCPT_L
	if (op == "+")	return a + b;
	if (op == "-")	return a - b;
	if (op == "*")	return a * b;
	if (op == "/")	return a / b;
	if (op == "^")	return pow(a, b);
	if (op == "%")	return (int)a % (int)b;	//否则会崩溃
	ErrorLogTip("无效的操作符：" + op, "CalcNumberExpr");
	XCPT_R
	return 0.0f;
}
float ParseNumber(const string& s)
{	//e.g.		uix-5
	//e.g.		
	string varName = "";	string op = "";
	string another = "";
	for (int i = 0; i < s.size(); ++i)
	{
		if (s.at(i) > 0 && s.at(i) < 255 && ispunct(s.at(i)) && s.at(i) != '_' && s.at(i) != '.')
		{	//op start
			if (varName.empty())
				varName = s.substr(0, i);
			else if (!op.empty() && s.at(i) == '-')
			{
				another = "-";	//这是负号呀拜托
				continue;
			}
			op += s.at(i);
		}
		else if (!op.empty())
		{	//op stop
			another += s.substr(i, s.size() - 1);
			break;
		}
	}
	if (varName.empty())	varName = s;
	//DebugLogFormat("ParseNumber: varName=%s  op=%s  another=%s", varName.c_str(), op.c_str(), another.c_str());
	if (op != "" && another != "")
	{
		float fore = 0, back = 0;
		for (int j = 0; j < 2; j++)
		{
			string* sptr = (j == 0 ? &varName : &another);
			float*	res = (j == 0 ? &fore : &back);
			bool suc = false;
			*res = GetNamedNumber(*sptr, suc);
			if (!suc)	*res = Convert<string, float>(*sptr);
		}
		return CalcNumberExpr(fore, back, op);
	}
	else {
		bool suc = false;
		float res = GetNamedNumber(varName, suc);
		if (!suc)
		{
			if (strtail(varName) == "f" || strtail(varName) == "L" || strtail(varName) == "s")
			{	//后缀
				strxtail(varName);
			}
			return Convert<string, float>(varName);
		}
		return res;
	}
}

template <typename _Tp>
inline bool HaveFlag(_Tp var, const _Tp chkFlag)
{
	return (var & chkFlag == chkFlag);
}