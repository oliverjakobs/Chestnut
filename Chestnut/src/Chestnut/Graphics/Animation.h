#pragma once

#include "api.h"

namespace chst
{
	class CHESTNUT_API Animation
	{
	private:
		int m_start;
		int m_length;

		float m_delay;
		float m_frameCounter;

		int m_frame;
	public:
		Animation(int start, int length, float delay);
		virtual ~Animation();

		void setStart(int s);

		void start();
		void step(float deltaTime);
		int getFrame();
	};
}