#include "framebuffer.h"

#include "buffers.h"

#include "tools.h"

namespace chst
{
	FrameBuffer::FrameBuffer()
	{
		float vertices[]
		{
			// normal
			-1.0f, -1.0f, 0.0f, 0.0f,
			 1.0f, -1.0f, 1.0f, 0.0f,
			 1.0f,  1.0f, 1.0f, 1.0f,
			-1.0f,  1.0f, 0.0f, 1.0f,
			// mirror
			-1.0f, -1.0f, 1.0f, 0.0f,
			 1.0f, -1.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 1.0f,
			-1.0f,  1.0f, 1.0f, 1.0f
		};

		m_vao = createVertexArray();
		createVertexBuffer(vertices, sizeof(vertices), BufferLayout({ { GL_FLOAT, 2 },{ GL_FLOAT, 2 } }));
		
		//createIndexBuffer(indices, 6);

		glGenFramebuffers(1, &m_fbo);

		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

		m_texture = new Texture(Renderer::getWindowWidth(), Renderer::getWindowHeight());

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture->getTextureID(), 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			DEBUG_MESSAGE("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	FrameBuffer::~FrameBuffer()
	{
		SAFE_DELETE(m_texture);
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
		glBindVertexArray(m_vao);
		Renderer::renderTexture(m_texture, glm::vec2(), glm::mat4(1.0f), { 0,1,2,2,3,0 });
	}
}
