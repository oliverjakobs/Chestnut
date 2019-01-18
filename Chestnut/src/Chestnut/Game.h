#pragma once

#include "Graphics\Renderer.h"
#include "Input.h"

namespace chst
{
	class CHESTNUT_API Game
	{
	private:
		bool m_isRunning;

		unsigned int m_exitKey;
		unsigned int m_debugKey;
	public:
		Game(const std::string& title, int width, int height, float viewW, float viewH);
		~Game();

		void onEvent(Event& e);
		virtual void onUpdate() = 0;
		virtual void onRender() const = 0;

		void setExitKey(unsigned int key);
		void setDebugKey(unsigned int key);

		bool onWindowClose(WindowCloseEvent& e);

		void run();
	};

	Game* CreateGame();
}
