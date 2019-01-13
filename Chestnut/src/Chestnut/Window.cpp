#include "chstpch.h"
#include "Window.h"

namespace chst
{
	static void GLFWErrorCallback(int error, const char* desc)
	{
		CHST_CORE_ERROR("[GLFW]: (%c) %d", error, desc);
	}

	Window::Window(const std::string& title, unsigned int width, unsigned int height)
	{
		m_data.title = title;
		m_data.width = width;
		m_data.height = height;

		int status = glfwInit();
		CHST_CORE_ASSERT(status, "[GLFW] Failed to initialize GLFW");

		glfwSetErrorCallback(GLFWErrorCallback);

		//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		CHST_CORE_INFO("[GLFW] Creating window: %s, %d, %d", title.c_str(), width, height);

		m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		CHST_CORE_ASSERT(m_window, "[GLFW] Failed to create GLFW window");
		glfwMakeContextCurrent(m_window);
		
		status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CHST_CORE_ASSERT(status, "[GLAD] Failed to initialize Glad");

		glfwSetWindowUserPointer(m_window, &m_data);
		setVSync(true);

		// set glfw callbacks
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* win, int w, int h)
		{
			auto data = *(WindowData*)glfwGetWindowUserPointer(win);
			data.width = w;
			data.height = h;

			WindowResizeEvent e(w, h);
			data.eventCallback(e);
		});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
		{
			auto data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent e;
			data.eventCallback(e);
		});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			auto data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.eventCallback(event);
					break;
				}
			case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.eventCallback(event);
					break;
				}
			case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.eventCallback(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
		{
			auto data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.eventCallback(event);
					break;
				}
			case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.eventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			auto data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.eventCallback(event);
		});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos)
		{
			auto data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.eventCallback(event);
		});
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_window);
	}

	void Window::onUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void Window::setEventCallback(const EventCallbackFunc& callback)
	{
		m_data.eventCallback = callback;
	}

	void Window::setVSync(bool b)
	{
		if (b)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_data.vSync = b;
	}

	bool Window::isVSync() const
	{
		return m_data.vSync;
	}

	unsigned int Window::getWidth() const
	{
		return m_data.width;
	}

	unsigned int Window::getHeight() const
	{
		return m_data.height;
	}

	
}