#pragma once

#include "Chestnut/Api.h"

namespace chst 
{
	class CHST_API ImGuiRenderer 
	{
	private:
		float m_Time = 0.0f;
	public:
		void Init();
		void Quit();

		void Begin();
		void End();
	};
}