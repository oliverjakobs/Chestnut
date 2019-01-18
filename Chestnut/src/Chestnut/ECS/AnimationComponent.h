#pragma once

#include "Chestnut\Graphics\Animation.h"
#include "PhysicsComponent.h"

namespace chst
{
	class Image;

	typedef std::pair<std::string, Animation*> AnimationDef;

	class CHESTNUT_API AnimationComponent : public Component
	{
	private:
		std::map<std::string, Animation*> m_animations;
		Animation* m_currentAnimation;
		std::string m_currentName;
				
		Image* m_sprite;
		PhysicsComponent* m_physComp;
	public:
		AnimationComponent(Image* sprite, std::map<std::string, Animation*> animations);
		~AnimationComponent();

		void flip(RenderFlip flip);
		void play(const std::string anim);

		bool setEntity(Entity* e) override;

		void onInput() override;
		void onUpdate() override;
		void onRender() const override;
	};
}