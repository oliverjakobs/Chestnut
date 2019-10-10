#pragma once

#include "Chestnut/Events/WindowEvent.h"
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
	};
}