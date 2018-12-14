#pragma once

#include "primitives.h"

#include <map>

#include "color.h"

#include "view.h"

#include "tools.h"

#include "texture.h"

namespace chst
{	
	enum ShaderType
	{
		NO_TYPE,
		DEFAULT,
		KERNEL,
		PRIMITIVE
	};

	class Renderer : public Singleton<Renderer>
	{
	private:				
		View m_view;

		Primitives m_primitives;

		std::string m_defaultShader;
		std::map<std::string, Shader*> m_shaders;
		std::map<ShaderType, std::string> m_shaderTypes;

		GLFWwindow* m_window;
	public:
		Renderer();
		~Renderer();
						
		void setViewPos(float x, float y, chstMath::Rect* constraint);
		
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
		static void addShader(const std::string& name, Shader* shader, ShaderType type = NO_TYPE);
		static Shader* getShader(const std::string& name);
		static Shader* getShader(ShaderType type);

		static GLFWwindow* getContext();
		
		// ----------------------------texture---------------------------------------------------------------------------
		static void renderTexture(Texture* texture, std::vector<GLuint> indices);
		static void renderTextureS(Texture* texture, const glm::vec2& srcPos, const glm::mat4& mvp, std::vector<GLuint> indices, const std::string& shader);
		static void renderTextureS(Texture* texture, const glm::vec2& srcPos, const glm::mat4& mvp, std::vector<GLuint> indices, ShaderType shader);
		static void renderTextureS(Texture* texture, const glm::vec2& srcPos, const glm::mat4& mvp, std::vector<GLuint> indices, Shader* shader);

		// ----------------------------render queue----------------------------------------------------------------------
		static void start();
		static void flush();

		// ----------------------------primitives------------------------------------------------------------------------
		static void drawLine(const glm::vec2& start, const glm::vec2& end, const glm::vec4& color);
		static void drawLine(const chstMath::Line& line, const glm::vec4& color);
		static void drawRect(float x, float y, float w, float h, const glm::vec4& color);
		static void drawRect(const glm::vec2& pos, const glm::vec2& dim, const glm::vec4& color);
		static void drawRect(chstMath::Rect rect, const glm::vec4& color);
		static void drawCircle(const glm::vec2& center, float radius, const glm::vec4& color);
		static void drawPolygon(const std::vector<glm::vec2>& vertices, const glm::vec4& color);

		static void fillRect(float x, float y, float w, float h, const glm::vec4& color);
		static void fillRect(chstMath::Rect rect, const glm::vec4& color);
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

