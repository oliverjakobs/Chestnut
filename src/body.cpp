#include "body.h"

#include <algorithm>   

using namespace chst;

Body::Body(float x, float y, float w, float h)
	: m_position(glm::vec2(x, y)), m_halfDimension(glm::vec2(w, h) / 2.0f)
{
	m_velocity = glm::vec2();
	sensorOffset = 0.02f;

	m_collidesBottom = false;
	m_collidesTop = false;
	m_collidesLeft = false;
	m_collidesRight = false;
	m_onSlope = 0;

	gravityScale = 1.0f;

	m_drop = false;
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
	glm::vec2 gravity = glm::vec2(0.0f, -9.8f);

	if (m_onSlope && m_velocity.y <= 0.0f)
		gravityScale = 20.0f;
	else
		gravityScale = 1.0f;

	m_velocity += gravity * gravityScale * deltaTime;

	m_offsetHorizontal = glm::vec2(sensorOffset, m_onSlope ? 0.08f : 0.01f);
	m_offsetVertical = glm::vec2(0.01f, sensorOffset);

	moveX(m_velocity.x * deltaTime);
	moveY(m_velocity.y * deltaTime);

	m_drop = false;
}

void Body::draw() const
{
	Renderer::drawRect(Rect(m_position - glm::vec2(m_halfDimension.x, 0.0f), m_halfDimension * 2.0f), m_onSlope ? BLUE : GREEN);

	Renderer::drawLine(getSensorBottom(m_position + glm::vec2(0.0f, m_halfDimension.y), m_offsetVertical), RED);
	Renderer::drawLine(getSensorTop(m_position + glm::vec2(0.0f, m_halfDimension.y), m_offsetVertical), RED);
	Renderer::drawLine(getSensorLeft(m_position + glm::vec2(0.0f, m_halfDimension.y), m_offsetHorizontal), RED);
	Renderer::drawLine(getSensorRight(m_position + glm::vec2(0.0f, m_halfDimension.y), m_offsetHorizontal), RED);
	
	/*Line sensor = getSensorBottom(m_position + glm::vec2(0.0f, m_halfDimension.y), glm::vec2(sensorOffset));

	auto tiles = m_map->getAdjacentTiles(sensor.start, sensor.end - sensor.start + glm::vec2(0.0f, sensorOffset));

	for (auto& t : tiles)
	{
		Renderer::fillRect(t->position.x, t->position.y, m_map->getTileSize(), m_map->getTileSize(), blendColor(CYAN, 0.2f));
	}*/
	
	Renderer::fillCircle(m_position, 0.04f, BLACK);
}

void Body::setPosition(const glm::vec2& pos)
{
	m_position = pos;
}

void Body::setVelocity(const glm::vec2 & vel)
{
	m_velocity = vel;
}

void Body::drop()
{
	m_drop = true;
}

glm::vec2 Body::getVelocity() const
{
	return m_velocity;
}

bool Body::collidesBottom() const
{
	return m_collidesBottom;
}

void Body::moveX(float x)
{
	glm::vec2 oldPosition = m_position;

	m_position.x += x;

	float wallX = 0.0f;
	if (m_velocity.x <= 0.0f && checkLeft(m_position, oldPosition, &wallX))
	{
		m_position.x = wallX + m_halfDimension.x;
		m_velocity.x = 0.0f;
		m_collidesLeft = true;
	}
	else
		m_collidesLeft = false;

	wallX = 0.0f;
	if (m_velocity.x >= 0.0f && checkRight(m_position, oldPosition, &wallX))
	{
		m_position.x = wallX - m_halfDimension.x;
		m_velocity.x = 0.0f;
		m_collidesRight = true;
	}
	else
		m_collidesRight = false;
}

void Body::moveY(float y)
{
	glm::vec2 oldPosition = m_position;
	m_position.y += y;

	m_onSlope = false;

	float groundY = 0.0f;
	if (m_velocity.y <= 0.0f && checkBottom(m_position, oldPosition, &groundY, &m_onSlope))
	{
		m_position.y = groundY;
		m_velocity.y = 0.0f;
		m_collidesBottom = true;
	}
	else
		m_collidesBottom = false;

	groundY = 0.0f;
	if (m_velocity.y >= 0.0f && checkTop(m_position, oldPosition, &groundY))
	{
		m_position.y = groundY - (2.0f * m_halfDimension.y);
		m_velocity.y = 0.0f;
		m_collidesTop = true;
	}
	else
		m_collidesTop = false;
}

bool Body::checkBottom(const glm::vec2& position, const glm::vec2& oldPosition, float* groundY, bool* onSlope)
{
	Line sensor = getSensorBottom(position + glm::vec2(0.0f, m_halfDimension.y), m_offsetVertical);
	Line oldSensor = getSensorBottom(oldPosition + glm::vec2(0.0f, m_halfDimension.y), m_offsetVertical);

	botSensor = Rect(sensor.start, oldSensor.end - sensor.start + glm::vec2(0.0f, sensorOffset));

	auto tiles = m_map->getAdjacentTiles(sensor.start, oldSensor.end - sensor.start + glm::vec2(0.0f, sensorOffset));

	std::sort(tiles.begin(), tiles.end(), [](const Tile* t1, const Tile* t2)
	{
		if (t1->position.y == t2->position.y)
			return t1->type < t2->type;

		return t1->position.y > t2->position.y;
	});

	for (auto& t : tiles)
	{
		if (t->type == Solid && !m_onSlope)
		{
			*groundY = t->position.y + m_map->getTileSize();
			return true;
		}
		else if (t->type == SlopeLeft)
		{
			float x = m_position.x - m_halfDimension.x - t->position.x;

			*groundY = t->position.y + m_map->getTileSize() - x;
			*onSlope = true;
			return true;
		}
		else if (t->type == SlopeRight)
		{
			float x = m_position.x + m_halfDimension.x - t->position.x;

			*groundY = t->position.y + x;
			*onSlope = true;
			return true;
		}
		else if (t->type == OneWay && !m_drop)
		{
			*groundY = t->position.y + m_map->getTileSize();
			if (oldPosition.y >= *groundY)
				return true;
		}
	}

	return false;
}

bool Body::checkTop(const glm::vec2& position, const glm::vec2& oldPosition, float* groundY) const
{
	Line sensor = getSensorTop(position + glm::vec2(0.0f, m_halfDimension.y), m_offsetVertical);
	Line oldSensor = getSensorTop(oldPosition + glm::vec2(0.0f, m_halfDimension.y), m_offsetVertical);

	auto tiles = m_map->getAdjacentTiles(oldSensor.start, sensor.end - oldSensor.start);

	std::sort(tiles.begin(), tiles.end(), [](const Tile* t1, const Tile* t2)
	{
		return t1->position.y < t2->position.y;
	});

	for (auto& t : tiles)
	{
		if (t->type == Solid)
		{
			*groundY = t->position.y;
			return true;
		}
	}

	return false;
}

bool Body::checkLeft(const glm::vec2& position, const glm::vec2& oldPosition, float* wallX) const
{
	Line sensor = getSensorLeft(position + glm::vec2(0.0f, m_halfDimension.y), m_offsetHorizontal);
	Line oldSensor = getSensorLeft(oldPosition + glm::vec2(0.0f, m_halfDimension.y), m_offsetHorizontal);

	auto tiles = m_map->getAdjacentTiles(sensor.start, oldSensor.end - sensor.start);

	std::sort(tiles.begin(), tiles.end(), [](const Tile* t1, const Tile* t2)
	{
		return t1->position.x > t2->position.x;
	});

	for (auto& t : tiles)
	{
		if (t->type == Solid)
		{
			*wallX = t->position.x + m_map->getTileSize();
			return true;
		}
	}

	return false;
}

bool Body::checkRight(const glm::vec2& position, const glm::vec2& oldPosition, float* wallX) const
{
	Line sensor = getSensorRight(position + glm::vec2(0.0f, m_halfDimension.y), m_offsetHorizontal);
	Line oldSensor = getSensorRight(oldPosition + glm::vec2(0.0f, m_halfDimension.y), m_offsetHorizontal);

	auto tiles = m_map->getAdjacentTiles(oldSensor.start, sensor.end - oldSensor.start);

	std::sort(tiles.begin(), tiles.end(), [](const Tile* t1, const Tile* t2)
	{
		return t1->position.x < t2->position.x;
	});

	for (auto& t : tiles)
	{
		if (t->type == Solid)
		{
			*wallX = t->position.x;
			return true;
		}
	}

	return false;
}

Line Body::getSensorBottom(const glm::vec2& cen, const glm::vec2& offset) const
{
	return Line(cen.x - m_halfDimension.x + offset.x, cen.y - m_halfDimension.y - offset.y, cen.x + m_halfDimension.x - offset.x, cen.y - m_halfDimension.y - offset.y);
}

Line Body::getSensorTop(const glm::vec2& cen, const glm::vec2& offset) const
{
	return Line(cen.x - m_halfDimension.x + 0.01f, cen.y + m_halfDimension.y + sensorOffset, cen.x + m_halfDimension.x - 0.01f, cen.y + m_halfDimension.y + sensorOffset);
}

Line Body::getSensorLeft(const glm::vec2& cen, const glm::vec2& offset) const
{
	return Line(cen.x - m_halfDimension.x - offset.x, cen.y - m_halfDimension.y + offset.y, cen.x - m_halfDimension.x - offset.x, cen.y + m_halfDimension.y - offset.y);
}

Line Body::getSensorRight(const glm::vec2& cen, const glm::vec2& offset) const
{
	return Line(cen.x + m_halfDimension.x + offset.x, cen.y - m_halfDimension.y + offset.y, cen.x + m_halfDimension.x + offset.x, cen.y + m_halfDimension.y - offset.y);
}