#include "chstpch.h"
#include "View.h"

#include "glm\gtc\matrix_transform.hpp"

#include "Renderer.h"

namespace chst
{
	void View::create(float x, float y, float w, float h)
	{
		xPos = x;
		yPos = y;
		width = w;
		height = h;

		mat = glm::ortho(xPos, xPos + width, yPos, yPos + height, 1.0f, -1.0f);
	}

	glm::vec2 View::fromScreen(const glm::vec2& screenPos) const
	{
		float x = screenPos.x * (width / Renderer::GetWindowWidth());
		float y = height - (screenPos.y  * (height / Renderer::GetWindowHeight()));

		return glm::vec2(x, y);
	}
}
