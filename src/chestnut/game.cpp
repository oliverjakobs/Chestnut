#include "Game.h"

#include "graphics.h"
#include "timer.h"

namespace chst
{
	bool Game::init(const std::string& title, int width, int height, float viewW, float viewH)
	{
#if _DEBUG
		setDebug(true);
#else 
		setDebug(false);
#endif
		m_title = title;

		if (!Renderer::init(title.c_str(), width, height, viewW, viewH))
		{
			DEBUG_MESSAGE("Failed to initialize Renderer");
			return false;
		}
		glfwSetWindowUserPointer(Renderer::getContext(), this);

		m_input = new Input();

		Renderer::enableBlend(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return true;
	}

	Game::Game(const std::string& title, int width, int height, float viewW, float viewH)
	{
		init(title, width, height, viewW, viewH);
	}

	Game::~Game()
	{

	}

	void Game::setTitle(const std::string & title)
	{
		glfwSetWindowTitle(Renderer::getContext(), title.c_str());
	}

	void Game::setDebug(bool b)
	{
		m_debug = b;
	}

	void Game::showFPS(bool b)
	{
		m_showFPS = b;
	}

	void Game::setExitKey(unsigned int key)
	{
		m_exitKey = key;
	}

	void Game::setDebugKey(unsigned int key)
	{
		m_debugKey = key;
	}
	
	void Game::run()
	{
		while (!Renderer::closed())
		{
			m_timer.start();

			glfwPollEvents();
						
			m_input->update();

			if (m_input->keyHit(m_exitKey))
				Renderer::close();

			if (m_input->keyHit(m_debugKey))
				setDebug(!m_debug);

			update(m_timer.getDeltaTime());

			Renderer::start();
			draw();

			if (m_debug)
				debugDraw();
			
			Renderer::flush();

			m_timer.end();

			if (m_showFPS)
				setTitle(m_title + stringf("  |  FPS: %i", m_timer.getFPS()));
		}
	}

	Input* Game::getInput() const
	{
		return m_input;
	}
}