#pragma once

#include "component.h"
#include "physics.h"

namespace chst
{
	enum Direction
	{
		LEFT,
		RIGHT
	};

	class PhysicsComponent : public Component
	{
	private:
		Body* m_body;

		bool m_isMoving;
		bool m_isJumping;
		
		Direction m_direction;
	public: 
		PhysicsComponent(Body* body);
		~PhysicsComponent();
		
		void handleInput(Input* input) override;
		void update(float deltaTime) override;
		void draw() const override;
		void debugDraw() const override;

		void setVelocity(const glm::vec2& vel);
		glm::vec2 getVelocity() const;

		void drop();

		Direction getDirection() const;
		Body* getBody() const;

		bool isOnFloor() const;

		bool isJumping() const;
		bool isFalling() const;
		bool isMoving() const;
	};
}