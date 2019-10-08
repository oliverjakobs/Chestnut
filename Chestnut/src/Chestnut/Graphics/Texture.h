#pragma once

#include <string>

#include "Chestnut/Core/Core.h"

namespace chst
{
	class Texture
	{
	private:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
	public:
		Texture(const std::string& path);
		~Texture();

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

		void Bind(uint32_t slot = 0) const;
	};
}