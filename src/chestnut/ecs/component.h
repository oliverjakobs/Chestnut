#pragma once

#include <cstdlib>

#include "entity.h"

namespace chst
{
	class Component
	{
	protected:
		Entity* m_entity;

		bool m_active;
	public:
		Component() : m_entity(nullptr), m_active(true) {}
				
		virtual bool setEntity(Entity* e) { m_entity = e; return m_entity != nullptr; }
		virtual Entity* getEntity() { return m_entity; }

		virtual void setActive(bool a) { m_active = a; }
		virtual bool isActive() { return m_active; }

		virtual void handleInput(Input* input) = 0;
		virtual void update(float deltaTime) = 0;
		virtual void draw() const = 0;
		virtual void debugDraw() const {};
	};

	template<class T> T* getComponent(const Entity* e)
	{
		T* comp = nullptr;
		if (e == nullptr)
			return comp;

		std::vector<Component*> components = e->getComponents();
		std::vector<Component*>::const_iterator it = components.begin();
		while (it != components.end())
		{
			comp = dynamic_cast<T*>(*it);
			if (comp != nullptr)
			{
				break;
			}
			it++;
		}

		return comp;
	}
}