#pragma once

#include <glad\glad.h>

#include "api.h"

namespace chst
{
	class CHESTNUT_API Texture
	{
	private:
		GLuint m_textureID;

		int m_width;
		int m_height;
	public:
		Texture(int w, int h, GLubyte* pixels);
		Texture(const char* path, bool flipOnLoad);
		~Texture();
		
		void bind(GLuint slot = 0);
		void unbind();

		GLuint getTextureID() const;
		int getWidth() const;
		int getHeight() const;
	};
}