#pragma once

#include "Texture.h"
#include <GLFW\glfw3.h>

#include "View.h"
#include "Primitives.h"

#include "Chestnut\Events.h"
#include "Chestnut\Patterns\Singelton.h"

#include "Chestnut\Math\Maths.h"

#include "Color.h"

namespace chst
{
	using EventCallbackFunc = std::function<void(Event&)>;

	class CHESTNUT_API Renderer : private Singleton<Renderer>
	{
	private:
		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool vSync;

			EventCallbackFunc eventCallback;
		} m_data;

		GLFWwindow* m_window;

		std::string m_defaultShader;
		std::map<std::string, Shader*> m_shaders;

		View m_view;
		Primitives m_primitives;
	public:
		static bool Init(const std::string& title, int width, int height, float viewW, float viewH);
		static void Destroy();

		static void Start();
		static void Flush();

		static void SetVSync(bool b);

		static void SetClearColor(float r, float g, float b, float a);
		static void SetClearColor(const glm::vec4& color);
		static void EnableBlend(GLenum sfactor, GLenum dfactor);

		static void SetEventCallback(const EventCallbackFunc& callback);
		static bool OnResize(WindowResizeEvent& e);

		static void SetWindowTitle(const std::string& title);
		static std::string GetWindowTitle();

		static void SetDefaultShader(const std::string& name);
		static void AddShader(const std::string& name, Shader* shader);
		static Shader* GetShader(const std::string& name);

		// ----------------------------texture---------------------------------------------------------------------------
		static void RenderTexture(Texture* texture, std::vector<GLuint> indices);
		static void RenderTextureS(Texture* texture, const glm::vec2& srcPos, const glm::mat4& mvp, std::vector<GLuint> indices, const std::string& shader);
		static void RenderTextureS(Texture* texture, const glm::vec2& srcPos, const glm::mat4& mvp, std::vector<GLuint> indices, Shader* shader);

		// ----------------------------primitives------------------------------------------------------------------------
		static void DrawLine(const glm::vec2& start, const glm::vec2& end, const glm::vec4& color);
		static void DrawLine(const chstMath::Line& line, const glm::vec4& color);
		static void DrawRect(float x, float y, float w, float h, const glm::vec4& color);
		static void DrawRect(const glm::vec2& pos, const glm::vec2& dim, const glm::vec4& color);
		static void DrawRect(chstMath::Rect rect, const glm::vec4& color);
		static void DrawCircle(const glm::vec2& center, float radius, const glm::vec4& color);
		static void DrawPolygon(const std::vector<glm::vec2>& vertices, const glm::vec4& color);

		static void FillRect(float x, float y, float w, float h, const glm::vec4& color);
		static void FillRect(chstMath::Rect rect, const glm::vec4& color);
		static void FillCircle(const glm::vec2& center, float radius, const glm::vec4& color);
		static void FillPolygon(const std::vector<glm::vec2>& vertices, const glm::vec4& color);

		static GLFWwindow* GetContext();
		static unsigned int GetWindowWidth();
		static unsigned int GetWindowHeight();

		// ----------------------------view------------------------------------------------------------------------------
		static void SetView(float x, float y);
		static void SetView(float x, float y, float width, float height);
		static void SetViewPos(float x, float y, chstMath::Rect* constraint);
		static glm::vec2 GetViewPosition();

		static glm::mat4 GetViewMat();
		static View* GetView();
	};
}
