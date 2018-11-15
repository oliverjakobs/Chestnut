#pragma once

#include "poly.h"

namespace chestnutMath
{
#define EPSILON 0.000001
#define M_PI	3.14159265359f

	inline bool isBetween(float value, float left, float right)
	{
		return value > left && value < right;
	}

	inline bool isBetweenE(float value, float left, float right)
	{
		return value >= left && value <= right;
	}

	inline bool compare(float f1, float f2)
	{
		return fabs(f1 - f2) < EPSILON;
	}

	inline bool compare(const glm::vec2& vec1, const glm::vec2& vec2)
	{
		return compare(vec1.x, vec2.x) && compare(vec1.y, vec2.y);
	}
}