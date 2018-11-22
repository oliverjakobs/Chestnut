#include "input.h"

#include "graphics.h"
#include "game.h"

namespace chst
{
	Input::Input()
	{
		for (int i = 0; i < GLFW_KEY_LAST; i++)
		{
			m_keys[i] = false;
			m_prevKeys[i] = false;
		}

		for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++)
		{
			m_mouseButtons[i] = false;
			m_prevMouseButtons[i] = false;
		}

		m_mouseScroll = 0;

		glfwSetScrollCallback(Renderer::getContext(), mouseScrollCallback);
	}

	Input::~Input()
	{

	}

	void Input::update()
	{
		for (int i = 0; i < GLFW_KEY_LAST; i++)
		{
			m_prevKeys[i] = m_keys[i];
			m_keys[i] = (glfwGetKey(Renderer::getContext(), i) == GLFW_PRESS);
		}

		for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++)
		{
			m_prevMouseButtons[i] = m_mouseButtons[i];
			m_mouseButtons[i] = (glfwGetMouseButton(Renderer::getContext(), i) == GLFW_PRESS);
		}

		double x, y;
		glfwGetCursorPos(Renderer::getContext(), &x, &y);
		
		m_mouseX = static_cast<float>(x);
		m_mouseY = static_cast<float>(y);

		m_mouseScroll = m_lastScroll;
		m_lastScroll = 0;
	}

	bool Input::keyDown(unsigned int key) const
	{
		if (key >= GLFW_KEY_LAST || key == GLFW_KEY_UNKNOWN)
			return false;

		return m_keys[key];
	}

	bool Input::keyHit(unsigned int key) const
	{
		if (key >= GLFW_KEY_LAST || key == GLFW_KEY_UNKNOWN)
			return false;

		return (m_keys[key] && !m_prevKeys[key]);
	}

	bool Input::keyUp(unsigned int key) const
	{
		if (key >= GLFW_KEY_LAST || key == GLFW_KEY_UNKNOWN)
			return false;

		return (m_prevKeys[key] && !m_keys[key]);
	}

	bool Input::mouseButtonDown(unsigned int button) const
	{
		if (button >= GLFW_MOUSE_BUTTON_LAST)
			return false;

		return m_mouseButtons[button];
	}

	bool Input::mouseButtonHit(unsigned int button) const
	{
		if (button >= GLFW_MOUSE_BUTTON_LAST)
			return false;

		return (m_mouseButtons[button] && !m_prevMouseButtons[button]);
	}

	bool Input::mouseButtonUp(unsigned int button) const
	{
		if (button >= GLFW_MOUSE_BUTTON_LAST)
			return false;

		return (m_prevMouseButtons[button] && !m_mouseButtons[button]);
	}

	void Input::setMousePosition(float x, float y)
	{
		m_mouseX = x;
		m_mouseY = y;

		glfwSetCursorPos(Renderer::getContext(), m_mouseX, m_mouseY);
	}
	
	glm::vec2 Input::getMousePosition() const
	{
		return glm::vec2(m_mouseX, m_mouseY);
	}

	int Input::getMouseScroll() const
	{
		return m_mouseScroll;
	}
	
	void Input::setCursorMode(int value)
	{
		glfwSetInputMode(Renderer::getContext(), GLFW_CURSOR, value);
	}

	void mouseScrollCallback(GLFWwindow* window, double x, double y)
	{
		Input* in = (static_cast<Game*>(glfwGetWindowUserPointer(Renderer::getContext())))->getInput();

		if (in != nullptr)
		{
			in->m_lastScroll = static_cast<int>(y);
		}
	}
}