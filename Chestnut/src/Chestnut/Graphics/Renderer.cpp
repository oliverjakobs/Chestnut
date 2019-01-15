#include "chstpch.h"
#include "Renderer.h"

namespace chst
{
	static void GLFWErrorCallback(int error, const char* desc)
	{
		CHST_CORE_ERROR("[GLFW]: (%c) %d", error, desc);
	}

	bool Renderer::Init(const std::string& title, int width, int height)
	{
		Get()->m_data.title = title;
		Get()->m_data.width = width;
		Get()->m_data.height = height;

		int status = glfwInit();
		CHST_CORE_ASSERT(status, "[GLFW] Failed to initialize GLFW");

		glfwSetErrorCallback(GLFWErrorCallback);

		//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		CHST_CORE_INFO("[GLFW] Creating window: %s, %d, %d", title.c_str(), width, height);

		Get()->m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		CHST_CORE_ASSERT(Get()->m_window, "[GLFW] Failed to create GLFW window");
		glfwMakeContextCurrent(Get()->m_window);

		status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CHST_CORE_ASSERT(status, "[GLAD] Failed to initialize Glad");

		glfwSetWindowUserPointer(Get()->m_window, &Get()->m_data);

		// set glfw callbacks
		glfwSetWindowSizeCallback(Get()->m_window, [](GLFWwindow* win, int w, int h)
		{
			auto data = *(WindowData*)glfwGetWindowUserPointer(win);
			data.width = w;
			data.height = h;

			WindowResizeEvent e(w, h);
			data.eventCallback(e);
		});

		glfwSetWindowCloseCallback(Get()->m_window, [](GLFWwindow* window)
		{
			auto data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent e;
			data.eventCallback(e);
		});

		glfwSetKeyCallback(Get()->m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			auto data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
				data.eventCallback(KeyPressedEvent(key, 0));
				break;
			case GLFW_RELEASE:
				data.eventCallback(KeyReleasedEvent(key));
				break;
			case GLFW_REPEAT:
				data.eventCallback(KeyPressedEvent(key, 1));
				break;
			}
		});

		glfwSetMouseButtonCallback(Get()->m_window, [](GLFWwindow* window, int button, int action, int mods)
		{
			auto data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
				data.eventCallback(MouseButtonPressedEvent(button));
				break;
			case GLFW_RELEASE:
				data.eventCallback(MouseButtonReleasedEvent(button));
				break;
			}
		});

		glfwSetScrollCallback(Get()->m_window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			auto data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.eventCallback(event);
		});

		glfwSetCursorPosCallback(Get()->m_window, [](GLFWwindow* window, double xPos, double yPos)
		{
			auto data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.eventCallback(event);
		});
		
		return true;
	}

	void Renderer::Destroy()
	{
		glfwDestroyWindow(Get()->m_window);
		glfwTerminate();
	}

	void Renderer::Start()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::Flush()
	{
		glfwPollEvents();
		glfwSwapBuffers(Get()->m_window);
	}

	void Renderer::SetVSync(bool b)
	{
		glfwSwapInterval(b ? 1 : 0);

		Get()->m_data.vSync = b;
	}

	void Renderer::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void Renderer::SetEventCallback(const EventCallbackFunc& callback)
	{
		Get()->m_data.eventCallback = callback;
	}

	void Renderer::SetWindowTitle(const std::string& title)
	{
		glfwSetWindowTitle(Get()->m_window, title.c_str());
	}

	std::string Renderer::GetWindowTitle()
	{
		return Get()->m_data.title;
	}

	unsigned int Renderer::GetWindowWidth()
	{
		return Get()->m_data.width;
	}
	unsigned int Renderer::GetWindowHeight()
	{
		return Get()->m_data.height;
	}
}