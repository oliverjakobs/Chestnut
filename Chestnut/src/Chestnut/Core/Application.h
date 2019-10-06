#pragma once

#include "Core.h"

#include "Window.h"
#include "Chestnut/Core/LayerStack.h"
#include "Chestnut/Events/Event.h"
#include "Chestnut/Events/ApplicationEvent.h"

#include "Chestnut/Core/Timestep.h"

#include "Chestnut/ImGui/ImGuiRenderer.h"

namespace chst
{
	class Application
	{
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiRenderer m_imGuiRenderer;

		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		static Application* s_Instance;
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}