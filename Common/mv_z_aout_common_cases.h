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