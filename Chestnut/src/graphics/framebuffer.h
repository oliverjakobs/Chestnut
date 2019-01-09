#pragma once

#include "renderer.h"

namespace chst
{
	class FrameBuffer
	{
	private:
		GLuint m_fbo;
		GLuint m_vao;

		int m_width;
		int m_height;

		glm::mat4 m_view;
		glm::mat4 m_model;

		Texture* m_texture;
	public:
		FrameBuffer(int w, int h);
		~FrameBuffer();

		void bind();
		void unbind();

		void draw();
		void toFile();

		glm::mat4 getView() const;
	};
}