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

		for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++)
		{
			m_mouseButtons[i] = { false, false };
		}

		m_mousePos = glm::vec2();
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

	bool Input::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		Get()->m_mouseButtons[e.getMouseButton()] = { true, false };

		return true;
	}

	bool Input::OnMouseButtonReleased(MouseButtonReleasedEvent& e)
	{
		Get()->m_mouseButtons[e.getMouseButton()] = { false, true };

		return true;
	}

	bool Input::OnMouseScrolled(MouseScrolledEvent& e)
	{
		return true;
	}

	bool Input::OnMouseMoved(MouseMovedEvent& e)
	{
		Get()->m_mousePos = glm::vec2(e.getX(), e.getY());

		return true;
	}

	void Input::OnUpdate()
	{
		for (auto& key : Get()->m_keys)
		{
			key.second.prev = key.second.pressed;
		}

		for (auto& button : Get()->m_mouseButtons)
		{
			button.second.prev = button.second.pressed;
		}
	}

	bool Input::KeyDown(unsigned int key)
	{
		if (key >= GLFW_KEY_LAST || key == GLFW_KEY_UNKNOWN)
			return false;

		return Get()->m_keys[key].pressed;
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

		return (Get()->m_keys[key].prev && !Get()->m_keys[key].pressed);
	}

	bool Input::MouseButtonDown(unsigned int button)
	{
		if (button >= GLFW_MOUSE_BUTTON_LAST || button == GLFW_KEY_UNKNOWN)
			return false;

		return Get()->m_mouseButtons[button].pressed;
	}

	bool Input::MouseButtonPressed(unsigned int button)
	{
		if (button >= GLFW_MOUSE_BUTTON_LAST || button == GLFW_KEY_UNKNOWN)
			return false;

		return Get()->m_mouseButtons[button].pressed && !Get()->m_mouseButtons[button].prev;
	}

	bool Input::MouseButtonReleased(unsigned int button)
	{
		if (button >= GLFW_MOUSE_BUTTON_LAST || button == GLFW_KEY_UNKNOWN)
			return false;

		return Get()->m_mouseButtons[button].pressed;
	}

	glm::vec2 Input::MousePosition()
	{
		return Get()->m_mousePos;
	}

	KeyState Input::GetKeyState(unsigned int key)
	{
		return Get()->m_keys[key];
	}

	KeyState Input::GetMouseButtonState(unsigned int key)
	{
		return Get()->m_mouseButtons[key];
	}
}