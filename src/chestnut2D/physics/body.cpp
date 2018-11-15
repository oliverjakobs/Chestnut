#include "body.h"

#include "map\tilemap.h"
#include <algorithm>   

namespace chestnutPhysics
{
	using namespace chestnut2D;
	
	AABB::AABB()
		: center(glm::vec2()), halfDimension(glm::vec2())
	{
		sensorOffset = 0.02f;
	}

	AABB::AABB(const glm::vec2& cen, const glm::vec2& halfDim)
		: center(cen), halfDimension(halfDim)
	{
		sensorOffset = 0.04f;

	}

	bool AABB::overlaps(const AABB& other) const
	{
		if (abs(center.x - other.center.x) > halfDimension.x + other.halfDimension.x) return false;
		if (abs(center.y - other.center.y) > halfDimension.y + other.halfDimension.y) return false;
		return true;
	}

	Line AABB::getSensorBottom(const glm::vec2& cen) const
	{
		return Line(cen.x - halfDimension.x , cen.y - halfDimension.y - sensorOffset, cen.x + halfDimension.x, cen.y - halfDimension.y - sensorOffset);
	}

	Line AABB::getSensorLeft(const glm::vec2& cen) const
	{
		return Line(cen.x - halfDimension.x - sensorOffset, cen.y - halfDimension.y + sensorOffset, cen.x - halfDimension.x - sensorOffset, cen.y + halfDimension.y - sensorOffset);
	}

	Line AABB::getSensorRight(const glm::vec2& cen) const
	{
		return Line(cen.x + halfDimension.x + sensorOffset, cen.y - halfDimension.y + sensorOffset, cen.x + halfDimension.x + sensorOffset, cen.y + halfDimension.y - sensorOffset);
	}

	Body::Body(float x, float y, float w, float h)
		: m_AABB(AABB(glm::vec2(x, y + (h / 2.0f)), glm::vec2(w, h) / 2.0f)), m_position(glm::vec2(x, y)), m_AABBOffset(glm::vec2(0.0f, h / 2.0f))
	{
		m_velocity = glm::vec2();

		m_onGround = false;
		m_wasOnGround = false;

		m_pushesLeftWall = false;
		m_pushesRightWall = false;
	}

	Body::~Body()
	{

	}

	void Body::setMap(chestnut2D::TileMap* map)
	{
		m_map = map;
	}

	void Body::update(float deltaTime)
	{		
		setPosition(m_position + m_velocity * deltaTime);
	}

	void Body::draw() const
	{
		Renderer::drawRect(Rect(m_AABB.center - m_AABB.halfDimension, m_AABB.halfDimension * 2.0f), m_pushesRightWall ? BLUE : GREEN);

		//Renderer::drawLine(m_AABB.getSensorBottom(m_AABB.center).start, m_AABB.getSensorBottom(m_AABB.center).end, RED);
		//Renderer::drawLine(m_AABB.getSensorLeft(m_AABB.center).start, m_AABB.getSensorLeft(m_AABB.center).end, RED);
		//Renderer::drawLine(m_AABB.getSensorRight(m_AABB.center).start, m_AABB.getSensorRight(m_AABB.center).end, RED);

		Renderer::fillCircle(m_position, 0.04f, BLACK);
	}

	void Body::setPosition(const glm::vec2& pos)
	{
		m_position = pos;
		m_AABB.center = m_position + m_AABBOffset;
	}

	void Body::setVelocity(float x, float y)
	{
		m_velocity = glm::vec2(x, y);	
	}

	void Body::applyVelocity(float x, float y)
	{
		setVelocity(m_velocity.x + x, m_velocity.y + y);
	}

	bool Body::hasGround(const glm::vec2& oldPosition, const glm::vec2& position, float* groundY) const
	{
		glm::vec2 oldCenter = oldPosition + m_AABBOffset;
		glm::vec2 center = position + m_AABBOffset;

		glm::vec2 oldBottomLeft = m_AABB.getSensorBottom(oldCenter).start;
		glm::vec2 newBottomLeft = m_AABB.getSensorBottom(center).start;
		glm::vec2 newBottomRight = m_AABB.getSensorBottom(center).end;

		int endY = m_map->getMapTileYAtPoint(newBottomLeft.y);
		int begY = std::max(m_map->getMapTileYAtPoint(oldBottomLeft.y) - 1, endY);
		int dist = std::max(abs(endY - begY), 1);

		int tileIndexX;

		for (int tileIndexY = begY; tileIndexY >= endY; --tileIndexY)
		{
			glm::vec2 bottomLeft = glm::mix(newBottomLeft, oldBottomLeft, (float)abs(endY - tileIndexY) / dist);
			glm::vec2 bottomRight = glm::vec2(bottomLeft.x + m_AABB.halfDimension.x * 2.0f, bottomLeft.y);

			for (glm::vec2 checkedTile = bottomLeft; ; checkedTile.x += m_map->getTileSize())
			{
				checkedTile.x = std::min(checkedTile.x, bottomRight.x);

				tileIndexX = m_map->getMapTileXAtPoint(checkedTile.x);

				*groundY = (float)tileIndexY * m_map->getTileSize() + m_map->getTileSize();

				if (m_map->isObstacle(tileIndexX, tileIndexY))
					return true;

				if (checkedTile.x >= bottomRight.x)
					break;
			}
		}

		return false;
	}

	bool Body::collidesWithLeftWall(const glm::vec2& oldPosition, const glm::vec2& position, float* wallX) const
	{
		glm::vec2 oldCenter = oldPosition + m_AABBOffset;
		glm::vec2 center = position + m_AABBOffset;

		glm::vec2 oldBottomLeft = m_AABB.getSensorLeft(oldCenter).start;
		glm::vec2 newBottomLeft = m_AABB.getSensorLeft(center).start;
		glm::vec2 newTopLeft = m_AABB.getSensorLeft(center).end;
		
		int endX = m_map->getMapTileXAtPoint(newBottomLeft.x);
		int begX = std::max(m_map->getMapTileXAtPoint(oldBottomLeft.x) - 1, endX);
		int dist = std::max(abs(endX - begX), 1);

		int tileIndexY;

		for (int tileIndexX = begX; tileIndexX >= endX; --tileIndexX)
		{
			glm::vec2 bottomLeft = glm::mix(newBottomLeft, oldBottomLeft, (float)abs(endX - tileIndexX) / dist);
			glm::vec2 topLeft = glm::vec2(bottomLeft.x, bottomLeft.y + (m_AABB.halfDimension.y - m_AABB.sensorOffset) * 2.0f );

			for (glm::vec2 checkedTile = bottomLeft; ; checkedTile.y += m_map->getTileSize())
			{
				checkedTile.y = std::min(checkedTile.y, topLeft.y);

				tileIndexY = m_map->getMapTileYAtPoint(checkedTile.y);

				if (m_map->isObstacle(tileIndexX, tileIndexY))
				{
					*wallX = (float)tileIndexX * m_map->getTileSize() + m_map->getTileSize();
					return true;
				}

				if (checkedTile.y >= topLeft.y)
					break;
			}
		}

		return false;
	}

	bool Body::collidesWithRightWall(const glm::vec2& oldPosition, const glm::vec2& position, float* wallX) const
	{
		glm::vec2 oldCenter = oldPosition + m_AABBOffset;
		glm::vec2 center = position + m_AABBOffset;

		glm::vec2 oldBottomRight = m_AABB.getSensorRight(oldCenter).start;
		glm::vec2 newBottomRight = m_AABB.getSensorRight(center).start;
		glm::vec2 newTopRight = m_AABB.getSensorRight(center).end;

		int endX = m_map->getMapTileXAtPoint(newBottomRight.x);
		int begX = std::max(m_map->getMapTileXAtPoint(oldBottomRight.x) + 1, endX);
		int dist = std::max(abs(endX - begX), 1);

		int tileIndexY;

		for (int tileIndexX = begX; tileIndexX <= endX; ++tileIndexX)
		{
			glm::vec2 bottomRight = glm::mix(newBottomRight, oldBottomRight, (float)abs(endX - tileIndexX) / dist);
			glm::vec2 topRight = glm::vec2(bottomRight.x, bottomRight.y + (m_AABB.halfDimension.y - m_AABB.sensorOffset) * 2.0f);

			for (glm::vec2 checkedTile = bottomRight; ; checkedTile.y += m_map->getTileSize())
			{
				checkedTile.y = std::min(checkedTile.y, topRight.y);

				tileIndexY = m_map->getMapTileYAtPoint(checkedTile.y);

				if (m_map->isObstacle(tileIndexX, tileIndexY))
				{
					*wallX = (float)tileIndexX * m_map->getTileSize();
					return true;
				}

				if (checkedTile.y >= topRight.y)
					break;
			}
		}

		return false;
	}
}