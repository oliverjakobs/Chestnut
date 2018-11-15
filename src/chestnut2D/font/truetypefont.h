#pragma once

#include "font.h"

namespace chestnut2D
{
	struct Character 
	{
		GLuint     TextureID;  // ID handle of the glyph texture
		glm::ivec2 Size;       // Size of glyph
		glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
		GLuint     Advance;    // Offset to advance to next glyph
	};

	class TrueTypeFont : public Font
	{
	private:
		std::map<GLchar, Character> m_characters;

		GLuint VAO, VBO;
		Shader* m_shader;
	public:
		TrueTypeFont(const std::string& path, unsigned int size);
		~TrueTypeFont();

		void draw(const std::string& text, float x, float y, const glm::vec4& color, const glm::mat4& view) const override;
		void draw(const std::string& text, const glm::vec2& position, const glm::vec4& color, const glm::mat4& view) const override;

	};
}