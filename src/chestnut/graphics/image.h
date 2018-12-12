#pragma once

#include <string>
#include "renderer.h"

#include "glm\glm.hpp"

namespace chst
{
	enum RenderFlip
	{
		FLIP_NONE,
		FLIP_HORIZONTAL,
		FLIP_VERTICAL
	};

	class Image
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
	public:
		Image(const std::string& filename, int rows = 1, int columns = 1);
		Image(const std::string& filename, float scale, int rows = 1, int columns = 1);
		Image(const std::string& filename, float width, float height, int rows = 1, int columns = 1);
		~Image();

		void setRenderFlip(RenderFlip flip);
		
		virtual void draw(float x, float y, int frame = 0, const glm::mat4& view = Renderer::getViewMat()) const;
		virtual void draw(float x, float y, const glm::vec4& colorMod, int frame = 0, const glm::mat4& view = Renderer::getViewMat()) const;

		virtual void draw(const glm::vec2& position, int frame = 0, const glm::mat4& view = Renderer::getViewMat()) const;
		virtual void draw(const glm::vec2& position, const glm::vec4& colorMod, int frame = 0, const glm::mat4& view = Renderer::getViewMat()) const;
		
		float getWidth() const;
		float getHeight() const;

		float getFrameWidth() const;
		float getFrameHeight() const;
	};
}