#pragma once

#include "Graphics\Renderer.h"
#include "Input.h"

namespace chst
{
	class CHESTNUT_API Game
	{
	private:
		bool m_isRunning;
	public:
		Game(const std::string& title, int width, int height);
		~Game();

		void onEvent(Event& e);
		virtual void onUpdate() = 0;
		virtual void onRender() const = 0;

		bool onWindowClose(WindowCloseEvent& e);

		void run();
	};

	Game* CreateGame();
}
