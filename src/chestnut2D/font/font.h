#pragma once

#include "graphics.h"

namespace chestnut2D
{
	class Font
	{
	public:
		virtual void draw(const std::string& text, float x, float y, const glm::vec4& color, const glm::mat4& view) const = 0;
		virtual void draw(const std::string& text, const glm::vec2& position, const glm::vec4& color, const glm::mat4& view) const = 0;
	};
}