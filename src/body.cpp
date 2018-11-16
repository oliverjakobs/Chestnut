#include "body.h"

#include <algorithm>   

using namespace chestnut2D;

AABB::AABB()
	: center(glm::vec2()), halfDimension(glm::vec2())
{
	sensorOffset = 0.0f;
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
	return Line(cen.x - halfDimension.x + sensorOffset, cen.y - halfDimension.y - sensorOffset, cen.x + halfDimension.x - sensorOffset, cen.y - halfDimension.y - sensorOffset);
}

Line AABB::getSensorTop(const glm::vec2& cen) const
{
	return Line(cen.x - halfDimension.x + sensorOffset, cen.y + halfDimension.y + sensorOffset, cen.x + halfDimension.x - sensorOffset, cen.y + halfDimension.y + sensorOffset);
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

	m_collidesBottom = false;
	m_collidesLeft = false;
	m_collidesRight = false;
}

Body::~Body()
{

}

void Body::setMap(TileMap* map)
{
	m_map = map;
}

void Body::update(float deltaTime)
{
	m_position.y += m_velocity.y * deltaTime;

	float groundY = 0.0f;
	if (m_velocity.y <= 0.0f && checkBottom(m_position, &groundY))
	{
		m_position.y = groundY + m_AABB.halfDimension.y - m_AABBOffset.y;
		m_collidesBottom = true;
	}
	else
		m_collidesBottom = false;

	groundY = 0.0f;
	if (m_velocity.y >= 0.0f && checkTop(m_position, &groundY))
	{
		m_position.y = groundY - m_AABB.halfDimension.y - m_AABBOffset.y;
		m_collidesTop = true;
	}
	else
		m_collidesTop = false;

	m_position.x += m_velocity.x * deltaTime;

	float wallX = 0.0f;
	if (m_velocity.x <= 0.0f && checkLeft(m_position, &wallX))
	{
		m_position.x = wallX + m_AABB.halfDimension.x - m_AABBOffset.x;
		m_collidesLeft = true;
	}
	else
		m_collidesLeft = false;

	wallX = 0.0f;
	if (m_velocity.x >= 0.0f && checkRight(m_position, &wallX))
	{
		m_position.x = wallX - m_AABB.halfDimension.x - m_AABBOffset.x;
		m_collidesRight = true;
	}
	else
		m_collidesRight = false;

	m_AABB.center = m_position + m_AABBOffset;
}

void Body::draw() const
{
	/*Line sensor = m_AABB.getSensorTop(m_AABB.center);

	for (auto& t : m_map->getAdjacentTiles(sensor.start, sensor.end - sensor.start))
	{
		Renderer::drawRect(t->posititon.x, t->posititon.y, m_map->getTileSize(), m_map->getTileSize(), t->type == Block ? RED : GREEN);
	}*/

	Renderer::drawRect(Rect(m_AABB.center - m_AABB.halfDimension, m_AABB.halfDimension * 2.0f), (m_collidesBottom || m_collidesTop || m_collidesLeft || m_collidesRight) ? BLUE : GREEN);

	Renderer::drawLine(m_AABB.getSensorBottom(m_AABB.center).start, m_AABB.getSensorBottom(m_AABB.center).end, RED);
	Renderer::drawLine(m_AABB.getSensorTop(m_AABB.center).start, m_AABB.getSensorTop(m_AABB.center).end, RED);
	Renderer::drawLine(m_AABB.getSensorLeft(m_AABB.center).start, m_AABB.getSensorLeft(m_AABB.center).end, RED);
	Renderer::drawLine(m_AABB.getSensorRight(m_AABB.center).start, m_AABB.getSensorRight(m_AABB.center).end, RED);

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

bool Body::checkBottom(const glm::vec2& position, float* groundY) const
{
	Line sensor = m_AABB.getSensorBottom(position + m_AABBOffset);

	for (auto& t : m_map->getAdjacentTiles(sensor.start, sensor.end - sensor.start))
	{
		if (t->type == Block)
		{
			*groundY = t->posititon.y + m_map->getTileSize();
			return true;
		}
	}

	return false;
}

bool Body::checkTop(const glm::vec2& position, float* groundY) const
{
	Line sensor = m_AABB.getSensorTop(position + m_AABBOffset);

	for (auto& t : m_map->getAdjacentTiles(sensor.start, sensor.end - sensor.start))
	{
		if (t->type == Block)
		{
			*groundY = t->posititon.y;
			return true;
		}
	}

	return false;
}

bool Body::checkLeft(const glm::vec2& position, float* wallX) const
{
	Line sensor = m_AABB.getSensorLeft(position + m_AABBOffset);

	for (auto& t : m_map->getAdjacentTiles(sensor.start, sensor.end - sensor.start))
	{
		if (t->type == Block)
		{
			*wallX = t->posititon.x + m_map->getTileSize();
			return true;
		}
	}

	return false;
}

bool Body::checkRight(const glm::vec2& position, float* wallX) const
{
	Line sensor = m_AABB.getSensorRight(position + m_AABBOffset);

	for (auto& t : m_map->getAdjacentTiles(sensor.start, sensor.end - sensor.start))
	{
		if (t->type == Block)
		{
			*wallX = t->posititon.x;
			return true;
		}
	}

	return false;
}