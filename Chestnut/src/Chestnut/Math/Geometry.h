#pragma once

#include <vector>
#include "glm\glm.hpp"

namespace chstMath
{
	inline bool isInside(const glm::vec2& point, float x, float y, float w, float h)
	{
		if (point.x >= x && point.y >= y && point.x <= (x + w) && point.y <= (y + h))
			return true;

		return false;
	}

	inline bool isInside(const glm::vec2& point, const std::vector<glm::vec2>& vertices)
	{
		bool c = false;

		for (unsigned int i = 0, j = vertices.size() - 1; i < vertices.size(); j = i++)
		{
			if (((vertices[i].y > point.y) != (vertices[j].y > point.y)) &&
				(point.x < (vertices[j].x - vertices[i].x) * (point.y - vertices[i].y) / (vertices[j].y - vertices[i].y) + vertices[i].x))
				c = !c;
		}
		return c;
	}

	inline glm::vec2 getPolygonDimension(std::vector<glm::vec2> vertices)
	{
		if (vertices.empty())
			return glm::vec2();

		float minX = vertices.front().x;
		float maxX = vertices.front().x;

		float minY = vertices.front().y;
		float maxY = vertices.front().y;

		for (auto& v : vertices)
		{
			if (v.x < minX) minX = v.x;
			if (v.x > maxX) maxX = v.x;

			if (v.y < minY) minY = v.y;
			if (v.y > maxY) maxY = v.y;
		}

		return glm::vec2(maxX - minX, maxY - minY);
	}

	inline glm::vec2 getPolygonCentroid(std::vector<glm::vec2> vertices)
	{
		if (vertices.empty())
			return glm::vec2();

		glm::vec2 centroid = { 0, 0 };
		float signedArea = 0.0f;
		float x0 = 0.0f; // Current vertex X
		float y0 = 0.0f; // Current vertex Y
		float x1 = 0.0f; // Next vertex X
		float y1 = 0.0f; // Next vertex Y
		float a = 0.0f;  // Partial signed area

		for (unsigned int i = 0; i < vertices.size(); ++i)
		{
			x0 = vertices[i].x;
			y0 = vertices[i].y;
			x1 = vertices[(i + 1) % vertices.size()].x;
			y1 = vertices[(i + 1) % vertices.size()].y;
			a = x0 * y1 - x1 * y0;
			signedArea += a;
			centroid.x += (x0 + x1)*a;
			centroid.y += (y0 + y1)*a;
		}

		signedArea *= 0.5f;
		centroid.x /= (6.0f * signedArea);
		centroid.y /= (6.0f * signedArea);

		return centroid;
	}

	inline bool isConvex(std::vector<glm::vec2> points)
	{
		//If we have less than 3 points (dot or line) return
		if (points.size() < 3)
			return true;

		//lengths on x and y axes between points i, i+1 and i+2
		float dx1, dy1, dx2, dy2, zComp;

		//Sign of z-components, false = positive, true = negative
		bool hasSign;

		//We get the sign of the z-component for the first 3 points to serve as a basis for the rest of out comparisons
		dx1 = points[1].x - points[0].x;
		dy1 = points[1].y - points[0].y;
		dx2 = points[2].x - points[1].x;
		dy2 = points[2].y - points[1].y;
		zComp = dx1 * dy2 - dx2 * dy1;
		hasSign = zComp < 0;

		//Check sign of z-component of the rest of the points on the polygon. 
		//If theyre all the same, we have a convex polygon, otherwise it is concave.
		unsigned int numberOfPoints = points.size();

		for (unsigned int i = 1; i < numberOfPoints; ++i)
		{
			dx1 = points[(i + 1) % numberOfPoints].x - points[i].x;
			dy1 = points[(i + 1) % numberOfPoints].y - points[i].y;
			dx2 = points[(i + 2) % numberOfPoints].x - points[(i + 1) % numberOfPoints].x;
			dy2 = points[(i + 2) % numberOfPoints].y - points[(i + 1) % numberOfPoints].y;
			zComp = dx1 * dy2 - dx2 * dy1;

			//If any of the z-components has the opposite sign of the base case, shape is concave.
			if ((zComp < 0 && !hasSign) || (zComp > 0 && hasSign))
				return false;
		}

		return true;
	}

	inline std::vector<glm::vec2> moveVertices(const std::vector<glm::vec2>& vertices, const glm::vec2& vec)
	{
		std::vector<glm::vec2> moved;

		for (auto& v : vertices)
			moved.push_back(v + vec);

		return moved;		
	}

	inline float distance(const glm::vec2& a, const glm::vec2& b)
	{
		return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
	}

	struct Line
	{
		glm::vec2 start;
		glm::vec2 end;

		Line() : start(glm::vec2(0.0f)), end(glm::vec2(0.0f)) {};

		Line(float x1, float y1, float x2, float y2)
			: start(glm::vec2(x1, y1)), end(glm::vec2(x2, y2)) {};

		friend Line operator+(Line l, glm::vec2 v)
		{
			l.start = l.start + v;
			l.end = l.end + v;

			return l;
		}
	};
}

