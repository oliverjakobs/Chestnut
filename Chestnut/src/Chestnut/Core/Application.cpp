#include "chstpch.h"
#include "Application.h"

#include "Chestnut/Utility/Obelisk.h"
#include "Chestnut/Utility/Debugger.h"

#include "Chestnut/Graphics/Renderer.h"
#include "Chestnut/Input/Input.h"

#include <glfw/glfw3.h>

namespace chst
{
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		DEBUG_ASSERT(!s_instance, "Application already exists!");
		s_instance = this;

		m_window = chst::CreateScope<Window>("Chestnut Engine", 1280, 720);
		m_window->SetEventCallback(BIND_FUNCTION(Application::OnEvent));

		Renderer::Init();

		m_imGuiRenderer.Init();
	}

	void Application::PushLayer(Layer* layer)
	{
		m_layerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_layerStack.PushOverlay(layer);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_FUNCTION(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_FUNCTION(Application::OnWindowResize));

		for (auto it = m_layerStack.end(); it != m_layerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_running)
		{
			m_timer.Start((float)glfwGetTime());

			if (!m_minimized)
			{
				for (Layer* layer : m_layerStack)
					layer->OnUpdate(Timestep(m_timer.DeltaTime));

				for (Layer* layer : m_layerStack)
					layer->OnRender();
			}

			// ImGui
			m_imGuiRenderer.Begin();

			for (Layer* layer : m_layerStack)
				layer->OnImGuiRender();

			m_imGuiRenderer.End();

			m_window->OnUpdate();

			m_timer.End((float)glfwGetTime());
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_minimized = true;
			return false;
		}

		m_minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}