#pragma once

namespace CardMath {
	
	template<typename T>
	T clamp(T val, T min, T max) {

		if (val > max)
			val = max;

		else if (val < min)
			val = min;

		return val;
	}
};