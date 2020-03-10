#pragma once
#include <algorithm>

namespace teaGameLib {

	//valueをminとmaxの範囲内に収まるように修正する
	template<typename T>
	constexpr T Clamp(const T& value, const T& min, const T& max) {
		return std::min({ std::max({ value,min }) , max });
	}
}