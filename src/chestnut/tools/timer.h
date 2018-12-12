#pragma once

namespace chst
{
	class Timer
	{
	private:
		float m_timer;
		int m_frames;
		int m_fps;

		float m_deltaTime;
		float m_lastFrame;
	public:
		Timer();
		~Timer();

		void start();
		void end();

		float getDeltaTime() const;
		int getFPS() const;
	};
}