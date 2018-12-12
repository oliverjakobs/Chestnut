#pragma once

#include "renderer.h"

namespace chst
{
	class FrameBuffer
	{
	private:
		GLuint m_fbo;
		GLuint m_vao;
		Texture* m_texture;
	public:
		FrameBuffer();
		~FrameBuffer();

		void bind();
		void unbind();

		void draw();
	};
}