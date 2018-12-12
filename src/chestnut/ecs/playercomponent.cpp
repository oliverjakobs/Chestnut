#include "playercomponent.h"

#include "tools\util\utils.h"

namespace chst
{
	PlayerComponent::PlayerComponent()
	{
	}

	PlayerComponent::~PlayerComponent()
	{
	}

	bool PlayerComponent::setEntity(Entity* e)
	{
		m_physComp = getComponent<PhysicsComponent>(e);

		if (m_physComp == nullptr)
		{
			DEBUG_MESSAGE("No Physics Component");
			return false;
		}

		m_animComp = getComponent<AnimationComponent>(e);

		if (m_animComp == nullptr)
		{
			DEBUG_MESSAGE("No Animation Component");
			return false;
		}


		m_entity = e;
		return m_entity != nullptr;
	}

	void PlayerComponent::handleInput(Input* input)
	{
		float movementSpeed = 4.0f;
		float jumpPower = 8.0f;

		glm::vec2 velocity = glm::vec2(0.0f, m_physComp->getVelocity().y);

		if (input->keyDown(GLFW_KEY_A))
			velocity.x += -movementSpeed;
		if (input->keyDown(GLFW_KEY_D))
			velocity.x += movementSpeed;

		if (input->keyDown(GLFW_KEY_SPACE) && m_physComp->isOnFloor())
			velocity.y = jumpPower;
		else if (input->keyUp(GLFW_KEY_SPACE))
			if (m_physComp->getVelocity().y > 0)
				velocity.y = (m_physComp->getVelocity().y * 0.5f);

		m_physComp->setVelocity(velocity);

		if (input->keyDown(GLFW_KEY_S))
			m_physComp->drop();
	}

	void PlayerComponent::update(float deltaTime)
	{
		if (m_physComp->getDirection() == LEFT)
			m_animComp->flip(FLIP_HORIZONTAL);
		else
			m_animComp->flip(FLIP_NONE);

		if (m_physComp->isJumping())
		{
			m_animComp->play("jump");
		}
		else if (m_physComp->isFalling())
		{
			m_animComp->play("fall");
		}
		else
		{
			if (m_physComp->isMoving())
				m_animComp->play("walk");
			else
				m_animComp->play("idle");
		}
	}

	void PlayerComponent::draw() const
	{
	}
}