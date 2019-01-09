#pragma once

#include "math\maths.h"

namespace chst
{
	struct View
	{
		float xPos;
		float yPos;
		float width;
		float height;

		glm::mat4 mat;

		void create(float x, float y, float width, float height);
		glm::vec2 fromScreen(const glm::vec2& screenPos) const;
	};
}