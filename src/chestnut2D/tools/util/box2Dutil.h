#pragma once

#include "Box2D\Box2D.h"
#include "math\maths.h"

namespace chestnut2D
{
	inline glm::vec2 convertFromb2(b2Vec2 vec)
	{
		return glm::vec2(vec.x, vec.y);
	}

	inline b2Vec2 convertTob2(const glm::vec2& vec)
	{
		return b2Vec2(vec.x, vec.y);
	}
}