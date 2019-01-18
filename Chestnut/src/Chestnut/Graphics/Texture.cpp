#include "chstpch.h"
#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace chst
{
	Texture::Texture(int w, int h, GLubyte* pixels)
		: m_width(w), m_height(h)
	{
		glGenTextures(1, &m_textureID); glBindTexture(GL_TEXTURE_2D, m_textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	Texture::Texture(const char* path, bool flipOnLoad)
	{
		glGenTextures(1, &m_textureID);

		stbi_set_flip_vertically_on_load(flipOnLoad);

		m_width = 0;
		m_height = 0;
		int bpp;

		GLubyte* pixels = stbi_load(path, &m_width, &m_height, &bpp, 4);

		if (pixels)
		{
			glBindTexture(GL_TEXTURE_2D, m_textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			stbi_image_free(pixels);
		}
		else
		{
			CHST_CORE_ERROR("[stb] Unable to load file: %s", path);
		}
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_textureID);
	}

	void Texture::bind(GLuint slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_textureID);
	}

	void Texture::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	GLuint Texture::getTextureID() const
	{
		return m_textureID;
	}
	int Texture::getWidth() const
	{
		return m_width;
	}
	int Texture::getHeight() const
	{
		return m_height;
	}
}
