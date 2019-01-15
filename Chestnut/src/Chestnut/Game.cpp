#include "chstpch.h"
#include "Game.h"

#include "Timer.h"

namespace chst
{
#define BIND_EVENT_FUNC(x) std::bind(&x, this, std::placeholders::_1)

	Game::Game()
	{
		if (!Renderer::Init("Chestnut", 1200, 800))
		{
			CHST_CORE_ERROR("Failed to initialize the renderer.");
		}

		Renderer::SetEventCallback(BIND_EVENT_FUNC(Game::onEvent));
		Renderer::SetClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		Renderer::SetVSync(false);

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

		dispatcher.dispatch<KeyPressedEvent>([](KeyEvent& e)
		{
			CHST_CORE_INFO("Key pressed: %d", e.getKeyCode());
			return true;
		});
		
		//if (!e.handled)
		//	GOLEM_CORE_INFO("[EVENT] Unhandled Event: %s", e.toString().c_str());
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

			onUpdate();

			Renderer::Start();

			onRender();
			
			Renderer::Flush();

			Timer::End(glfwGetTime());

			Renderer::SetWindowTitle(Renderer::GetWindowTitle() + "  |  " + std::to_string(Timer::GetFPS()));
		}
	}
}