#include "chstpch.h"
#include "AnimationComponent.h"

#include "Chestnut\Graphics\Renderer.h"
#include "Chestnut\utils.h"

namespace chst
{
	AnimationComponent::AnimationComponent(Image* sprite, std::map<std::string, Animation*> animations)
	{
		m_sprite = sprite;

		m_currentAnimation = nullptr;
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
			CHST_CORE_WARN("No Physics Component");
			return false;
		}

		m_entity = e;
		return m_entity != nullptr;
	}

	void AnimationComponent::onInput()
	{
	}

	void AnimationComponent::onUpdate()
	{
		if (m_currentAnimation != nullptr)
			m_currentAnimation->step(Timer::GetDeltaTime());
	}

	void AnimationComponent::onRender() const
	{
		float x = m_entity->getPosition().x - m_sprite->getWidth() / 2.0f;
		float y = m_entity->getPosition().y;

		if (m_currentAnimation != nullptr)
			m_sprite->draw(x, y, m_currentAnimation->getFrame());
	}
}