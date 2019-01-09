#include "renderer.h"

#include "tools\util\utils.h"

namespace chst
{
	using namespace chstMath;

	Renderer::Renderer()
	{

	}

	Renderer::~Renderer()
	{
		Renderer::destroy();
	}

	bool Renderer::init(const char* title, int w, int h, float viewW, float viewH)
	{
		if (!glfwInit())
		{
			DEBUG_MESSAGE("[GLFW] Failed to initialize GLFW");
			glfwTerminate();
			return false;
		}

		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		instance()->m_window = glfwCreateWindow(w, h, title, NULL, NULL);

		if (!instance()->m_window)
		{
			DEBUG_MESSAGE("[GLFW] Failed to create GLFW window");
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(instance()->m_window);

		Renderer::enableBlend(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (glewInit() != GLEW_OK)
		{
			DEBUG_MESSAGE("[Glew] Failed to initialize glew");
			glfwTerminate();
			return false;
		}

		glViewport(0, 0, w, h);
		instance()->m_primitives.create(new Shader("res/shader/primitive.vert", "res/shader/primitive.frag"));
		instance()->m_view.create(0.0f, 0.0f, viewW, viewH);
		
		return true;
	}

	void Renderer::destroy()
	{
		instance()->m_primitives.destroy();

		glfwDestroyWindow(instance()->m_window);

		glfwTerminate();
	}

	void Renderer::setWindowIcon(const std::string& path)
	{
		Texture::loadAsIcon(path, instance()->m_window);
	}
	
	void Renderer::setViewPos(float posX, float posY, Rect* constraint)
	{
		if (constraint != nullptr)
		{			
			posX -= m_view.width / 2.0f;
			posY -= m_view.height / 2.0f;

			if (posX < constraint->x)
				posX = constraint->x;

			if (posX + m_view.width > constraint->x + constraint->w)
				posX = constraint->x + constraint->w - m_view.width;

			if (posY < constraint->y)
				posY = constraint->y;

			if (posY + m_view.height > constraint->y + constraint->h)
				posY = constraint->y + constraint->h - m_view.height;

			setView(posX, posY);
		}
		else
		{
			setView(posX - m_view.width / 2.0f, posY - m_view.height / 2.0f);
		}
	}

	void Renderer::setClearColor(glm::vec4 color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void Renderer::enableBlend(GLenum sfactor, GLenum dfactor)
	{
		glEnable(GL_BLEND);
		glBlendFunc(sfactor, dfactor);
	}

	float Renderer::getWidth()
	{
		return instance()->m_view.width;
	}

	float Renderer::getHeight()
	{
		return instance()->m_view.height;
	}

	int Renderer::getWindowWidth()
	{
		int width;
		glfwGetWindowSize(instance()->m_window, &width, nullptr);

		return width;
	}

	int Renderer::getWindowHeight()
	{
		int height;
		glfwGetWindowSize(instance()->m_window, nullptr, &height);

		return height;
	}

	void Renderer::close()
	{
		glfwSetWindowShouldClose(instance()->m_window, GLFW_TRUE);
	}

	bool Renderer::closed()
	{
		return glfwWindowShouldClose(instance()->m_window) == 1;
	}

	void Renderer::setDefaultShader(const std::string& name)
	{
		instance()->m_defaultShader = name;
	}

	void Renderer::addShader(const std::string& name, Shader* shader, ShaderType type)
	{
		instance()->m_shaders[name] = shader;

		if (type != NO_TYPE)
			instance()->m_shaderTypes[type] = name;
		else
		{
			try
			{
				instance()->m_shaderTypes.at(DEFAULT);
			}
			catch (std::out_of_range outofrange)
			{
				instance()->m_shaderTypes[DEFAULT] = name;
			}
		}
	}

	Shader* Renderer::getShader(const std::string& name)
	{
		if (name.empty())
			return getShader(DEFAULT);

		try
		{
			return instance()->m_shaders.at(name);
		}
		catch (std::out_of_range outofrange)
		{
			DEBUG_MESSAGE("No such shader: " << (name.empty() ? instance()->m_defaultShader : name));
			return nullptr;
		}
	}

	Shader* Renderer::getShader(ShaderType type)
	{
		try
		{
			return instance()->m_shaders.at(instance()->m_shaderTypes.at(type));
		}
		catch (std::out_of_range outofrange)
		{
			DEBUG_MESSAGE("No such shader type: " << type);
			return nullptr;
		}
	}
	
	GLFWwindow* Renderer::getContext()
	{
		return instance()->m_window;
	}
	
	void Renderer::renderTexture(Texture * texture, std::vector<GLuint> indices)
	{
		if (texture != nullptr && texture->getTextureID() != 0)
		{
			texture->bind();
			
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());
		}
	}

	void Renderer::renderTextureS(Texture* texture, const glm::vec2& srcPos, const glm::mat4& mvp, std::vector<GLuint> indices, const std::string& shader)
	{
		renderTextureS(texture, srcPos, mvp, indices, getShader(shader));
	}

	void Renderer::renderTextureS(Texture* texture, const glm::vec2& srcPos, const glm::mat4& mvp, std::vector<GLuint> indices, ShaderType shader)
	{
		renderTextureS(texture, srcPos, mvp, indices, getShader(shader));
	}

	void Renderer::renderTextureS(Texture* texture, const glm::vec2& srcPos, const glm::mat4& mvp, std::vector<GLuint> indices, Shader* shader)
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
				DEBUG_MESSAGE(e.what());
				return;
			}

			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());
		}
	}

	void Renderer::start()
	{
		glClearErrorLog();

		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::flush()
	{
		Renderer::instance()->m_primitives.flush(getViewMat());

		glfwSwapBuffers(instance()->m_window);
	}

	void Renderer::drawLine(const glm::vec2& start, const glm::vec2& end, const glm::vec4& color)
	{
		instance()->m_primitives.drawLine(start, end, color, getViewMat());
	}

	void Renderer::drawLine(const Line& line, const glm::vec4 & color)
	{
		instance()->m_primitives.drawLine(line.start, line.end, color, getViewMat());
	}

	void Renderer::drawRect(float x, float y, float w, float h, const glm::vec4& color)
	{
		std::vector<glm::vec2> vertices =
		{
			glm::vec2(x, y),
			glm::vec2(x + w, y),
			glm::vec2(x + w, y + h),
			glm::vec2(x, y + h)
		};

		instance()->m_primitives.drawPolygon(vertices, color, getViewMat());
	}

	void Renderer::drawRect(const glm::vec2& pos, const glm::vec2& dim, const glm::vec4& color)
	{
		drawRect(pos.x, pos.y, dim.x, dim.y, color);
	}

	void Renderer::drawRect(Rect rect, const glm::vec4& color)
	{
		drawRect(rect.x, rect.y, rect.w, rect.h, color);
	}

	void Renderer::drawCircle(const glm::vec2& center, float radius, const glm::vec4 & color)
	{
		instance()->m_primitives.drawCircle(center, radius, color, getViewMat());
	}

	void Renderer::drawPolygon(const std::vector<glm::vec2>& vertices, const glm::vec4& color)
	{
		instance()->m_primitives.drawPolygon(vertices, color, getViewMat());
	}

	void Renderer::fillRect(float x, float y, float w, float h, const glm::vec4& color)
	{
		std::vector<glm::vec2> vertices =
		{
			glm::vec2(x, y),
			glm::vec2(x + w, y),
			glm::vec2(x + w, y + h),
			glm::vec2(x, y + h)
		};

		instance()->m_primitives.fillPolygon(vertices, color, getViewMat());
	}

	void Renderer::fillRect(Rect rect, const glm::vec4 & color)
	{
		fillRect(rect.x, rect.y, rect.w, rect.h, color);
	}

	void Renderer::fillCircle(const glm::vec2& center, float radius, const glm::vec4& color)
	{
		instance()->m_primitives.fillCircle(center, radius, color, getViewMat());
	}

	void Renderer::fillPolygon(const std::vector<glm::vec2>& vertices, const glm::vec4& color)
	{
		instance()->m_primitives.fillPolygon(vertices, color, getViewMat());
	}
	
	void Renderer::setView(float x, float y)
	{
		instance()->m_view.create(x, y, instance()->m_view.width, instance()->m_view.height);
	}

	void Renderer::setView(float x, float y, float width, float height)
	{
		instance()->m_view.create(x, y, width, height);
	}

	glm::vec2 Renderer::getViewPosition()
	{
		return glm::vec2(instance()->m_view.xPos, instance()->m_view.yPos);
	}

	glm::mat4 Renderer::getViewMat()
	{
		return instance()->m_view.mat;
	}

	View* Renderer::getView()
	{
		return &instance()->m_view;
	}
}