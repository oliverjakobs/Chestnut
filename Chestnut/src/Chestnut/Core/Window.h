#pragma once

#include "chstpch.h"

#include "Chestnut/Core/Core.h"
#include "Chestnut/Events/Event.h"

struct GLFWwindow;

namespace chst
{
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			uint32_t Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;

		void Init(const std::string& title, uint32_t width, uint32_t height);
		void Shutdown();
	public:
		Window(const std::string& title, uint32_t width, uint32_t height);
		~Window();

		void OnUpdate();

		inline unsigned int GetWidth() const { return m_Data.Width; }
		inline unsigned int GetHeight() const { return m_Data.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }
		virtual void SetVSync(bool enabled);
		virtual bool IsVSync() const;

		inline void* GetNativeWindow() const { return m_Window; }

		static Window* Create(const std::string& title, uint32_t width, uint32_t height);
	};
}