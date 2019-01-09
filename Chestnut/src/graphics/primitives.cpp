#include "primitives.h"

#include "renderer.h"
#include "buffers.h"

#include "glm\gtc\type_ptr.hpp"
#include <assert.h>

#include "tools.h"

namespace chst
{
	struct GLRenderLines
	{
		enum { MaxVertices = 2 * 512 };

		glm::vec2 m_vertices[MaxVertices];
		glm::vec4 m_colors[MaxVertices];

		int m_count;

		GLuint m_vao;
		GLuint m_vbos[2];

		Shader* m_shader = nullptr;
		GLint m_viewLocation;

		void create(Shader* shader)
		{
			m_shader = shader;
			m_viewLocation = m_shader->getUniformLocation("view");

			// Generate
			m_vao = createVertexArray();

			// Vertex buffer
			m_vbos[0] = createVertexBuffer(m_vertices, sizeof(m_vertices), BufferLayout({}));
			createVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const void*)0);

			m_vbos[1] = createVertexBuffer(m_colors, sizeof(m_colors), BufferLayout({}));
			createVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const void*)0);

			// Cleanup
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			m_count = 0;
		}

		void destroy()
		{
			if (m_vao)
			{
				glDeleteVertexArrays(1, &m_vao);
				glDeleteBuffers(2, m_vbos);
			}

			SAFE_DELETE(m_shader);
		}

		void vertex(const glm::vec2& v, const glm::vec4& c, const glm::mat4& view)
		{
			if (m_count == MaxVertices)
				flush(view);

			m_vertices[m_count] = v;
			m_colors[m_count] = c;
			m_count++;
		}

		void flush(const glm::mat4& view)
		{
			if (m_count == 0)
				return;

			m_shader->enable();
			m_shader->setUniformMat4(m_viewLocation, Renderer::getViewMat());

			glBindVertexArray(m_vao);

			glBindBuffer(GL_ARRAY_BUFFER, m_vbos[0]);
			glBufferSubData(GL_ARRAY_BUFFER, 0, m_count * sizeof(glm::vec2), m_vertices);

			glBindBuffer(GL_ARRAY_BUFFER, m_vbos[1]);
			glBufferSubData(GL_ARRAY_BUFFER, 0, m_count * sizeof(glm::vec4), m_colors);

			glDrawArrays(GL_LINES, 0, m_count);

			m_count = 0;
		}
	};


	struct GLRenderTriangles
	{
		enum { MaxVertices = 3 * 512 };

		glm::vec2 m_vertices[MaxVertices];
		glm::vec4 m_colors[MaxVertices];

		int m_count;

		GLuint m_vao;
		GLuint m_vbos[2];

		Shader* m_shader = nullptr;
		GLint m_viewLocation;

		void create(Shader* shader)
		{
			m_shader = shader;
			m_viewLocation = m_shader->getUniformLocation("view");

			// Generate
			m_vao = createVertexArray();
			glGenBuffers(2, m_vbos);

			// Vertex buffer
			m_vbos[0] = createVertexBuffer(m_vertices, sizeof(m_vertices), BufferLayout({}));
			createVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const void*)0);

			m_vbos[1] = createVertexBuffer(m_colors, sizeof(m_colors), BufferLayout({}));
			createVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const void*)0);

			// Cleanup
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			m_count = 0;
		}

		void destroy()
		{
			if (m_vao)
			{
				glDeleteVertexArrays(1, &m_vao);
				glDeleteBuffers(2, m_vbos);
			}

			SAFE_DELETE(m_shader);
		}

		void vertex(const glm::vec2& v, const glm::vec4& c, const glm::mat4& view)
		{
			if (m_count == MaxVertices)
				flush(view);

			m_vertices[m_count] = v;
			m_colors[m_count] = c;
			m_count++;
		}

		void flush(const glm::mat4& view)
		{
			if (m_count == 0)
				return;

			m_shader->enable();
			m_shader->setUniformMat4(m_viewLocation, view);

			glBindVertexArray(m_vao);

			glBindBuffer(GL_ARRAY_BUFFER, m_vbos[0]);
			glBufferSubData(GL_ARRAY_BUFFER, 0, m_count * sizeof(glm::vec2), m_vertices);

			glBindBuffer(GL_ARRAY_BUFFER, m_vbos[1]);
			glBufferSubData(GL_ARRAY_BUFFER, 0, m_count * sizeof(glm::vec4), m_colors);

			glDrawArrays(GL_TRIANGLES, 0, m_count);

			m_count = 0;
		}
	};

	Primitives::Primitives()
	{
		m_lines = NULL;
		m_triangles = NULL;
	}

	Primitives::~Primitives()
	{
		assert(m_lines == NULL);
		assert(m_triangles == NULL);
	}

	void Primitives::create(Shader* shader)
	{
		m_lines = new GLRenderLines();
		m_lines->create(shader);

		m_triangles = new GLRenderTriangles();
		m_triangles->create(shader);
	}

	void Primitives::destroy()
	{
		m_lines->destroy();
		delete m_lines;
		m_lines = NULL;

		m_triangles->destroy();
		delete m_triangles;
		m_triangles = NULL;
	}

	void Primitives::flush(const glm::mat4& view)
	{
		m_lines->flush(view);
		m_triangles->flush(view);
	}

	void Primitives::drawLine(const glm::vec2& start, const glm::vec2& end, const glm::vec4& color, const glm::mat4& view) const
	{
		m_lines->vertex(start, color, view);
		m_lines->vertex(end, color, view);
	}

	void Primitives::drawPolygon(const std::vector<glm::vec2>& vertices, const glm::vec4& color, const glm::mat4& view) const
	{
		glm::vec2 p1 = vertices.back();

		for (auto& p2 : vertices)
		{
			m_lines->vertex(p1, color, view);
			m_lines->vertex(p2, color, view);
			p1 = p2;
		}
	}

	void Primitives::fillPolygon(const std::vector<glm::vec2>& vertices, const glm::vec4& color, const glm::mat4& view) const
	{
		for (unsigned int i = 1; i < vertices.size() - 1; ++i)
		{
			m_triangles->vertex(vertices[0], color, view);
			m_triangles->vertex(vertices[i], color, view);
			m_triangles->vertex(vertices[i + 1], color, view);
		}
	}

	void Primitives::fillCircle(const glm::vec2& center, float radius, const glm::vec4& color, const glm::mat4& view) const
	{
		const float k_segments = 36;
		const float k_increment = 2.0f * M_PI / k_segments;
		float sinInc = sinf(k_increment);
		float cosInc = cosf(k_increment);
		glm::vec2 v0 = center;
		glm::vec2 r1(cosInc, sinInc);
		glm::vec2 v1 = center + radius * r1;

		for (int i = 0; i < k_segments; ++i)
		{
			// Perform rotation to avoid additional trigonometry.
			glm::vec2 r2;
			r2.x = cosInc * r1.x - sinInc * r1.y;
			r2.y = sinInc * r1.x + cosInc * r1.y;
			glm::vec2 v2 = center + radius * r2;
			m_triangles->vertex(v0, color, view);
			m_triangles->vertex(v1, color, view);
			m_triangles->vertex(v2, color, view);
			r1 = r2;
			v1 = v2;
		}

		r1 = glm::vec2(1.0f, 0.0f);
		v1 = center + radius * r1;
		for (int i = 0; i < k_segments; ++i)
		{
			glm::vec2 r2;
			r2.x = cosInc * r1.x - sinInc * r1.y;
			r2.y = sinInc * r1.x + cosInc * r1.y;
			glm::vec2 v2 = center + radius * r2;
			m_lines->vertex(v1, color, view);
			m_lines->vertex(v2, color, view);
			r1 = r2;
			v1 = v2;
		}
	}

	void Primitives::drawCircle(const glm::vec2& center, float radius, const glm::vec4& color, const glm::mat4& view) const
	{
		const float k_segments = 36;
		const float k_increment = 2.0f * M_PI / k_segments;

		float sinInc = sinf(k_increment);
		float cosInc = cosf(k_increment);

		glm::vec2 r1(1.0f, 0.0f);
		glm::vec2 v1 = center + radius * r1;
		
		for (int i = 0; i < k_segments; ++i)
		{
			// Perform rotation to avoid additional trigonometry.
			glm::vec2 r2;
			r2.x = cosInc * r1.x - sinInc * r1.y;
			r2.y = sinInc * r1.x + cosInc * r1.y;
			glm::vec2 v2 = center + radius * r2;
			m_lines->vertex(v1, color, view);
			m_lines->vertex(v2, color, view);
			r1 = r2;
			v1 = v2;
		}
	}
}