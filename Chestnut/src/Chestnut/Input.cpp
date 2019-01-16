#include "chstpch.h"
#include "Input.h"

namespace chst
{
	Input::Input()
	{
		for (int i = 0; i < GLFW_KEY_LAST; i++)
		{
			m_keys[i] = { false, false };
		}
	}

	Input::~Input()
	{
	}

	bool Input::OnKeyPressed(KeyPressedEvent& e)
	{
		Get()->m_keys[e.getKeyCode()] = { true, false };

		return true;
	}

	bool Input::OnKeyReleased(KeyReleasedEvent& e)
	{
		Get()->m_keys[e.getKeyCode()] = { false, true };

		return true;
	}

	void Input::OnUpdate()
	{
		for (auto& key : Get()->m_keys)
		{
			key.second.prev = key.second.pressed;
		}
	}

	bool Input::KeyPressed(unsigned int key)
	{
		if (key >= GLFW_KEY_LAST || key == GLFW_KEY_UNKNOWN)
			return false;
						
		return Get()->m_keys[key].pressed && !Get()->m_keys[key].prev;
	}

	bool Input::KeyReleased(unsigned int key)
	{
		if (key >= GLFW_KEY_LAST || key == GLFW_KEY_UNKNOWN)
			return false;

		//return (Get()->m_keys[key] && !Get()->m_prevKeys[key]);
	}

	KeyState Input::getKeyState(unsigned int key)
	{
		return Get()->m_keys[key];
	}
}