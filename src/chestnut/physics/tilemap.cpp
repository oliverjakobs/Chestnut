#include "tilemap.h"

#include "graphics\buffers.h"
#include "glm\gtc\matrix_transform.hpp"

namespace chst
{
	TileMap::TileMap(const std::string& imagePath, int width, int height, float tileSize, const std::vector<int>& map)
	{
		m_width = width;
		m_height = height;

		m_tileSize = tileSize;

		m_image = new Image(imagePath, m_tileSize, m_tileSize, 3, 8);

		for (int i = 0; i < m_height; i++)
		{
			for (int j = 0; j < m_width; j++)
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

		for (int i = 0; i < m_height; i++)
		{
			for (int j = 0; j < m_width; j++)
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
					tile.type = Platform;
				else if (tile.id == 0)
					tile.type = Empty;
				else
					tile.type = Solid;

				m_tiles.push_back(tile);
			}
		}

		m_frameBuffer = new FrameBuffer();

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

		for (int i = 0; i < m_height; i++)
		{
			for (int j = 0; j < m_width; j++)
			{
				Tile tile;

				tile.position = glm::vec2(j, m_height - i - 1) * m_tileSize;
				tile.id = std::stoi(tiles.at(i * m_width + j));

				if (contains<std::string>(solidTiles, toString(tile.id)))
					tile.type = Solid;
				else if (contains<std::string>(oneWayTiles, toString(tile.id)))
					tile.type = Platform;
				else
					tile.type = Empty;

				m_tiles.push_back(tile);
			}
		}

	}

	TileMap::~TileMap()
	{
		SAFE_DELETE(m_image);
		SAFE_DELETE(m_frameBuffer);

		m_tiles.clear();
	}

	void TileMap::updateFrameBuffer()
	{
		m_frameBuffer->bind();

		glClear(GL_COLOR_BUFFER_BIT);

		for (auto& tile : m_tiles)
		{
			m_image->draw(tile.position, tile.id);
		}

		m_frameBuffer->unbind();
	}

	void TileMap::update(float deltaTime)
	{
		if (m_changed)
		{
			updateFrameBuffer();
			m_changed = false;
		}
	}

	void TileMap::draw() const
	{
		m_frameBuffer->draw();
	}

	void TileMap::debugDraw() const
	{
		for (auto& tile : m_tiles)
		{
			if (tile.type == Solid)
				Renderer::drawRect(tile.position.x, tile.position.y, m_tileSize, m_tileSize, RED);
			else if (tile.type == Platform)
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

	glm::ivec2 TileMap::getTilePos(float x, float y) const
	{
		return glm::ivec2(static_cast<int>(std::floor(x / m_tileSize)), static_cast<int>(std::floor(y / m_tileSize)));
	}

	glm::ivec2 TileMap::getTilePos(const glm::vec2 & pos) const
	{
		return getTilePos(pos.x, pos.y);
	}

	std::vector<const Tile*> TileMap::getAdjacentTiles(float x, float y, float w, float h)
	{
		std::vector<const Tile*> tiles;

		glm::ivec2 start = getTilePos(x, y);
		glm::ivec2 end = getTilePos(x + w, y + h);

		for (int i = start.x; i <= end.x; i++)
		{
			for (int j = start.y; j <= end.y; j++)
			{
				const Tile* t = getTileM(i, j);

				if (t != nullptr)
					tiles.push_back(t);
			}
		}

		return tiles;
	}

	std::vector<const Tile*> TileMap::getAdjacentTiles(const glm::vec2& pos, const glm::vec2& size)
	{
		return getAdjacentTiles(pos.x, pos.y, size.x, size.y);
	}

	void TileMap::changeTile(const glm::vec2& pos, unsigned int id, TileType type)
	{
		changeTile(pos.x, pos.y, id, type);
	}

	void TileMap::changeTile(float x, float y, unsigned int id, TileType type)
	{
		glm::ivec2 pos = getTilePos(x, y);

		if (pos.x < 0 || pos.x >= m_width || pos.y < 0 || pos.y >= m_height)
			return;

		Tile* tile = &m_tiles.at((m_height - pos.y - 1) * m_width + pos.x);

		if (!(tile->id == id || tile->type == type))
		{
			tile->id = id;
			tile->type = type;
			m_changed = true;
		}
	}

	const Tile* TileMap::getTile(float x, float y) const
	{
		return getTileM(getTilePos(x, y));
	}

	const Tile* TileMap::getTile(const glm::vec2& pos) const
	{
		return getTile(pos.x, pos.y);
	}

	const Tile* TileMap::getTileM(int x, int y) const
	{
		if (x < 0 || x >= m_width || y < 0 || y >= m_height)
			return nullptr;

		return &m_tiles.at((m_height - y - 1) * m_width + x);
	}

	const Tile* TileMap::getTileM(const glm::ivec2& pos) const
	{
		return getTileM(pos.x, pos.y);
	}
}