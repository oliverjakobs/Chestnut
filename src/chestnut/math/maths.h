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

	inline glm::vec2 clampVec2(const glm::vec2& vec, float c)
	{
		if (vec.length() > c)
			return glm::normalize(vec) * c;

		return vec;
	}

	inline glm::vec2 project(const glm::vec2& a, const glm::vec2& b)
	{
		return glm::dot(a, glm::normalize(b)) * glm::normalize(b);
	}

	inline float roundFloat(float f, int decimal) { return std::roundf(f * decimal) / decimal; }
	inline float ceilFloat(float f, int decimal) { return std::ceilf(f * decimal) / decimal; }
}