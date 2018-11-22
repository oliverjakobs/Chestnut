#include "buffers.h"

#include "gl.h"

namespace chst
{
	unsigned int LayoutElement::getSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:			return sizeof(GLfloat);
		case GL_UNSIGNED_INT:	return sizeof(GLuint);
		case GL_UNSIGNED_BYTE:	return sizeof(GLubyte);
		}

		return 0;
	}

	BufferLayout::BufferLayout(std::vector<std::pair<unsigned int, unsigned int>> layout)
		: m_stride(0)
	{
		for (auto& e : layout)
		{
			m_elements.push_back({ e.first, e.second, GL_FALSE });
			m_stride += e.second * LayoutElement::getSizeOfType(e.first);
		}
	}

	unsigned int createVertexArray()
	{
		unsigned int vao;

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		return vao;
	}

	unsigned int createVertexBuffer(const void* vertices, unsigned int size, const BufferLayout& layout)
	{
		unsigned int vbo;

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);

		const auto& elements = layout.getElements();

		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++)
		{
			const auto& element = elements[i];

			createVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset);
			offset += element.count * LayoutElement::getSizeOfType(element.type);
		}

		return vbo;
	}

	void createVertexAttribPointer(unsigned int index, unsigned int size, unsigned int type, unsigned int normalized, unsigned int stride, const void* pointer)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	}

	unsigned int createIndexBuffer(const unsigned int* indices, unsigned int count)
	{
		unsigned int ibo;

		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);

		return ibo;
	}
}