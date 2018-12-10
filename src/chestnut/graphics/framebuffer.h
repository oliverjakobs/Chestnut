#pragma once

#include "shader.h"

namespace chst
{
	class FrameBuffer
	{
	private:
		GLuint m_fbo;
		GLuint m_vao;
		GLuint m_texture;
		Shader* m_shader;

	public:
		FrameBuffer(Shader* shader, float w, float h);
		~FrameBuffer();

		void bind();
		void unbind();

		void draw();
	};
}