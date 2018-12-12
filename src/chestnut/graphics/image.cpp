#include "image.h"

#include "buffers.h"
#include "glm\gtc\matrix_transform.hpp"

namespace chst
{
	std::vector<GLfloat> Image::getVertices(float w, float h, float fW, float fH)
	{
		return 
		{
			0.0f, 0.0f, 0.0f, 0.0f,
			   w, 0.0f,   fW, 0.0f,
			   w,    h,   fW,   fH,
			0.0f,    h, 0.0f,   fH,
			// FLIP_HORIZONTAL
			0.0f, 0.0f,   fW, 0.0f,
			   w, 0.0f, 0.0f, 0.0f,
			   w,    h, 0.0f,   fH,
			0.0f,    h,   fW,   fH
		};
	}

	Image::Image(const std::string& filename, int rows, int columns)
		: m_columns(columns), m_rows(rows)
	{
		m_texture = new Texture(filename.c_str(), true);
		m_width = static_cast<float>(m_texture->getWidth());
		m_height = static_cast<float>(m_texture->getHeight());

		m_vao = createVertexArray();
				
		std::vector<GLfloat> vertices = getVertices(m_width, m_height, getFrameWidth(), getFrameHeight());

		createVertexBuffer(vertices.data(), vertices.size() * sizeof(GLfloat), BufferLayout({ { GL_FLOAT, 2 }, { GL_FLOAT, 2 } }));
	}

	Image::Image(const std::string& filename, float scale, int rows, int columns)
		: m_columns(columns), m_rows(rows)
	{
		m_texture = new Texture(filename.c_str(), true);
		m_width = m_texture->getWidth() * scale;
		m_height = m_texture->getHeight() * scale;

		m_vao = createVertexArray();

		std::vector<GLfloat> vertices = getVertices(m_width, m_height, getFrameWidth(), getFrameHeight());

		createVertexBuffer(vertices.data(), vertices.size() * sizeof(GLfloat), BufferLayout({ { GL_FLOAT, 2 },{ GL_FLOAT, 2 } }));
	}

	Image::Image(const std::string& filename, float width, float height, int rows, int columns)
		: m_width(width), m_height(height), m_columns(columns), m_rows(rows)
	{
		m_texture = new Texture(filename.c_str(), true);
		
		m_vao = createVertexArray();

		std::vector<GLfloat> vertices = getVertices(m_width, m_height, getFrameWidth(), getFrameHeight());

		createVertexBuffer(vertices.data(), vertices.size() * sizeof(GLfloat), BufferLayout({ { GL_FLOAT, 2 },{ GL_FLOAT, 2 } }));
	}

	Image::~Image()
	{
		SAFE_DELETE(m_texture);

		glDeleteBuffers(1, &m_vao);
	}

	void Image::setRenderFlip(RenderFlip flip)
	{
		m_flip = flip;
	}

	void Image::draw(float x, float y, int frame, const glm::mat4& view) const
	{
		draw(glm::vec2(x, y), WHITE, frame, view);
	}

	void Image::draw(float x, float y, const glm::vec4& colorMod, int frame, const glm::mat4& view) const
	{
		draw(glm::vec2(x, y), colorMod, frame, view);		
	}

	void Image::draw(const glm::vec2& position, int frame, const glm::mat4& view) const
	{
		draw(position, WHITE, frame, view);
	}

	void Image::draw(const glm::vec2& position, const glm::vec4& colorMod, int frame, const glm::mat4& view) const
	{
		float fX = (frame % m_columns) * getFrameWidth();
		float fY = 1 - getFrameHeight() - ((frame / m_columns) * getFrameHeight());
		
		glm::mat4 projection = glm::mat4();
		glm::mat4 model = glm::translate(glm::mat4(), glm::vec3(position, 0.0f));

		std::vector<GLuint> indices;

		switch (m_flip)
		{
		case FLIP_VERTICAL:
			indices = { 8,9,10,10,11,8 };
			break;
		case FLIP_HORIZONTAL:
			indices = { 4,5,6,6,7,4 };
			break;
		default:
			indices = { 0,1,2,2,3,0 };
			break;
		}

		glBindVertexArray(m_vao);
		Renderer::renderTexture(m_texture, glm::vec2(fX, fY), projection * view * model, indices);
	}

	float Image::getWidth() const
	{
		return m_width;
	}

	float Image::getHeight() const
	{
		return m_height;
	}

	float Image::getFrameWidth() const
	{
		return 1.0f / m_columns;
	}

	float Image::getFrameHeight() const
	{
		return 1.0f / m_rows;
	}
}