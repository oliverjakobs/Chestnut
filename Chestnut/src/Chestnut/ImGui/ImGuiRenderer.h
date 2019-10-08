#pragma once

#include "Chestnut/Events/ApplicationEvent.h"
#include "Chestnut/Events/KeyEvent.h"
#include "Chestnut/Events/MouseEvent.h"

namespace chst
{
	class ImGuiRenderer
	{
	public:
		ImGuiRenderer() = default;
		~ImGuiRenderer();

		virtual void Init();
		virtual void Quit();

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}