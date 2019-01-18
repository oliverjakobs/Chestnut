#pragma once

#include "Component.h"
#include "Chestnut\Physics\Body.h"

namespace chst
{
	enum Direction
	{
		LEFT,
		RIGHT
	};

	class CHESTNUT_API PhysicsComponent : public Component
	{
	private:
		Body* m_body;

		bool m_isMoving;
		bool m_isJumping;
		
		Direction m_direction;
	public: 
		PhysicsComponent(Body* body);
		~PhysicsComponent();
		
		void onInput() override;
		void onUpdate() override;
		void onRender() const override;
		void onRenderDebug() const override;

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