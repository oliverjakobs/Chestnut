#include "physicscomponent.h"

namespace chst
{
	PhysicsComponent::PhysicsComponent(Body* body)
		: m_body(body), m_direction(RIGHT)
	{
		m_isMoving = false;
		m_isJumping = false;
	}

	PhysicsComponent::~PhysicsComponent()
	{

	}

	void PhysicsComponent::handleInput(Input* input)
	{
	}

	void PhysicsComponent::update(float deltaTime)
	{
		m_entity->setPosition(m_body->getPosition());
	}

	void PhysicsComponent::draw() const
	{

	}

	void PhysicsComponent::debugDraw() const
	{
		m_body->draw();
	}

	void PhysicsComponent::setVelocity(const glm::vec2& vel)
	{
		if (vel.x < 0.0f)
			m_direction = LEFT;
		else if (vel.x > 0.0f)
			m_direction = RIGHT;

		if (vel.x == 0.0f)
			m_isMoving = false;
		else
			m_isMoving = true;

		if (vel.y > 0.0f)
			m_isJumping = true;
		else
			m_isJumping = false;
		
		m_body->setVelocity(vel);
	}

	glm::vec2 PhysicsComponent::getVelocity() const
	{
		return m_body->getVelocity();
	}

	void PhysicsComponent::drop()
	{
		m_body->drop();
	}

	Direction PhysicsComponent::getDirection() const
	{
		return m_direction;
	}

	Body* PhysicsComponent::getBody() const
	{
		return m_body;
	}

	bool PhysicsComponent::isOnFloor() const
	{
		return m_body->collidesBottom();
	}

	bool PhysicsComponent::isJumping() const
	{
		return m_isJumping;
	}

	bool PhysicsComponent::isFalling() const
	{
		return !(isOnFloor() || isJumping());
	}

	bool PhysicsComponent::isMoving() const
	{
		return m_isMoving;
	}
}