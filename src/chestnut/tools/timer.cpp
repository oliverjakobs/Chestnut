#include "timer.h"

#include "gl.h"

namespace chst
{
	Timer::Timer()
	{
		m_timer = 0.0f;
		m_frames = 0;
		m_fps = 0;

		m_deltaTime = 0.0f;
		m_lastFrame = 0.0f;
	}

	Timer::~Timer()
	{
	}

	void Timer::start()
	{
		float currentFrame = (float)glfwGetTime();
		m_deltaTime = currentFrame - m_lastFrame;
		m_lastFrame = currentFrame;
	}

	void Timer::end()
	{
		m_frames++;
		if (glfwGetTime() - m_timer > 1.0f)
		{
			m_timer += 1.0f;
			m_fps = m_frames;
			m_frames = 0;
		}
	}

	float Timer::getDeltaTime() const
	{
		return m_deltaTime;
	}

	int Timer::getFPS() const
	{
		return m_fps;
	}
}
