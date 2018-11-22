#pragma once

#include "math\maths.h"
#include "tilemap.h"

using namespace chestnutMath;

struct AABB
{
	float sensorOffset;

	glm::vec2 center;
	glm::vec2 halfDimension;

	AABB();
	AABB(const glm::vec2& cen, const glm::vec2& halfDim);

	bool overlaps(const AABB& other) const;

	Line getSensorBottom(const glm::vec2& center) const;
	Line getSensorTop(const glm::vec2& center) const;
	Line getSensorLeft(const glm::vec2& center) const;
	Line getSensorRight(const glm::vec2& center) const;
};

class Body
{
private:
	glm::vec2 m_position;

	glm::vec2 m_velocity;
	glm::vec2 m_targetVelocity;

	bool m_collidesBottom;
	bool m_collidesTop;
	bool m_collidesLeft;
	bool m_collidesRight;

	AABB m_AABB;
	glm::vec2 m_AABBOffset;

	TileMap* m_map;
public:
	Body(float x, float y, float w, float h);
	virtual ~Body();

	void setMap(TileMap* map);

	void update(float deltaTime);
	void draw() const;

	void setPosition(const glm::vec2& pos);
	void setVelocity(float x, float y);
	void setTargetVelocity(float x, float y);

	glm::vec2 getVelocity() const;

	bool collidesBottom() const;

	bool checkBottom(const glm::vec2& position, const glm::vec2& oldPosition, float* groundY) const;
	bool checkTop(const glm::vec2& position, const glm::vec2& oldPosition, float* groundY) const;
	bool checkLeft(const glm::vec2& position, const glm::vec2& oldPosition, float* wallX) const;
	bool checkRight(const glm::vec2& position, const glm::vec2& oldPosition, float* wallX) const;
};