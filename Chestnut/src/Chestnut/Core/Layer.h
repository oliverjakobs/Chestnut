#pragma once

#include "Chestnut/Core/Core.h"
#include "Chestnut/Core/Timestep.h"
#include "Chestnut/Events/Event.h"

namespace chst
{
	class CHST_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}