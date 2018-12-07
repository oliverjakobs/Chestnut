#include "tilemap.h"

#include "tools.h"

#include "graphics\buffers.h"
#include "glm\gtc\matrix_transform.hpp"

using namespace chst;

void TileMap::loadFrameBuffer(float w, float h)
{
	m_shader = new Shader(readFile("res/shader/framebuffer.vert").c_str(), readFile("res/shader/framebuffer.frag").c_str());

	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
							 // positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};

	unsigned int quadVBO;
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	glGenFramebuffers(1, &m_fbo);

	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);

	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
																								 
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		DEBUG_MESSAGE("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void TileMap::updateFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto& tile : m_tiles)
	{
		m_image->draw(tile.position, tile.id);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
}

void TileMap::deleteFrameBuffer()
{
	glDeleteTextures(1, &m_texture);
	glDeleteBuffers(1, &m_vao);
	glDeleteFramebuffers(1, &m_fbo);
}

TileMap::TileMap(const std::string& imagePath, int width, int height, float tileSize, const std::vector<int>& map)
{
	m_width = width;
	m_height = height;

	m_tileSize = tileSize;

	m_image = new Image(imagePath, m_tileSize, m_tileSize, 3, 8);

	for (unsigned int i = 0; i < m_height; i++)
	{
		for (unsigned int j = 0; j < m_width; j++)
		{
			Tile tile;

			tile.position = glm::vec2(j, m_height - (i + 1)) * m_tileSize;
			tile.id = map.at(i * m_width + j);

			m_tiles.push_back(tile);
		}
	}
}

TileMap::TileMap(const std::string& imagePath, int width, int height, float tileSize, const std::string& map)
{
	m_width = width;
	m_height = height;

	m_tileSize = tileSize;

	m_image = new Image(imagePath, m_tileSize, m_tileSize, 3, 8);

	auto tiles = cutString(",", readFile(map.c_str()));

	for (unsigned int i = 0; i < m_height; i++)
	{
		for (unsigned int j = 0; j < m_width; j++)
		{
			Tile tile;

			tile.position = glm::vec2(j, m_height - (i + 1)) * m_tileSize;
			tile.id = std::stoi(tiles.at(i * m_width + j));

			if (tile.id == 9)
				tile.type = SlopeLeft;
			else if (tile.id == 10)
				tile.type = SlopeRight;
			else if (tile.id == 11)
				tile.type = Empty;
			else if (tile.id == 12)
				tile.type = Empty;
			else if (tile.id == 13 || tile.id == 14 || tile.id == 15)
				tile.type = OneWay;
			else if (tile.id == 0)
				tile.type = Empty;
			else
				tile.type = Solid;

			m_tiles.push_back(tile);
		}
	}

	loadFrameBuffer(Renderer::getWindowWidth(), Renderer::getWindowHeight());

	updateFrameBuffer();
}

TileMap::TileMap(const std::string& image, const std::string& map)
{
	auto parts = cutString("[Map]", readFile(map.c_str()));

	auto lines = cutString("\n", parts[0]);

	m_width = std::stoi(cutString(" ", lines[0])[1]);
	m_height = std::stoi(cutString(" ", lines[1])[1]);
	m_tileSize = std::stof(cutString(" ", lines[2])[1]);

	auto solidTiles = cutString(" ", lines[3]);
		
	auto oneWayTiles = cutString(" ", lines[4]);

	m_image = new Image(image, m_tileSize, m_tileSize, 8, 8);

	auto tiles = cutString(",", parts[1]);

	for (unsigned int i = 0; i < m_height; i++)
	{
		for (unsigned int j = 0; j < m_width; j++)
		{
			Tile tile;

			tile.position = glm::vec2(j, m_height - i - 1) * m_tileSize;
			tile.id = std::stoi(tiles.at(i * m_width + j));

			if (contains<std::string>(solidTiles, toString(tile.id)))
				tile.type = Solid;
			else if (contains<std::string>(oneWayTiles, toString(tile.id)))
				tile.type = OneWay;
			else
				tile.type = Empty;

			m_tiles.push_back(tile);
		}
	}

}

TileMap::~TileMap()
{
	SAFE_DELETE(m_image);

	m_tiles.clear();

	deleteFrameBuffer();
}

void TileMap::draw() const
{
	glm::mat4 model = glm::translate(glm::mat4(), glm::vec3(0.0f));
	
	//Renderer::renderTexture(m_vao, m_texture, glm::vec2(), glm::mat4(), Renderer::getViewMat());

	m_shader->enable();
	glBindVertexArray(m_vao);
	glBindTexture(GL_TEXTURE_2D, m_texture);	// use the color attachment texture as the texture of the quad plane
	glDrawArrays(GL_TRIANGLES, 0, 6);

}

void TileMap::debugDraw() const
{
	for (auto& tile : m_tiles)
	{
		if (tile.type == Solid)
			Renderer::drawRect(tile.position.x, tile.position.y, m_tileSize, m_tileSize, RED);
		else if (tile.type == OneWay)
			Renderer::drawRect(tile.position.x, tile.position.y, m_tileSize, m_tileSize, BLUE);
		else if (tile.type == SlopeLeft)
			Renderer::drawPolygon({ tile.position, tile.position + glm::vec2(m_tileSize, 0.0f),  tile.position + glm::vec2(0.0f, m_tileSize) }, MAGENTA);
		else if (tile.type == SlopeRight)
			Renderer::drawPolygon({ tile.position, tile.position + glm::vec2(m_tileSize, 0.0f),  tile.position + glm::vec2(m_tileSize) }, MAGENTA);
	}
}

float TileMap::getTileSize() const
{
	return m_tileSize;
}

glm::ivec2 TileMap::getMapTileAtPoint(float x, float y) const
{
	return glm::ivec2(static_cast<int>(std::floor(x / m_tileSize)), static_cast<int>(std::floor(y / m_tileSize)));
}

glm::ivec2 TileMap::getMapTileAtPoint(const glm::vec2 & pos) const
{
	return getMapTileAtPoint(pos.x, pos.y);
}

std::vector<Tile*> TileMap::getAdjacentTiles(float x, float y, float w, float h)
{
	std::vector<Tile*> tiles;

	glm::ivec2 start = getMapTileAtPoint(x, y);
	glm::ivec2 end = getMapTileAtPoint(x + w, y + h);

	for (int i = start.x; i <= end.x; i++)
	{
		for (int j = start.y; j <= end.y; j++)
		{			
			Tile* t = getTile(i, j);

			if (t != nullptr)
				tiles.push_back(t);
		}
	}

	return tiles;
}

std::vector<Tile*> TileMap::getAdjacentTiles(const glm::vec2& pos, const glm::vec2& size)
{
	return getAdjacentTiles(pos.x, pos.y, size.x, size.y);
}

Tile* TileMap::getTile(int x, int y)
{
	if (x < 0 || x >= m_width || y < 0 || y >= m_height)
		return nullptr;

	return &m_tiles.at((m_height - y - 1) * m_width + x);
}

Tile* TileMap::getTile(const glm::ivec2& pos)
{
	return getTile(pos.x, pos.y);
}
