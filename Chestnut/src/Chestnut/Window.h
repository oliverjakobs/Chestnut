#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "Events.h"

namespace chst
{
	using EventCallbackFunc = std::function<void(Event&)>;

	class CHESTNUT_API Window
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
		Window(const std::string& title = "Chestnut Engine", unsigned int width = 1280, unsigned int height = 720);
		virtual ~Window();

		void onUpdate();

		void setEventCallback(const EventCallbackFunc& callback);
		void setVSync(bool b);
		bool isVSync() const;

		unsigned int getWidth() const;
		unsigned int getHeight() const;
	};

}