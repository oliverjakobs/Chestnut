#include "chstpch.h"
#include "Renderer.h"

namespace chst
{
	using namespace chstMath;

	static void GLFWErrorCallback(int error, const char* desc)
	{
		//CHST_CORE_ERROR("[GLFW]: (%c) %d", error, desc);
	}

	bool Renderer::Init(const std::string& title, int width, int height, float viewW, float viewH)
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

		CHST_CORE_INFO("[GLFW] Creating window: {}, {}, {}", title.c_str(), width, height);

		Get()->m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		CHST_CORE_ASSERT(Get()->m_window, "[GLFW] Failed to create GLFW window");
		glfwMakeContextCurrent(Get()->m_window);

		status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CHST_CORE_ASSERT(status, "[GLAD] Failed to initialize Glad");

		glfwSetWindowUserPointer(Get()->m_window, &Get()->m_data);

		Get()->m_view.create(0.0f, 0.0f, viewW, viewH);
		Get()->m_primitives.create(new Shader("res/shader/primitive.vert", "res/shader/primitive.frag"));

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
		Get()->m_primitives.flush(GetViewMat());
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

	void Renderer::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void Renderer::EnableBlend(GLenum sfactor, GLenum dfactor)
	{
		glEnable(GL_BLEND);
		glBlendFunc(sfactor, dfactor);
	}

	void Renderer::SetEventCallback(const EventCallbackFunc& callback)
	{
		Get()->m_data.eventCallback = callback;
	}

	bool Renderer::OnResize(WindowResizeEvent& e)
	{
		Get()->m_view.create(Get()->m_view.xPos, Get()->m_view.yPos, e.getWidth(), e.getHeight());
		return true;
	}

	void Renderer::SetWindowTitle(const std::string& title)
	{
		glfwSetWindowTitle(Get()->m_window, title.c_str());
	}

	std::string Renderer::GetWindowTitle()
	{
		return Get()->m_data.title;
	}

	void Renderer::SetDefaultShader(const std::string& name)
	{
		Get()->m_defaultShader = name;
	}

	void Renderer::AddShader(const std::string& name, Shader* shader)
	{
		Get()->m_shaders[name] = shader;

		if (Get()->m_defaultShader.empty())
			Get()->m_defaultShader = name;
	}

	Shader* Renderer::GetShader(const std::string& name)
	{
		try
		{
			return Get()->m_shaders.at(name.empty() ? Get()->m_defaultShader : name);
		}
		catch (std::out_of_range outofrange)
		{
			CHST_CORE_WARN("No such shader: %s", (name.empty() ? Get()->m_defaultShader : name).c_str());
			return nullptr;
		}
	}

	void Renderer::RenderTexture(Texture* texture, std::vector<GLuint> indices)
	{
		if (texture != nullptr && texture->getTextureID() != 0)
		{
			texture->bind();

			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());
		}
	}

	void Renderer::RenderTextureS(Texture* texture, const glm::vec2& srcPos, const glm::mat4& mvp, std::vector<GLuint> indices, const std::string& shader)
	{
		RenderTextureS(texture, srcPos, mvp, indices, GetShader(shader));
	}

	void Renderer::RenderTextureS(Texture* texture, const glm::vec2& srcPos, const glm::mat4& mvp, std::vector<GLuint> indices, Shader* shader)
	{
		if (texture != nullptr && texture->getTextureID() != 0)
		{
			texture->bind();

			shader->enable();

			try
			{
				shader->setUniformMat4("mvp", mvp);
				shader->setUniform2f("uFramePos", srcPos);
			}
			catch (ShaderException& e)
			{
				CHST_CORE_ERROR(e.what());
				return;
			}

			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());
		}
	}

	void Renderer::DrawLine(const glm::vec2& start, const glm::vec2& end, const glm::vec4& color)
	{
		Get()->m_primitives.drawLine(start, end, color, GetViewMat());
	}

	void Renderer::DrawLine(const Line& line, const glm::vec4 & color)
	{
		Get()->m_primitives.drawLine(line.start, line.end, color, GetViewMat());
	}

	void Renderer::DrawRect(float x, float y, float w, float h, const glm::vec4& color)
	{
		std::vector<glm::vec2> vertices =
		{
			glm::vec2(x, y),
			glm::vec2(x + w, y),
			glm::vec2(x + w, y + h),
			glm::vec2(x, y + h)
		};

		Get()->m_primitives.drawPolygon(vertices, color, GetViewMat());
	}

	void Renderer::DrawRect(const glm::vec2& pos, const glm::vec2& dim, const glm::vec4& color)
	{
		DrawRect(pos.x, pos.y, dim.x, dim.y, color);
	}

	void Renderer::DrawRect(Rect rect, const glm::vec4& color)
	{
		DrawRect(rect.x, rect.y, rect.w, rect.h, color);
	}

	void Renderer::DrawCircle(const glm::vec2& center, float radius, const glm::vec4 & color)
	{
		Get()->m_primitives.drawCircle(center, radius, color, GetViewMat());
	}

	void Renderer::DrawPolygon(const std::vector<glm::vec2>& vertices, const glm::vec4& color)
	{
		Get()->m_primitives.drawPolygon(vertices, color, GetViewMat());
	}

	void Renderer::FillRect(float x, float y, float w, float h, const glm::vec4& color)
	{
		std::vector<glm::vec2> vertices =
		{
			glm::vec2(x, y),
			glm::vec2(x + w, y),
			glm::vec2(x + w, y + h),
			glm::vec2(x, y + h)
		};

		Get()->m_primitives.fillPolygon(vertices, color, GetViewMat());
	}

	void Renderer::FillRect(Rect rect, const glm::vec4 & color)
	{
		FillRect(rect.x, rect.y, rect.w, rect.h, color);
	}

	void Renderer::FillCircle(const glm::vec2& center, float radius, const glm::vec4& color)
	{
		Get()->m_primitives.fillCircle(center, radius, color, GetViewMat());
	}

	void Renderer::FillPolygon(const std::vector<glm::vec2>& vertices, const glm::vec4& color)
	{
		Get()->m_primitives.fillPolygon(vertices, color, GetViewMat());
	}

	GLFWwindow* Renderer::GetContext()
	{
		return Get()->m_window;
	}

	unsigned int Renderer::GetWindowWidth()
	{
		return Get()->m_data.width;
	}

	unsigned int Renderer::GetWindowHeight()
	{
		return Get()->m_data.height;
	}

	void Renderer::SetView(float x, float y)
	{
		Get()->m_view.create(x, y, Get()->m_view.width, Get()->m_view.height);
	}

	void Renderer::SetView(float x, float y, float width, float height)
	{
		Get()->m_view.create(x, y, width, height);
	}

	void Renderer::SetViewPos(float x, float y, chstMath::Rect* constraint)
	{
		View& v = *GetView();

		if (constraint != nullptr)
		{
			x -= v.width / 2.0f;
			y -= v.height / 2.0f;

			if (x < constraint->x)
				x = constraint->x;

			if (x + v.width > constraint->x + constraint->w)
				x = constraint->x + constraint->w - v.width;

			if (y < constraint->y)
				y = constraint->y;

			if (y + v.height > constraint->y + constraint->h)
				y = constraint->y + constraint->h - v.height;

			SetView(x, y);
		}
		else
		{
			SetView(x - v.width / 2.0f, y - v.height / 2.0f);
		}
	}

	glm::vec2 Renderer::GetViewPosition()
	{
		return glm::vec2(Get()->m_view.xPos, Get()->m_view.yPos);
	}

	glm::mat4 Renderer::GetViewMat()
	{
		return Get()->m_view.mat;
	}

	View* Renderer::GetView()
	{
		return &Get()->m_view;
	}
}