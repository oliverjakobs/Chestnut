#include "poly.h"

namespace chstMath
{
	Poly::Poly(std::vector<glm::vec2> vert) 
		: m_vertices(vert)
	{
		m_position = vert.front();
		m_centroid = getPolygonCentroid(vert);
		m_dimension = getPolygonDimension(vert);
	}

	Poly::Poly(const Rect& rect)
	{
		m_vertices = rect.getVeritces();

		m_position = rect.getPosition();
		m_dimension = rect.getDimension();
		m_centroid = glm::vec2(rect.x + rect.w / 2.0f, rect.y + rect.h / 2.0f);
	}

	Poly::Poly(float x, float y, float w, float h)
	{
		m_vertices.push_back(glm::vec2(x, y));
		m_vertices.push_back(glm::vec2(x + w, y));
		m_vertices.push_back(glm::vec2(x + w, y + h));
		m_vertices.push_back(glm::vec2(x, y + h));

		m_position = glm::vec2(x, y);
		m_centroid = glm::vec2(x + w / 2.0f, y + h / 2.0f);
		m_dimension = glm::vec2(w, h);
	}

	glm::vec2 Poly::getCentroid() const { return m_centroid; }

	glm::vec2 Poly::getPosition() const { return m_position; }

	glm::vec2 Poly::getDimension() const { return m_dimension; }

	std::vector<glm::vec2> Poly::getVertices() const { return m_vertices; }

	bool Poly::inside(const glm::vec2& point)
	{
		return isInside(point, m_vertices);
	}
}
