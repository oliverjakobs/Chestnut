#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "Chestnut\Events.h"
#include "Chestnut\Patterns\Singelton.h"

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
	public:
		Input();
		~Input();

		static bool OnKeyPressed(KeyPressedEvent& e);
		static bool OnKeyReleased(KeyReleasedEvent& e);
		static void OnUpdate();

		static bool KeyDown(unsigned int key);
		static bool KeyPressed(unsigned int key);
		static bool KeyReleased(unsigned int key);

		static KeyState getKeyState(unsigned int key);
	};
}