#pragma once

#include "math\maths.h"

namespace chst
{
	struct AABB
	{
		glm::vec2 center;
		glm::vec2 halfDimension;

		AABB() : center(glm::vec2()), halfDimension(glm::vec2()) {}
		AABB(const glm::vec2& cen, const glm::vec2& halfDim) : center(cen), halfDimension(halfDim) {}
	};
}