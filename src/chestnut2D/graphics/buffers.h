#pragma once

#include <vector>

namespace chestnut2D
{
	struct LayoutElement
	{
		unsigned int type;
		unsigned int count;
		unsigned int normalized;

		static unsigned int getSizeOfType(unsigned int type);
	};

	class BufferLayout
	{
	private:
		std::vector<LayoutElement> m_elements;
		unsigned int m_stride;
	public:
		BufferLayout(std::vector<std::pair<unsigned int, unsigned int>> layout);

		inline const std::vector<LayoutElement> getElements() const { return m_elements; }
		inline unsigned int getStride() const { return m_stride; }
	};

	unsigned int createVertexArray();

	unsigned int createVertexBuffer(const void* vertices, unsigned int size, const BufferLayout& layout);

	void createVertexAttribPointer(unsigned int index, unsigned int size, unsigned int type, unsigned int normalized, unsigned int stride, const void* pointer);

	unsigned int createIndexBuffer(const unsigned int* indices, unsigned int count);
}
