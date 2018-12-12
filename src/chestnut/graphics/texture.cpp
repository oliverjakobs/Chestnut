#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "tools.h"

namespace chst
{
	Texture::Texture(int w, int h)
		: m_width(w), m_height(h)
	{
		glGenTextures(1, &m_textureID); glBindTexture(GL_TEXTURE_2D, m_textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

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

		unsigned char* data = stbi_load(path, &m_width, &m_height, &bpp, 4);

		if (data)
		{
			glBindTexture(GL_TEXTURE_2D, m_textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			stbi_image_free(data);
		}
		else
		{
			DEBUG_MESSAGE("[stb] Unable to load file: " << path);
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

	void Texture::loadAsIcon(const std::string& path, GLFWwindow* window)
	{
		if (path.empty())
			return;

		GLFWimage images[1];

		stbi_set_flip_vertically_on_load(true);

		images[0].pixels = stbi_load(path.c_str(), &images[0].width, &images[0].height, 0, 4); //rgba channels 
		glfwSetWindowIcon(window, 1, images);
		stbi_image_free(images[0].pixels); 
	}
}
