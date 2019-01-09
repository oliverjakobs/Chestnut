#include "animationcomponent.h"

#include "graphics.h"

#include "tools\util\utils.h"

namespace chst
{
	AnimationComponent::AnimationComponent(Image* sprite, std::map<std::string, Animation*> animations)
	{
		m_sprite = sprite;

		m_animations = animations;
	}

	AnimationComponent::~AnimationComponent()
	{
	}

	void AnimationComponent::flip(RenderFlip flip)
	{
		m_sprite->setRenderFlip(flip);
	}

	void AnimationComponent::play(const std::string anim)
	{
		if (stringCompare(m_currentName, anim))
			return;

		m_currentAnimation = m_animations[anim];

		if (m_currentAnimation != nullptr)
		{
			m_currentAnimation->start();
			m_currentName = anim;
		}
	}

	bool AnimationComponent::setEntity(Entity* e)
	{
		m_physComp = getComponent<PhysicsComponent>(e);

		if (m_physComp == nullptr)
		{
			DEBUG_MESSAGE("No Physics Component");
			return false;
		}

		m_entity = e;
		return m_entity != nullptr;
	}

	void AnimationComponent::handleInput(Input* input)
	{
	}

	void AnimationComponent::update(float deltaTime)
	{
		if (m_currentAnimation != nullptr)
			m_currentAnimation->step(deltaTime);
	}

	void AnimationComponent::draw() const
	{
		float x = m_entity->getPosition().x - m_sprite->getWidth() / 2.0f;
		float y = m_entity->getPosition().y;

		if (m_currentAnimation != nullptr)
			m_sprite->draw(x, y, m_currentAnimation->getFrame());
	}
}