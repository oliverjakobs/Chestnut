#pragma once

#include "geometry.h"

namespace chstMath
{
	struct Rect
	{
		float x, y, w, h;

		Rect();
		Rect(float x, float y, float w, float h);
		Rect(glm::vec2 pos, glm::vec2 dim);

		glm::vec2 getPosition() const;
		glm::vec2 getDimension() const;
		std::vector<glm::vec2> getVeritces() const; 
		
		friend Rect operator+(Rect r, glm::vec2 v);

		bool inside(const glm::vec2& point);
	};
}