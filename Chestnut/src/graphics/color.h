#pragma once

#include "glm\glm.hpp"

namespace chst
{
	const glm::vec4 BLACK	= glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	const glm::vec4 WHITE	= glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	const glm::vec4 RED		= glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	const glm::vec4 GREEN	= glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	const glm::vec4 BLUE	= glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	const glm::vec4 YELLOW	= glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
	const glm::vec4 MAGENTA = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
	const glm::vec4 CYAN	= glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);


	inline glm::vec4 blendColor(const glm::vec4& color, float alpha)
	{
		return glm::vec4(color.r, color.g, color.b, alpha);
	}
}