#pragma once

#include "physicscomponent.h"
#include "animationcomponent.h"

namespace chst
{	
	class PlayerComponent : public Component
	{
	private:
		PhysicsComponent* m_physComp;
		AnimationComponent* m_animComp;
	public:
		PlayerComponent();
		~PlayerComponent();

		bool setEntity(Entity* e) override;

		void handleInput(Input* input) override;
		void update(float deltaTime) override;
		void draw() const override;
	};
}