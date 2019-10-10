#pragma once

#include "Api.h"

#include "Window.h"
#include "LayerStack.h"

#include "Chestnut/ImGui/ImGuiRenderer.h"

#include "Chestnut/Utility/Timer.h"

namespace chst
{
	class Application
	{
	private:
		chst::Scope<Window> m_window;
		ImGuiRenderer m_imGuiRenderer;

		bool m_running = true;
		bool m_minimized = false;
		LayerStack m_layerStack;

		obelisk::Timer m_timer;

		static Application* s_instance;

	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_instance; }
		inline static Window& GetWindow() { return *Get().m_window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}