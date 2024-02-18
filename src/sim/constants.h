#pragma once

#undef M_1_PI
#undef M_2_PI
#undef M_1_PI

namespace math
{
	constexpr long double EXP       = 2.71828182845904523536;   // e
	constexpr long double PI        = 3.14159265358979323846;   // pi
	constexpr long double PI_2      = 1.57079632679489661923;   // pi/2
	constexpr long double PI_4      = 0.785398163397448309616;  // pi/4
	constexpr long double PI_3      = 1.04719755119659763131;   // pi/3
	constexpr long double PI_6      = 0.523598775598298815658;  // pi/6
	constexpr long double M_1_PI    = 0.318309886183790671538;  // 1/pi
	constexpr long double M_2_PI    = 0.636619772367581343076;  // 2/pi
	constexpr long double SQRT2     = 1.41421356237309504880;   // sqrt(2)
	constexpr long double M_1_SQRT2 = 0.707106781186547524401;  // 1/sqrt(2)
}

namespace anim {
	enum shape
	{
		none = 0,
		circle,
		rect,
		line
	};
}
