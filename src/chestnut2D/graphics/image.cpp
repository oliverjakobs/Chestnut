#include "image.h"

#include "buffers.h"
#include "glm\gtc\matrix_transform.hpp"

namespace chestnut2D
{
	Image::Image(const std::string& filename, int rows, int columns)
	{
		if (!filename.empty())
			m_texture = Renderer::createTexture(filename.c_str(), &m_width, &m_height, true);

		m_vao = createVertexArray();

		m_frameWidth = 1.0f / columns;
		m_frameHeight = 1.0f / rows;

		m_columns = columns;
		m_rows = rows;

		GLfloat vertices[]
		{
			0.0f, 0.0f, 0.0f, 0.0f,
			m_width, 0.0f, m_frameWidth, 0.0f,
			m_width, m_height, m_frameWidth, m_frameHeight,
			0.0f, m_height,	0.0f, m_frameHeight
		};

		createVertexBuffer(vertices, sizeof(vertices), BufferLayout(
			{
				{ GL_FLOAT, 2 },
				{ GL_FLOAT, 2 }
			}));

		GLuint indices[] = { 0,1,2,2,3,0 };

		createIndexBuffer(indices, 6);
	}

	Image::Image(const std::string& filename, float scale, int rows, int columns)
	{
		if (!filename.empty())
			m_texture = Renderer::createTexture(filename.c_str(), &m_width, &m_height, true);

		m_width *= scale;
		m_height *= scale;

		m_vao = createVertexArray();

		m_frameWidth = 1.0f / columns;
		m_frameHeight = 1.0f / rows;

		m_columns = columns;
		m_rows = rows;

		GLfloat vertices[]
		{
			0.0f, 0.0f, 0.0f, 0.0f,
			m_width, 0.0f, m_frameWidth, 0.0f,
			m_width, m_height, m_frameWidth, m_frameHeight,
			0.0f, m_height,	0.0f, m_frameHeight
		};

		createVertexBuffer(vertices, sizeof(vertices), BufferLayout(
			{
				{ GL_FLOAT, 2 },
				{ GL_FLOAT, 2 }
			}));

		GLuint indices[] = { 0,1,2,2,3,0 };

		createIndexBuffer(indices, 6);
	}

	Image::Image(const std::string& filename, float width, float height, int rows, int columns)
		: m_width(width), m_height(height)
	{
		if (!filename.empty())
			m_texture = Renderer::createTexture(filename.c_str(), nullptr, nullptr, true);
		
		m_vao = createVertexArray();

		m_frameWidth = 1.0f / columns;
		m_frameHeight = 1.0f / rows;

		m_columns = columns;
		m_rows = rows;

		GLfloat vertices[]
		{
			0.0f, 0.0f, 0.0f, 0.0f,
			m_width, 0.0f, m_frameWidth, 0.0f,
			m_width, m_height, m_frameWidth, m_frameHeight,
			0.0f, m_height,	0.0f, m_frameHeight
		};

		createVertexBuffer(vertices, sizeof(vertices), BufferLayout(
			{
				{ GL_FLOAT, 2 },
				{ GL_FLOAT, 2 }
			}));

		GLuint indices[] = { 0,1,2,2,3,0 };

		createIndexBuffer(indices, 6);
	}

	Image::~Image()
	{
		//SDL_DestroyTexture(m_texture);
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
		float fX = (frame % m_columns) * m_frameWidth;
		float fY = (frame / m_columns) * m_frameHeight;

		glm::mat4 model = glm::mat4();

		switch (m_flip)
		{
		case FLIP_HORIZONTAL:
			model = glm::translate(model, glm::vec3(position.x + m_width, position.y, 0.0f));
			model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
			break;
		case FLIP_VERTICAL:

			break;
		default:
			model = glm::translate(model, glm::vec3(position, 0.0f));
			break;
		}

		Renderer::renderTexture(m_vao, m_texture, glm::vec2(fX, fY), model, view);
	}

	float Image::getWidth() const
	{
		return m_width;
	}

	float Image::getHeight() const
	{
		return m_height;
	}
}