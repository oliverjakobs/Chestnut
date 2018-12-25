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
		float m_scale;

		glm::mat4 m_view;

		Texture* m_texture;
	public:
		FrameBuffer(int w, int h, float scale);
		~FrameBuffer();

		void bind();
		void unbind(bool safe = false);

		void draw();

		glm::mat4 getView() const;
	};
}