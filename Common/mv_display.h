#pragma once
////////////////////////////////////////////////
//         MV C++ Performer ר��ͷ�ļ�         //
//          by Wormwaker, ��ֹ����             //
////////////////////////////////////////////////

///////////////////////////////////////////////////////////
//                  Color ɫ��ϵ��                        //
///////////////////////////////////////////////////////////

#define ALMOST_BLACK	EGERGB(1,1,1)
color_t CJZAPI Color16ToRGB(UINT u16Clr) {
	switch (u16Clr) {
	case 0: {
		return EGERGB(0, 0, 0);		//��
		//return ALMOST_BLACK;
		break;
	}
	case 1: {
		return EGERGB(0, 0, 128);	//����
		break;
	}
	case 2: {
		return EGERGB(0, 128, 0);	//����
		break;
	}
	case 3: {
		return EGERGB(0, 128, 128);	//��ɫ
		break;
	}
	case 4: {
		return EGERGB(128, 0, 0);	//Dark Red
		break;
	}
	case 5: {
		return EGERGB(128, 0, 128);	//Dark Magenta
		break;
	}
	case 6: {
		return EGERGB(128, 128, 0);	//Brown
		break;
	}
	case 7: {
		return EGERGB(192, 192, 192);	//ǳ��
		break;
	}
	case 8: {
		return EGERGB(128, 128, 128);	//���
		break;
	}
	case 9: {
		return EGERGB(0, 0, 255);	//����
		break;
	}
	case 10: {
		return EGERGB(0, 255, 0);	//����
		break;
	}
	case 11: {
		return EGERGB(0, 255, 255);	//����
		break;
	}
	case 12: {
		return EGERGB(255, 0, 0);	//Ѫ��
		break;
	}
	case 13: {
		return EGERGB(255, 0, 255);	//Magenta ��ɫ
		break;
	}
	case 14: {
		return EGERGB(255, 255, 0);	//����
		break;
	}
	case 15: {
		return EGERGB(255, 255, 255);	//��
		break;
	}
	default: {
		return EGERGB(0, 0, 0);
		break;
	}
	}
}

color_t CJZAPI StepColor0(color_t startColor, color_t endColor, double rate) {
	if (fequ(rate, 0.0))	return startColor;
	if (fequ(rate, 1.0))	return endColor;
	//��ɫ�Ľ���
	int r = (EGEGET_R(endColor) - EGEGET_R(startColor));
	int g = (EGEGET_G(endColor) - EGEGET_G(startColor));
	int b = (EGEGET_B(endColor) - EGEGET_B(startColor));

	int nSteps = max(abs(r), max(abs(g), abs(b)));
	if (nSteps < 1) nSteps = 1;

	// Calculate the step size for each color
	float rStep = r / (float)nSteps;
	float gStep = g / (float)nSteps;
	float bStep = b / (float)nSteps;

	// Reset the colors to the starting position
	float fr = EGEGET_R(startColor);
	float fg = EGEGET_G(startColor);
	float fb = EGEGET_B(startColor);

	color_t color = startColor;
	for (int i = 0; i < int(nSteps * rate); i++) {
		fr += rStep;
		fg += gStep;
		fb += bStep;
		color = RGB((int)(fr + 0.5), (int)(fg + 0.5), (int)(fb + 0.5));
		//color ��Ϊ�ؽ���ɫ
	}
	return color;
}//from https://bbs.csdn.net/topics/240006897 , owner: zgl7903

color_t CJZAPI StepColor(color_t startColor, color_t endColor, double rate) {
	// ��ȡ��ʼ��ɫ����
	int startR = EGEGET_R(startColor);
	int startG = EGEGET_G(startColor);
	int startB = EGEGET_B(startColor);

	// ��ȡ������ɫ����
	int endR = EGEGET_R(endColor);
	int endG = EGEGET_G(endColor);
	int endB = EGEGET_B(endColor);

	// ���������ɫ����
	int newR = static_cast<int>(startR + (endR - startR) * rate);
	int newG = static_cast<int>(startG + (endG - startG) * rate);
	int newB = static_cast<int>(startB + (endB - startB) * rate);

	// ���������ɫ
	color_t resultColor = EGERGB(newR, newG, newB);
	return resultColor;
}

inline COLORREF CJZAPI WinColor(color_t clr) {
	//EGERGB -> RGB
	return RGB(EGEGET_R(clr), EGEGET_G(clr), EGEGET_B(clr));
}
inline color_t CJZAPI EgeColor(COLORREF clr) {
	//RGB -> EGERGB
	return EGERGB(GetRValue(clr), GetGValue(clr), GetBValue(clr));
}
inline color_t CJZAPI InvertedColor(color_t clr) {
	return EGERGB(255 - EGEGET_R(clr), 255 - EGEGET_G(clr), 255 - EGEGET_B(clr));
}

#define WVC_AMP 12
#define WVC_OMEGA 13.0
#define WVC_PHASE0 0
clock_t lastWvBeg = 0;
inline COLORREF WaveColor(COLORREF originClr, float phi = 0.0f) {	//originClr����Ϊ���ֵ
	//��˸����ɫ ������Ϸ��������
	short val = WVC_AMP * sin(WVC_OMEGA*((clock() - lastWvBeg) / 1000.0) + WVC_PHASE0 + phi) - WVC_AMP * 2;
	short r = GetRValue(originClr) + val, g = GetGValue(originClr) + val, b = GetBValue(originClr) + val;
	ClampA<short>(r, 2, 255);
	ClampA<short>(g, 2, 255);
	ClampA<short>(b, 2, 255);
	return RGB(r, g, b);
}
inline color_t WaveColor(color_t originClr, float phi = 0.0f)
{
	return EgeColor(WaveColor(WinColor(originClr), phi));
}
// ����������RGB��HSV��ɫת��
void RGBtoHSV(COLORREF rgb, double& h, double& s, double& v) {
	double r = GetRValue(rgb) / 255.0;
	double g = GetGValue(rgb) / 255.0;
	double b = GetBValue(rgb) / 255.0;

	double minVal = min(min(r, g), b);
	double maxVal = max(max(r, g), b);
	double delta = maxVal - minVal;

	// ����ɫ��
	if (delta > 0) {
		if (maxVal == r)
			h = 60.0 * fmod((g - b) / delta, 6.0);
		else if (maxVal == g)
			h = 60.0 * ((b - r) / delta + 2.0);
		else if (maxVal == b)
			h = 60.0 * ((r - g) / delta + 4.0);
	}
	else {
		h = 0.0;
	}

	// ���㱥�ͶȺ�����
	s = (maxVal > 0) ? (delta / maxVal) : 0.0;
	v = maxVal;
}

// ����������HSV��RGB��ɫת��
COLORREF HSVtoRGB(double h, double s, double v) {
	int hi = static_cast<int>(floor(h / 60.0)) % 6;
	double f = h / 60.0 - floor(h / 60.0);
	double p = v * (1.0 - s);
	double q = v * (1.0 - f * s);
	double t = v * (1.0 - (1.0 - f) * s);

	switch (hi) {
	case 0: return RGB(static_cast<int>(v * 255), static_cast<int>(t * 255), static_cast<int>(p * 255));
	case 1: return RGB(static_cast<int>(q * 255), static_cast<int>(v * 255), static_cast<int>(p * 255));
	case 2: return RGB(static_cast<int>(p * 255), static_cast<int>(v * 255), static_cast<int>(t * 255));
	case 3: return RGB(static_cast<int>(p * 255), static_cast<int>(q * 255), static_cast<int>(v * 255));
	case 4: return RGB(static_cast<int>(t * 255), static_cast<int>(p * 255), static_cast<int>(v * 255));
	case 5: return RGB(static_cast<int>(v * 255), static_cast<int>(p * 255), static_cast<int>(q * 255));
	default: return RGB(0, 0, 0);  // Shouldn't reach here
	}
}

// ��������������ʱ��仯�Ĳʺ�ɫ
color_t RainbowColor() {
	// ����ʱ�䰴����㣬����ʹ��ϵͳʱ��������ʵ���ʱ��Դ
	double timeInSeconds = GetTickCount() / 1000.0;

	// ɫ�ఴʱ��仯
	double hue = fmod(timeInSeconds * 30.0, 360.0);  // ����ÿ��仯30��

	// ���ͶȺ����ȱ��ֲ���
	double saturation = 1.0;
	double value = 1.0;

	// ��HSV��ɫת��ΪRGB������
	return EgeColor(HSVtoRGB(hue, saturation, value));
}

color_t FadeInOutColor(color_t bodyColor, clock_t deltaTime, clock_t totalTime, clock_t inTime, clock_t outTime, color_t endColor = BLACK)
{
	if (deltaTime >= inTime && deltaTime <= totalTime - outTime)
		return bodyColor;
	if (deltaTime >= totalTime || deltaTime <= 0L)
		return endColor;
	if (deltaTime <= inTime)
		return StepColor(endColor, bodyColor, deltaTime / double(inTime));
	return StepColor(bodyColor, endColor, (deltaTime - (totalTime - outTime)) / double(outTime));
}

///////////////////////////////////////////////////////////
//                   Display չʾϵ��                     //
///////////////////////////////////////////////////////////

int centerprintf(const char* szFormat, ...)
{
	va_list va;
	va_start(va, szFormat);
	char buffer[1024] = "\0";
	int res = _vsnprintf(buffer, 1024, szFormat, va);
	va_end(va);
	int x = uix / 2 - textwidth(buffer) / 2;
	int y = uiy / 2 - textheight(buffer) / 2;
	xyprintf(x, y, buffer);
	return res;
}
int midprintf(int y, const char* szFormat, ...)
{
	va_list va;
	va_start(va, szFormat);
	char buffer[1024] = "\0";
	int res = _vsnprintf(buffer, 1024, szFormat, va);
	va_end(va);
	int x = uix / 2 - textwidth(buffer) / 2;
	xyprintf(x, y, buffer);
	return res;
}

void __cdecl _resize(PIMAGE pDstImg, int w, int h)
{	//��дһ��
	int width = getwidth(pDstImg);
	int height = getheight(pDstImg);
	PIMAGE backproc = newimage(w, h);
	//Resize
	putimage(backproc, 0, 0, w, h, pDstImg, 0, 0, width, height);
	//delimage(pDstImg);
	//pDstImg = newimage();
		//putimage_withalpha(backproc, pDstImg, 0, 0, 0, 0, w, h);
	getimage(pDstImg, backproc, 0, 0, w, h);
	delimage(backproc);
}

PIMAGE Specl(const PIMAGE t, double ratio) 
{		//ë����Ч��
	//������������ 
	int ax[] = { -1,0,1,-1,1,-1,0,1 };
	int ay[] = { -1,-1,-1,0,0,1,1,1 };

	PIMAGE f = newimage(getwidth(t), getheight(t));//���������Ե�Ķ��� 
	PIMAGE ft = newimage(getwidth(t) - 2, getheight(t) - 2);//���������в�ͼ��Ķ��� 

	color_t c;
	int r;
	int xt, yt;

	f = t;//�˴����ǲ�ȡ����Ե���еĵ㣬����ֱ�ӿ�¡ 
	//���ȡ�� 
	for (int y = 1; y < getheight(t) - 1; y++) {
		for (int x = 1; x < getwidth(t) - 1; x++) {
			if (randomf() >= ratio)
				continue;
			r = random(8);
			xt = x + ax[r];
			yt = y + ay[r];

			c = getpixel(xt, yt, t);
			putpixel(x - 1, y - 1, c, ft);
		}
	}
	putimage(f, 2, 2, ft);//������õ��в�ͼ��ֱ�Ӹ���f�ϣ�f���в���ft���ǣ���f��ֻʣ��δ����ı�Ե�ʹ���õ��в� 
	delimage(ft);
	return f;
}
void GlowA(PIMAGE img, double ratio) {
	ratio *= 0.8;
	int w = getwidth(img);
	int h = getheight(img);

	const int glowRadius = static_cast<int>(12 * ratio);
	if (glowRadius <= 0) return;

	color_t* buffer = getbuffer(img);

	const int area = (2 * glowRadius + 1) * (2 * glowRadius + 1);

	for (int y = glowRadius; y < h - glowRadius; ++y) {
		for (int x = glowRadius; x < w - glowRadius; ++x) {
			int r_sum = 0, g_sum = 0, b_sum = 0;

			for (int dy = -glowRadius; dy <= glowRadius; ++dy) {
				for (int dx = -glowRadius; dx <= glowRadius; ++dx) {
					color_t clr = buffer[(y + dy) * w + x + dx];
					r_sum += EGEGET_R(clr);
					g_sum += EGEGET_G(clr);
					b_sum += EGEGET_B(clr);
				}
			}

			auto r_avg = r_sum / area;
			auto g_avg = g_sum / area;
			auto b_avg = b_sum / area;

			color_t clr = buffer[y * w + x];
			auto r = Clamp(static_cast<unsigned int>(EGEGET_R(clr) + (r_avg - EGEGET_R(clr)) * ratio), 0U, 255U);
			auto g = Clamp(static_cast<unsigned int>(EGEGET_G(clr) + (g_avg - EGEGET_G(clr)) * ratio), 0U, 255U);
			auto b = Clamp(static_cast<unsigned int>(EGEGET_B(clr) + (b_avg - EGEGET_B(clr)) * ratio), 0U, 255U);

			buffer[y * w + x] = EGERGB(r, g, b);
		}
	}
}

void InvertA(PIMAGE pimage, double ratio)
{	//��ɫ
	ClampA(ratio, 0.0, 1.0);
	if (fequ(ratio, 1.0))
	{
		for (size_t y = 0; y < getheight(); ++y)
			for (size_t x = 0; x < getwidth(); ++x)
				putpixel(x, y, InvertedColor(getpixel(x, y, pimage)), pimage);
		return;
	}
	for (size_t y = 0; y < getheight(); ++y)
		for (size_t x = 0; x < getwidth(); ++x)
		{
			color_t clr = getpixel(x, y, pimage);
			putpixel(x, y, StepColor(clr, InvertedColor(clr), ratio), pimage);
		}
}

void GaussianBlurA(PIMAGE pimage, double radius)
{
	XCPT_L
	//radius = 255 * radius;
	int size = std::ceil(radius) * 2 + 1; // ģ���뾶����ȡ��ֵ��Ϊģ������Ĵ�С
	static std::vector<std::vector<double>> kernel(size, std::vector<double>(size));
	static double lastRadius = 0.0;

	double center = size / 2.0;
	if (!fequ(lastRadius, radius))
	{
		double sigma = radius / 3;
		double sigma2 = 2 * sigma * sigma;
		double sum = 0;
		// �����˹ģ����Ȩ�ؾ���
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				int x = i - center;
				int y = j - center;
				kernel[i][j] = std::exp(-(x * x + y * y) / sigma2) / (PI * sigma2);
				sum += kernel[i][j];
			}
		}

		// ��һ��Ȩ�ؾ���ʹ��Ȩ��֮��Ϊ1
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				kernel[i][j] /= sum;
			}
		}
		lastRadius = radius;
	}

	int width = getwidth(pimage);
	int height = getheight(pimage);
	color_t* buffer = getbuffer(pimage);

	// ��ÿ�����ؽ���ģ������
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			double red = 0, green = 0, blue = 0;

			// ��ÿ��������Χ������Ӧ��Ȩ�ؾ������ģ�������ɫֵ
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					int x = col + i - center;
					int y = row + j - center;

					// ����߽����
					x = max(0, min(width - 1, x));
					y = max(0, min(height - 1, y));

					color_t pixel = buffer[y * width + x];
					double weight = kernel[i][j];

					red += EGEGET_R(pixel) * weight;
					green += EGEGET_G(pixel) * weight;
					blue += EGEGET_B(pixel) * weight;
				}
			}

			// ��ģ�������ɫֵ���浽���ͼƬ�е���Ӧλ��
			buffer[row * width + col] = EGERGB(static_cast<int>(red), static_cast<int>(green), static_cast<int>(blue));
		}
	}
	XCPT_R
}
void SharpenA(PIMAGE pimage, double strength)
{
	int width = getwidth(pimage);
	int height = getheight(pimage);

	// ������ǿ�ȵ���������
	double normalizedStrength = max(0.0, min(1.0, strength));

	// ��ÿ�����ؽ����񻯴���
	for (int row = 1; row < height - 1; row++) {
		for (int col = 1; col < width - 1; col++) {
			// ��ȡ��ǰ���ؼ�����Χ���ص���ɫֵ
			color_t centerPixel = getpixel(col, row, pimage);
			color_t leftPixel = getpixel(col - 1, row, pimage);
			color_t rightPixel = getpixel(col + 1, row, pimage);
			color_t topPixel = getpixel(col, row - 1, pimage);
			color_t bottomPixel = getpixel(col, row + 1, pimage);

			// �����񻯺����ɫֵ
			int red = EGEGET_R(centerPixel) + normalizedStrength * (EGEGET_R(centerPixel) - (EGEGET_R(leftPixel) + EGEGET_R(rightPixel) + EGEGET_R(topPixel) + EGEGET_R(bottomPixel)) / 4.0);
			int green = EGEGET_G(centerPixel) + normalizedStrength * (EGEGET_G(centerPixel) - (EGEGET_G(leftPixel) + EGEGET_G(rightPixel) + EGEGET_G(topPixel) + EGEGET_G(bottomPixel)) / 4.0);
			int blue = EGEGET_B(centerPixel) + normalizedStrength * (EGEGET_B(centerPixel) - (EGEGET_B(leftPixel) + EGEGET_B(rightPixel) + EGEGET_B(topPixel) + EGEGET_B(bottomPixel)) / 4.0);

			// ���񻯺����ɫֵ���浽���ͼƬ�е���Ӧλ��
			putpixel(col, row, (EGERGB(max(0, min(255, red)), max(0, min(255, green)), max(0, min(255, blue)))), pimage);
		}
	}
	delay_fps(60);
}
// �Աȶȵ����㷨
void AdjustContrastA(PIMAGE img, double intensity)
{
	int width = getwidth(img);
	int height = getheight(img);

	// ���ݵ���ǿ�ȼ���Աȶȵ�������
	double factor = pow(2.0, intensity);

	// ��ÿ�����ؽ��жԱȶȵ���
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			// ��ȡ��ǰ���ص���ɫֵ
			color_t pixel = getpixel(col, row, img);

			// ��ÿ����ɫͨ�����жԱȶȵ���
			int red = max(0, min(255, static_cast<int>((EGEGET_R(pixel) - 128) * factor + 128)));
			int green = max(0, min(255, static_cast<int>((EGEGET_G(pixel) - 128) * factor + 128)));
			int blue = max(0, min(255, static_cast<int>((EGEGET_B(pixel) - 128) * factor + 128)));

			// �����������ɫֵ���浽���ͼƬ�е���Ӧλ��
			putpixel(col, row, EGERGB(red, green, blue), img);
		}
	}
}
// ���Ͷȵ�������
void AdjustSaturationA(PIMAGE img, double intensity)
{
	int width = getwidth(img);
	int height = getheight(img);

	// ��ÿ�����ؽ��б��Ͷȵ���
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			// ��ȡ��ǰ���ص���ɫֵ
			color_t pixel = getpixel(col, row, img);

			float h, s, v;
			rgb2hsv(pixel, &h, &s, &v);

			// ���ݵ���ǿ�ȵ������Ͷ�ֵ
			s += intensity;

			// ���Ʊ��Ͷ�ֵ��0-1֮��
			s = max(0.0, min<double>(1.0, s));

			// ���������HSVֵת����RGB��ɫ�ռ�
			color_t adjustedPixel = hsv2rgb(h, s, v);

			// �����������ɫֵ���浽���ͼƬ�е���Ӧλ��
			putpixel(col, row, adjustedPixel, img);
		}
	}
}