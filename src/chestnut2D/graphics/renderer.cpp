#include "renderer.h"

#include "tools\util\utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace chestnut2D
{
	using namespace chestnutMath;

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

		glfwSwapInterval(1);

		if (glewInit() != GLEW_OK)
		{
			DEBUG_MESSAGE("[Glew] Failed to initialize glew");
			glfwTerminate();
			return false;
		}

		instance()->m_primitives.create();
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
		if (path.empty())
			return;

		GLFWimage images[1];

		stbi_set_flip_vertically_on_load(true);

		images[0].pixels = stbi_load(path.c_str(), &images[0].width, &images[0].height, 0, 4); //rgba channels 
		glfwSetWindowIcon(instance()->m_window, 1, images); 
		stbi_image_free(images[0].pixels); 
	}
	
	void Renderer::setCameraPos(float posX, float posY, Rect* constraint)
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

	void Renderer::setDefaultShader(const std::string & name)
	{
		instance()->m_defaultShader = name;
	}

	void Renderer::addShader(const std::string & name, Shader * shader)
	{
		instance()->m_shaders[name] = shader;

		if (instance()->m_defaultShader.empty())
			instance()->m_defaultShader = name;
	}

	Shader* Renderer::getShader(const std::string & name)
	{
		try
		{
			if (name.empty())
				return instance()->m_shaders.at(instance()->m_defaultShader);
			else
				return instance()->m_shaders.at(name);
		}
		catch (std::out_of_range outofrange)
		{
			DEBUG_MESSAGE("No such shader: " << (name.empty() ? instance()->m_defaultShader : name));
			return nullptr;
		}
	}
	
	GLFWwindow* Renderer::getContext()
	{
		return instance()->m_window;
	}

	GLuint Renderer::createTexture(const char* path, float* w, float* h, bool flipOnLoad)
	{
		unsigned int textureID;
		glGenTextures(1, &textureID);

		stbi_set_flip_vertically_on_load(flipOnLoad);

		int width = 0;
		int height = 0;
		int bpp;

		unsigned char* data = stbi_load(path, &width, &height, &bpp, 4);

		if (data)
		{
			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			stbi_image_free(data);
		}
		else
		{
			DEBUG_MESSAGE("[stb] Unable to load file: " << path);
		}

		if (w != nullptr)
			*w = (float)width;
		if (h != nullptr)
			*h = (float)height;

		return textureID;
	}

	void Renderer::deleteTexture(GLuint* textureID)
	{
		glDeleteTextures(1, textureID);
	}

	void Renderer::bindTexture(GLuint texture, unsigned int slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	void Renderer::renderTexture(unsigned int vao, unsigned int texture, const glm::vec2& srcPos, const glm::mat4& model, const glm::mat4& view, const std::string& shaderName)
	{
		if (texture != 0)
		{
			bindTexture(texture);
			glBindVertexArray(vao);

			Shader* shader = getShader(shaderName);

			glm::mat4 projection = glm::mat4();

			shader->enable();
			shader->setUniformMat4("mvp", projection * view * model);
			shader->setUniform2f("uFramePos", srcPos);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}
	}

	void Renderer::start()
	{
		glClearErrorLog();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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