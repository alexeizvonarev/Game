#pragma once
#include <SDL.h>
#include <cmath>

namespace utils
{
	inline float hireTimeInSeconds() {
		float t = SDL_GetTicks();
		t *= 0.001f;

		return t;
	}
	inline float getAngleFromVector(float x, float y) {
		float angle = std::atan2(y-720/2, x-1280/2);
		float degrees = 180 * angle / 3.14;

		int rd = std::round(degrees);
		return (360 + rd) % 360;
	}
}