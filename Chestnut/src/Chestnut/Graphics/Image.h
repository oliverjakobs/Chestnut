#pragma once

#include "Renderer.h"

namespace chst
{
	enum RenderFlip
	{
		FLIP_NONE = 0,
		FLIP_HORIZONTAL = 1,
		FLIP_VERTICAL = 2
	};

	class CHESTNUT_API Image
	{
	protected:
		unsigned int m_vao;
		Texture* m_texture;

		float m_width;
		float m_height;

		int m_columns;
		int m_rows;

		RenderFlip m_flip;

		std::vector<GLfloat> getVertices(float w, float h, float fW, float fH);

		GLuint getIndex(unsigned int pos) const;
	public:
		Image(const std::string& filename, int rows = 1, int columns = 1);
		Image(const std::string& filename, float scale, int rows = 1, int columns = 1);
		Image(const std::string& filename, float width, float height, int rows = 1, int columns = 1);
		~Image();

		void setRenderFlip(RenderFlip flip);
		
		virtual void draw(float x, float y, int frame = 0, const glm::mat4& view = Renderer::GetViewMat(), const std::string& shader = "") const;
		virtual void draw(const glm::vec2& position, int frame = 0, const glm::mat4& view = Renderer::GetViewMat(), const std::string& shader = "") const;
		
		float getWidth() const;
		float getHeight() const;

		float getFrameWidth() const;
		float getFrameHeight() const;
	};
}