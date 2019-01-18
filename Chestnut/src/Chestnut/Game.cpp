#include "chstpch.h"
#include "Game.h"

#include "Timer.h"

namespace chst
{
#define BIND_EVENT_FUNC(x) std::bind(&x, this, std::placeholders::_1)

	Game::Game(const std::string& title, int width, int height, float viewW, float viewH)
	{
		if (!Renderer::Init(title, width, height, viewW, viewH))
		{
			CHST_CORE_ERROR("Failed to initialize the renderer.");
		}

		Renderer::SetEventCallback(BIND_EVENT_FUNC(Game::onEvent));
		Renderer::SetClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		Renderer::SetVSync(false);

		m_exitKey = GLFW_KEY_UNKNOWN;
		m_debugKey = GLFW_KEY_UNKNOWN;

		m_isRunning = true;
	}

	Game::~Game()
	{
		Renderer::Destroy();
	}

	void Game::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(Game::onWindowClose));
		dispatcher.dispatch<WindowResizeEvent>(Renderer::OnResize);

		dispatcher.dispatch<KeyPressedEvent>(Input::OnKeyPressed);
		dispatcher.dispatch<KeyReleasedEvent>(Input::OnKeyReleased);
		dispatcher.dispatch<MouseButtonPressedEvent>(Input::OnMouseButtonPressed);
		dispatcher.dispatch<MouseButtonReleasedEvent>(Input::OnMouseButtonReleased);
		dispatcher.dispatch<MouseMovedEvent>(Input::OnMouseMoved);
		
		//if (!e.handled)
		//	GOLEM_CORE_INFO("[EVENT] Unhandled Event: %s", e.toString().c_str());
	}

	void Game::setExitKey(unsigned int key)
	{
		m_exitKey = key;
	}

	void Game::setDebugKey(unsigned int key)
	{
		m_debugKey = key;
	}

	bool Game::onWindowClose(WindowCloseEvent& e)
	{
		m_isRunning = false;
		return true;
	}

	void Game::run()
	{
		while (m_isRunning)
		{
			Timer::Start(glfwGetTime());

			Input::OnUpdate();
			glfwPollEvents();

			if (Input::KeyPressed(m_exitKey))
				m_isRunning = false;

			/*if (Input::KeyPressed(m_debugKey))
				setDebug(!m_debug);*/

			onUpdate();

			Renderer::Start();

			onRender();
			
			Renderer::Flush();

			Timer::End(glfwGetTime());

			Renderer::SetWindowTitle(Renderer::GetWindowTitle() + "  |  " + std::to_string(Timer::GetFPS()));
		}
	}
}