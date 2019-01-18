#include "chstpch.h"
#include "Framebuffer.h"

#include "Buffers.h"

#include "glm\gtc\matrix_transform.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <stdlib.h>  

namespace chst
{
	FrameBuffer::FrameBuffer(int w, int h)
		: m_width(w), m_height(h)
	{
		m_view = glm::ortho(0.0f, (float)w, 0.0f, (float)h, 1.0f, -1.0f);

		float vertices[]
		{
			// normal
			-1.0f, -1.0f, 0.0f, 0.0f,
			 1.0f, -1.0f, 1.0f, 0.0f,
			 1.0f,  1.0f, 1.0f, 1.0f,
			-1.0f,  1.0f, 0.0f, 1.0f
		};

		m_vao = createVertexArray();
		createVertexBuffer(vertices, sizeof(vertices), BufferLayout({ { GL_FLOAT, 2 },{ GL_FLOAT, 2 } }));
		
		glGenFramebuffers(1, &m_fbo);

		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

		m_texture = new Texture(w, h, nullptr);

		m_model = glm::translate(glm::mat4(), glm::vec3(m_width / 2.0f, m_height / 2.0f, 0.0f));
		m_model = glm::scale(m_model, glm::vec3(m_width / 2.0f, m_height / 2.0f, 0.0f));

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture->getTextureID(), 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			CHST_CORE_ERROR("Framebuffer is not complete!");
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
		glViewport(0, 0, m_width, m_height);
	}

	void FrameBuffer::unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, Renderer::GetWindowWidth(), Renderer::GetWindowHeight());
	}

	void FrameBuffer::draw()
	{
		glBindVertexArray(m_vao);
				
		Renderer::RenderTextureS(m_texture, glm::vec2(), Renderer::GetViewMat() * m_model, { 0,1,2,2,3,0 }, "default");
	}

	void FrameBuffer::toFile()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
		GLubyte* data = (GLubyte*)malloc(4 * m_width * m_height);

		if (data)
		{
			glReadPixels(0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}

		stbi_flip_vertically_on_write(1);

		stbi_write_bmp("res/images/tilemap.png", m_width, m_height, 4, data);

		free(data);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	glm::mat4 FrameBuffer::getView() const
	{
		return m_view;
	}
}
