#include "framebuffer.h"

#include "buffers.h"

#include "tools.h"

namespace chst
{
	FrameBuffer::FrameBuffer(Shader* shader, float w, float h)
		: m_shader(shader)
	{
		float vertices[]
		{
			-1.0f, -1.0f, 0.0f, 0.0f,
			1.0f, -1.0f, 1.0f, 0.0f,
			1.0f,  1.0f, 1.0f, 1.0f,
			-1.0f,  1.0f, 0.0f, 1.0f
		};

		m_vao = createVertexArray();
		createVertexBuffer(vertices, sizeof(vertices), BufferLayout({ { GL_FLOAT, 2 },{ GL_FLOAT, 2 } }));

		GLuint indices[] = { 0,1,2,2,3,0 };

		createIndexBuffer(indices, 6);

		glGenFramebuffers(1, &m_fbo);

		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);

		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			DEBUG_MESSAGE("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	FrameBuffer::~FrameBuffer()
	{
		glDeleteTextures(1, &m_texture);
		glDeleteBuffers(1, &m_vao);
		glDeleteFramebuffers(1, &m_fbo);
	}

	void FrameBuffer::bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	}

	void FrameBuffer::unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::draw()
	{
		m_shader->enable();
		glBindVertexArray(m_vao);
		glBindTexture(GL_TEXTURE_2D, m_texture);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}
