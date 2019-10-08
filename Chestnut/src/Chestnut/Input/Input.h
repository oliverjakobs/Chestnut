#pragma once

#include "Chestnut/Core/Core.h"

#include "KeyCodes.h"
#include <glm/glm.hpp>

namespace chst
{
	class Input
	{
	public:
		static bool KeyPressed(int keycode);
		static bool KeyReleased(int keycode);

		static bool MousePressed(int button);
		static bool MouseReleased(int button);

		static glm::vec2 MousePosition();
		static float MouseX();
		static float MouseY();
	};
}