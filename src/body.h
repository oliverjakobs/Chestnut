#pragma once

#include "math\maths.h"
#include "tilemap.h"

using namespace chestnutMath;

class Body
{
private:
	glm::vec2 m_position;
	glm::vec2 m_halfDimension;

	glm::vec2 m_velocity;

	glm::vec2 m_offsetHorizontal;
	glm::vec2 m_offsetVertical;

	Rect botSensor;

	bool m_collidesBottom;
	bool m_collidesTop;
	bool m_collidesLeft;
	bool m_collidesRight;
	bool m_onSlope;

	float gravityScale; 

	bool m_drop;

	float sensorOffset;

	TileMap* m_map;
public:
	Body(float x, float y, float w, float h);
	virtual ~Body();

	void setMap(TileMap* map);

	void update(float deltaTime);
	void draw() const;

	void setPosition(const glm::vec2& pos);
	void setVelocity(const glm::vec2& vel);

	void drop();

	glm::vec2 getVelocity() const;

	bool collidesBottom() const;

private:
	void moveX(float x);
	void moveY(float y);

	bool checkBottom(const glm::vec2& position, const glm::vec2& oldPosition, float* groundY, bool* onSlope);
	bool checkTop(const glm::vec2& position, const glm::vec2& oldPosition, float* groundY) const;
	bool checkLeft(const glm::vec2& position, const glm::vec2& oldPosition, float* wallX) const;
	bool checkRight(const glm::vec2& position, const glm::vec2& oldPosition, float* wallX) const;

	Line getSensorBottom(const glm::vec2& center, const glm::vec2& offset) const;
	Line getSensorTop(const glm::vec2& center, const glm::vec2& offset) const;
	Line getSensorLeft(const glm::vec2& center, const glm::vec2& offset) const;
	Line getSensorRight(const glm::vec2& center, const glm::vec2& offset) const;
};