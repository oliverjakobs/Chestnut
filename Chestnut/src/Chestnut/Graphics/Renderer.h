#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "Chestnut\Events.h"
#include "Chestnut\Patterns\Singelton.h"

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
	public:
		static bool Init(const std::string& title, int width, int height);
		static void Destroy();

		static void Start();
		static void Flush();

		static void SetVSync(bool b);

		static void SetClearColor(float r, float g, float b, float a);

		static void SetEventCallback(const EventCallbackFunc& callback);

		static void SetWindowTitle(const std::string& title);
		static std::string GetWindowTitle();

		static unsigned int GetWindowWidth();
		static unsigned int GetWindowHeight();
	};
}
