#pragma once

#include "Api.h"

#include "Chestnut/Events/WindowEvent.h"
#include "Chestnut/Events/MouseEvent.h"
#include "Chestnut/Events/KeyEvent.h"

#include "Chestnut/Core/Timestep.h"

namespace chst
{
	class Layer
	{
	protected:
		std::string m_name;

	public:
		Layer(const std::string& name = "Layer") : m_name(name) {}
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnUpdate(Timestep ts) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_name; }
	};
}