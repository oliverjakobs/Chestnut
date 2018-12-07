#pragma once

#include "shader.h"

#include "primitives.h"

#include <map>
#include <vector>

#include "color.h"

#include "view.h"

#include "tools.h"

namespace chst
{
	using namespace chestnutMath;
	
	class Renderer : public Singleton<Renderer>
	{
	private:				
		View m_view;

		Primitives m_primitives;

		std::string m_defaultShader;
		std::map<std::string, Shader*> m_shaders;

		GLFWwindow* m_window;
	public:
		Renderer();
		~Renderer();
						
		void setCameraPos(float x, float y, Rect* constraint);
		
		// ----------------------------statics---------------------------------------------------------------------------
		static bool init(const char* title, int w, int h, float viewW, float viewH);
		static void destroy();

		static void setWindowIcon(const std::string& path);

		static void setClearColor(glm::vec4 color);
		static void enableBlend(GLenum sfactor, GLenum dfactor);

		static float getWidth();
		static float getHeight();

		static int getWindowWidth();
		static int getWindowHeight();

		static void close();
		static bool closed();

		static void setDefaultShader(const std::string& name);
		static void addShader(const std::string& name, Shader* shader);
		static Shader* getShader(const std::string& name);

		static GLFWwindow* getContext();
		
		// ----------------------------texture---------------------------------------------------------------------------
		static GLuint createTexture(const char* path, float* w, float* h, bool flipOnLoad);
		static void deleteTexture(GLuint* textureID);
		static void bindTexture(GLuint texture, GLuint slot = 0);
		
		static void renderTexture(unsigned int vao, unsigned int texture, const glm::vec2& srcPos, const glm::mat4& model, const glm::mat4& view = Renderer::getViewMat(), const std::string& shader = "");

		// ----------------------------render queue----------------------------------------------------------------------
		static void start();
		static void flush();

		// ----------------------------primitives------------------------------------------------------------------------
		static void drawLine(const glm::vec2& start, const glm::vec2& end, const glm::vec4& color);
		static void drawLine(const Line& line, const glm::vec4& color);
		static void drawRect(float x, float y, float w, float h, const glm::vec4& color);
		static void drawRect(Rect rect, const glm::vec4& color);
		static void drawCircle(const glm::vec2& center, float radius, const glm::vec4& color);
		static void drawPolygon(const std::vector<glm::vec2>& vertices, const glm::vec4& color);

		static void fillRect(float x, float y, float w, float h, const glm::vec4& color);
		static void fillRect(Rect rect, const glm::vec4& color);
		static void fillCircle(const glm::vec2& center, float radius, const glm::vec4& color);
		static void fillPolygon(const std::vector<glm::vec2>& vertices, const glm::vec4& color);
		
		// ----------------------------view------------------------------------------------------------------------------
		static void setView(float x, float y);
		static void setView(float x, float y, float width, float height);
		static glm::vec2 getViewPosition();

		static glm::mat4 getViewMat();
		static View* getView();
	};
}

