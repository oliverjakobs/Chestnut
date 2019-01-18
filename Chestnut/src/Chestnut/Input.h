#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "Chestnut\Events.h"
#include "Chestnut\Patterns\Singelton.h"

#include "glm\glm.hpp"

namespace chst
{
	struct KeyState
	{
		bool pressed;
		bool prev;

		std::string toString() const
		{
			std::stringstream ss;
			ss << "KeyState: " << pressed << ", " << prev;
			return ss.str();
		}
	};

	class CHESTNUT_API Input : private Singleton<Input>
	{
	private:
		std::map<unsigned int, KeyState> m_keys;
		std::map<unsigned int, KeyState> m_mouseButtons;

		glm::vec2 m_mousePos;
	public:
		Input();
		~Input();

		static bool OnKeyPressed(KeyPressedEvent& e);
		static bool OnKeyReleased(KeyReleasedEvent& e);
		static bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		static bool OnMouseButtonReleased(MouseButtonReleasedEvent& e);
		static bool OnMouseScrolled(MouseScrolledEvent& e);
		static bool OnMouseMoved(MouseMovedEvent& e);
		static void OnUpdate();

		static bool KeyDown(unsigned int key);
		static bool KeyPressed(unsigned int key);
		static bool KeyReleased(unsigned int key);

		static bool MouseButtonDown(unsigned int button);
		static bool MouseButtonPressed(unsigned int button);
		static bool MouseButtonReleased(unsigned int button);

		static glm::vec2 MousePosition();

		static KeyState GetKeyState(unsigned int key);
		static KeyState GetMouseButtonState(unsigned int key);
	};
}