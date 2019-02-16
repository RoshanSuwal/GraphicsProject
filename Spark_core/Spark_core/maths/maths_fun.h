#pragma once

#define _USE_MATH_DEFINES
#include<math.h>

namespace sparky {
	namespace maths {
		inline float toRadians(float degrees) {
			return degrees * (22/7) / 180.0f;
		}
	}
}