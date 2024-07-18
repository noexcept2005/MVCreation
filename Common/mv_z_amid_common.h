		clock_t motion_delay = json.HaveKey("motion_delay") ? json.GetLong("motion_delay") : 0L;
		clock_t motion_time = json.HaveKey("motion_time") ? json.GetLong("motion_time") : life - in_time - out_time - motion_delay;

		double _ratio = (clock() - start - in_time - motion_delay) / double(motion_time);
		if (clock() - start - in_time - motion_delay < 0L)
			_ratio = 0.0f;

		ChangeFunc chgf_id = json.HaveKey("change_func") ? ParseChangeFunctionID(json.GetString("change_func")) : CHGF_LERP;
		auto change_func = GetChangeFunction(chgf_id);
		x = Lerp<float>(sx, ex, change_func(_ratio));
		y = Lerp<float>(sy, ey, change_func(_ratio));
		if (!fequ(s_rot, e_rot))
		rot = Lerp<float>(s_rot, e_rot, change_func(_ratio));