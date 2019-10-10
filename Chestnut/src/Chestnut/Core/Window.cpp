#include "chstpch.h"
#include "Window.h"

#include "Chestnut/Utility/Debugger.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace chst
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		DEBUG_ERROR("[GLFW] Error ({0}): {1}", error, description);
	}

	Window::Window(const std::string& title, uint32_t width, uint32_t height)
	{
		Init(title, width, height);
	}

	Window::~Window()
	{
		Shutdown();
	}

	void Window::Init(const std::string& title, uint32_t width, uint32_t height)
	{
		m_data.Title = title;
		m_data.Width = width;
		m_data.Height = height;

		DEBUG_INFO("Creating window {0} ({1}, {2})", title, width, height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			DEBUG_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_window = glfwCreateWindow((int)width, (int)height, title.c_str(), nullptr, nullptr);

		glfwMakeContextCurrent(m_window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		DEBUG_ASSERT(status, "Failed to initialize Glad!");

		DEBUG_INFO("OpenGL Info:");
		DEBUG_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		DEBUG_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		DEBUG_INFO("Version: {0}", glGetString(GL_VERSION));

		glfwSetWindowUserPointer(m_window, &m_data);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			data.EventCallback(WindowResizeEvent(width, height));
		});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.EventCallback(WindowCloseEvent());
		});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
				data.EventCallback(KeyPressedEvent(key, 0));
				break;
			case GLFW_RELEASE:
				data.EventCallback(KeyReleasedEvent(key));
				break;
			case GLFW_REPEAT:
				data.EventCallback(KeyPressedEvent(key, 1));
				break;
			}
		});

		glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.EventCallback(KeyTypedEvent(keycode));
		});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
				data.EventCallback(MouseButtonPressedEvent(button));
				break;
			case GLFW_RELEASE:
				data.EventCallback(MouseButtonReleasedEvent(button));
				break;
			}
		});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.EventCallback(MouseScrolledEvent((float)xOffset, (float)yOffset));
		});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.EventCallback(MouseMovedEvent((float)xPos, (float)yPos));
		});
	}

	void Window::Shutdown()
	{
		glfwDestroyWindow(m_window);

		if (s_GLFWInitialized)
		{
			glfwTerminate();
			s_GLFWInitialized = false;
		}
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void Window::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_data.VSync = enabled;
	}

	bool Window::IsVSync() const
	{
		return m_data.VSync;
	}
}