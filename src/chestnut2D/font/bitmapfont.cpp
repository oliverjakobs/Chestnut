#include "bitmapfont.h"

#include <string>

namespace chestnut2D
{
	BitMapFont::BitMapFont(const std::string& path, float width, float height, float charSpacing)
	{
		m_image = new Image(path, width, height, 6, 16);
		m_charSpacing = charSpacing;
	}

	BitMapFont::~BitMapFont()
	{
	}

	void BitMapFont::draw(const std::string& text, float x, float y, const glm::vec4& color, const glm::mat4& view) const
	{
		for (auto& c : text)
		{
			m_image->draw(x, y, c - ' ', view);
			x += (m_image->getWidth() + m_charSpacing);
		}
	}

	void BitMapFont::draw(const std::string& text, const glm::vec2& position, const glm::vec4& color, const glm::mat4& view) const
	{
		draw(text, position.x, position.y, color, view);
	}

	BitMapNumFont::BitMapNumFont(const std::string& path, float width, float height, float charSpacing)
	{
		m_image = new Image(path, width, height, 1, 11);
		m_charSpacing = charSpacing;
	}

	BitMapNumFont::~BitMapNumFont()
	{
	}

	void BitMapNumFont::draw(const std::string& text, float x, float y, const glm::vec4& color, const glm::mat4& view) const
	{
		for (auto& c : text)
		{
			m_image->draw(x, y, c - '0', view);
			x += (m_image->getWidth() + m_charSpacing);
		}
	}

	void BitMapNumFont::draw(const std::string& text, const glm::vec2& position, const glm::vec4& color, const glm::mat4& view) const
	{
		draw(text, position.x, position.y, color, view);
	}
}