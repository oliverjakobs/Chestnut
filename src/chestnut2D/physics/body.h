#pragma once

#include "math\maths.h"

namespace chestnut2D
{
	class TileMap;
}

namespace chestnutPhysics
{
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
		Line getSensorLeft(const glm::vec2& center) const;
		Line getSensorRight(const glm::vec2& center) const;
	};

	class Body
	{
	private:
		glm::vec2 m_position;
		glm::vec2 m_oldPosition;

		glm::vec2 m_velocity;
		glm::vec2 m_oldVelocity;

		bool m_onGround;
		bool m_wasOnGround;

		bool m_pushesLeftWall;
		bool m_pushesRightWall;

		AABB m_AABB;
		glm::vec2 m_AABBOffset;

		chestnut2D::TileMap* m_map;
	public:
		Body(float x, float y, float w, float h);
		virtual ~Body();

		void setMap(chestnut2D::TileMap* map);

		void update(float deltaTime);
		void draw() const;

		void setPosition(const glm::vec2& pos);
		void setVelocity(float x, float y);
		void applyVelocity(float x, float y);

		bool hasGround(const glm::vec2& oldPosition, const glm::vec2& position, float* groundY) const; 
		bool collidesWithLeftWall(const glm::vec2& oldPosition, const glm::vec2& position, float* wallX) const;
		bool collidesWithRightWall(const glm::vec2& oldPosition, const glm::vec2& position, float* wallX) const;
	};

}