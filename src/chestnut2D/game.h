#pragma once

#include "timer.h"

#include "input\input.h"

#include "tools.h"

namespace chestnut2D
{
	class Game 
	{
	protected:
		Input* m_input;

		bool m_debug;
		bool m_showFPS;

		Timer m_timer;

		unsigned int m_exitKey;
		unsigned int m_debugKey;
		
		bool init(const std::string& title, int width, int height, float viewW, float viewH);
	public:
		Game(const std::string& title, int width, int height, float viewW, float viewH);
		~Game();

		void setTitle(const std::string& title);

		void setDebug(bool b);
		void showFPS(bool b);
		
		void setExitKey(unsigned int key);
		void setDebugKey(unsigned int key);
		
		virtual void update(float deltaTime) = 0;
		virtual void draw() = 0;
		virtual void debugDraw() {};

		void run();

		Input* getInput() const;
	};
}