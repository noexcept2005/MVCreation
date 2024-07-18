#pragma once
////////////////////////////////////////////////
//         MV C++ Performer ר��ͷ�ļ�         //
//          by Wormwaker, ��ֹ����             //
////////////////////////////////////////////////

class BackgroundManager
{
public:

	BackgroundManager()
	{	}

	color_t GetActualBackColor()	//������MV_Draw�е���
	{
		return getbkcolor(imgBuffer);
	}
	void SetBackColor(color_t clr)
	{
		s_color = e_color = clr;
		fade_duration = 0L;
	}
	color_t GetBackColor() const
	{
		if (fade_duration == 0L)
			return s_color;
		if (!BackColorInFading())
			return e_color;
		return StepColor(s_color, e_color, Clamp<double>((clock() - fade_start) / double(fade_duration), 0.0, 1.0));
	}
	void StartBackColorFading(color_t eColor, clock_t duration_ms)
	{
		s_color = GetBackColor();
		e_color = eColor;
		fade_duration = duration_ms;
		fade_start = clock();
	}
	void StartBackColorFading(color_t sColor, color_t eColor, clock_t duration_ms)
	{
		s_color = sColor, e_color = eColor;
		fade_duration = duration_ms;
		fade_start = clock();
	}
	bool BackColorInFading() const
	{
		return (fade_duration > 0L && clock() - fade_start <= fade_duration);
	}

	void UpdateActualBackColor()
	{
		XCPT_L
		if (!BackColorInFading())
		{
			if (GetActualBackColor() != s_color)
				setbkcolor(s_color, imgBuffer);
		}
		setbkcolor(GetBackColor());
		setbkcolor(GetBackColor(), imgBuffer);
		XCPT_R
	}
private:

	color_t s_color = BLACK;
	color_t e_color = BLACK;
	clock_t fade_duration = 0L;		//����ʱ��
	clock_t fade_start = 0L;		//������ʼʱ���

}bgMgr;