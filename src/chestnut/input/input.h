#pragma once

#include "gl.h"
#include "glm\glm.hpp"

namespace chst
{
	class Input
	{
	private:
		bool m_keys[GLFW_KEY_LAST];
		bool m_prevKeys[GLFW_KEY_LAST];

		bool m_mouseButtons[GLFW_MOUSE_BUTTON_LAST];
		bool m_prevMouseButtons[GLFW_MOUSE_BUTTON_LAST];

		float m_mouseX, m_mouseY;

		int m_lastScroll;
		int m_mouseScroll;
	public:
		Input();
		~Input();

		void update();

		bool keyDown(unsigned int key) const;
		bool keyHit(unsigned int key) const;
		bool keyUp(unsigned int key) const;

		bool mouseButtonDown(unsigned int button) const;
		bool mouseButtonHit(unsigned int button) const;
		bool mouseButtonUp(unsigned int button) const;

		void setMousePosition(float x, float y);
		glm::vec2 getMousePosition() const;

		int getMouseScroll() const;

		void setCursorMode(int value);

		friend void mouseScrollCallback(GLFWwindow* window, double x, double y);
	};
}

