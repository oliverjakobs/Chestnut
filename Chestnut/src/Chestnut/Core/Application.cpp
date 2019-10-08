#include "chstpch.h"
#include "Application.h"

#include "Chestnut/Utility/Debugger.h"

#include "Chestnut/Graphics/Renderer.h"

#include "Chestnut/Input/Input.h"

#include <glfw/glfw3.h>

namespace chst
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		DEBUG_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create("Chestnut Engine", 1280, 720));
		m_Window->SetEventCallback(BIND_FUNCTION(Application::OnEvent));

		Renderer::Init();

		m_imGuiRenderer.Init();
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_FUNCTION(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_FUNCTION(Application::OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}

			m_imGuiRenderer.Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_imGuiRenderer.End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}