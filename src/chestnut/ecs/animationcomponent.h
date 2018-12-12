#pragma once

#include "graphics\animation.h"
#include "physicscomponent.h"

#include <map>

namespace chst
{
	class Image;

	typedef std::pair<std::string, Animation*> AnimationDef;

	class AnimationComponent : public Component
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

		void handleInput(Input* input) override;
		void update(float deltaTime) override;
		void draw() const override;
	};
}