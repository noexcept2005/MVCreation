		if (clock() - start > life)
			return;
		float x = sx, y = sy;
		float s_rot = json.HaveKey("s_rot") ? ParseNumber(json.GetValueRaw("s_rot")) : 0.0f;
		float e_rot = json.HaveKey("e_rot") ? ParseNumber(json.GetValueRaw("e_rot")) : s_rot;
		float rot = s_rot;

		float ex = json.HaveKey("ex") ? ParseNumber(json.GetValueRaw("ex")) : sx;
		float ey = json.HaveKey("ey") ? ParseNumber(json.GetValueRaw("ey")) : sy;

		clock_t in_time = json.HaveKey("in_time") ? (clock_t)ParseNumber(json.GetValueRaw("in_time")) : TEXT_DEF_IN_TIME;
		if (a_in == AIN_NONE)
			in_time = 0L;
		AnimaOut a_out = json.HaveKey("a_out") ? ParseAnimaOut(json.GetString("a_out")) : AOUT_FADEOUT;
		clock_t out_time = json.HaveKey("out_time") ? (clock_t)ParseNumber(json.GetValueRaw("out_time")) : TEXT_DEF_OUT_TIME;
		if (a_out == AOUT_NONE)
			out_time = 0L;

		bool rel_to_camera = IsRelativeToCamera();