#include "rect.h"

namespace chestnutMath
{
	Rect::Rect() : x(0.0f), y(0.0f), w(0.0f), h(0.0f)
	{
	}

	Rect::Rect(float x, float y, float w, float h)
		: x(x), y(y), w(w), h(h)
	{
	}

	Rect::Rect(glm::vec2 pos, glm::vec2 dim)
		: x(pos.x), y(pos.y), w(dim.x), h(dim.y)
	{
	}

	glm::vec2 Rect::getPosition() const
	{
		return glm::vec2(x, y);
	}

	glm::vec2 Rect::getDimension() const
	{
		return glm::vec2(w, h);
	}

	std::vector<glm::vec2> Rect::getVeritces() const
	{
		return {
			glm::vec2(x, y),
			glm::vec2(x + w, y),
			glm::vec2(x + w, y + h),
			glm::vec2(x, y + h)
		};
	}

	bool Rect::inside(const glm::vec2 & point)
	{
		return isInside(point, x, y, w, h);
	}

	Rect operator+(Rect r, glm::vec2 v)
	{
		r.x += v.x;
		r.y += v.y;

		return r;
	}
}