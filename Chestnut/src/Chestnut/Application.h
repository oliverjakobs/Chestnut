#pragma once

#include "Api.h"

#include "Window.h"
#include "Chestnut/Layer/LayerStack.h"
#include "Chestnut/Events/Event.h"
#include "Chestnut/Events/ApplicationEvent.h"

#include "Chestnut/ImGui/ImGuiRenderer.h"

#include "Chestnut/Renderer/Shader.h"
#include "Chestnut/Renderer/Buffer.h"

namespace chst
{
	class CHST_API Application
	{
	private:
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<ImGuiRenderer> m_imGuiRenderer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;

		bool OnWindowClose(WindowCloseEvent& e);
	private:
		static Application* s_Instance;
	public:
		Application();
		virtual ~Application();

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