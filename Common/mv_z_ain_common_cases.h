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