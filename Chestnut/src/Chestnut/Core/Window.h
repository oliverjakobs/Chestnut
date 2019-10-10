#pragma once

#include "Api.h"

#include "Chestnut/Events/WindowEvent.h"
#include "Chestnut/Events/MouseEvent.h"
#include "Chestnut/Events/KeyEvent.h"

struct GLFWwindow;

namespace chst
{
	class Window
	{
	public:
	private:
		GLFWwindow* m_window;

		struct WindowData
		{
			std::string Title;
			uint32_t Width, Height;
			bool VSync;

			EventCallback EventCallback;
		};

		WindowData m_data;

		void Init(const std::string& title, uint32_t width, uint32_t height);
		void Shutdown();
	public:
		Window(const std::string& title, uint32_t width, uint32_t height);
		~Window();

		void OnUpdate();

		inline unsigned int GetWidth() const { return m_data.Width; }
		inline unsigned int GetHeight() const { return m_data.Height; }
		inline float GetAspectRatio() const { return (float)m_data.Width / (float)m_data.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallback& callback) { m_data.EventCallback = callback; }
		virtual void SetVSync(bool enabled);
		virtual bool IsVSync() const;

		inline GLFWwindow* GetNative() const { return m_window; }
	};
}