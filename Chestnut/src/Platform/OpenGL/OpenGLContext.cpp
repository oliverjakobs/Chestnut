#include "chstpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace chst{

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		CHST_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CHST_CORE_ASSERT(status, "Failed to initialize Glad!");

		CHST_CORE_INFO("OpenGL Info:");
		CHST_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		CHST_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		CHST_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}