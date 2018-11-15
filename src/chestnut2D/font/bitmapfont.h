#pragma once

#include "font.h"

namespace chestnut2D 
{
	class BitMapFont : public Font
	{
	private:
		Image* m_image;

		float m_charSpacing;
	public:
		BitMapFont(const std::string& path, float width, float height, float charSpacing);
		~BitMapFont();

		void draw(const std::string& text, float x, float y, const glm::vec4& color, const glm::mat4& view) const override;
		void draw(const std::string& text, const glm::vec2& position, const glm::vec4& color, const glm::mat4& view) const override;
	};

	class BitMapNumFont : public Font
	{
	private:
		Image* m_image;

		float m_charSpacing; 
	public:
		BitMapNumFont(const std::string& path, float width, float height, float charSpacing);
		~BitMapNumFont();

		void draw(const std::string& text, float x, float y, const glm::vec4& color, const glm::mat4& view) const override;
		void draw(const std::string& text, const glm::vec2& position, const glm::vec4& color, const glm::mat4& view) const override;
	};
}