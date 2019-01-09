#pragma once

#include "rect.h"

namespace chstMath
{
	class Poly
	{
	private:
		glm::vec2 m_centroid;
		glm::vec2 m_position;
		glm::vec2 m_dimension;

		std::vector<glm::vec2> m_vertices;

	public:
		Poly(std::vector<glm::vec2> vert);
		Poly(const Rect& rect);
		Poly(float x, float y, float w, float h);

		glm::vec2 getCentroid() const;
		glm::vec2 getPosition() const;
		glm::vec2 getDimension() const; 
		std::vector<glm::vec2> getVertices() const;

		bool inside(const glm::vec2& point);
	};
}