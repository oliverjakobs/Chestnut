#pragma once

#include "gl.h"

#include <string>

namespace chst
{
	class Texture
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

		static void loadAsIcon(const std::string& path, GLFWwindow* window);
	};
}