#include "tilemap.h"

#include "tools.h"

using namespace chestnutPhysics;

namespace chestnut2D
{
	TileMap::TileMap(const std::string& tiles, float tileSize, unsigned int width, unsigned int  height)
		: m_width(width), m_height(height), m_tileSize(tileSize)
	{
		m_solidTiles = { 1,2,3,9,11,17,18,19 };

		m_tiles = new Image(tiles, tileSize, tileSize, 8, 8);

		auto lines = cutString(",", readFile("res/maps/tilemap.tile"));
		
		for (unsigned int i = 0; i < height; i++)
		{
			for (unsigned int j = 0; j < width; j++)
			{
				Tile tile;
				
				tile.posititon = glm::vec2(j, height - i - 1) * m_tileSize;
				tile.id = std::stoi(lines.at(i * width + j));

				if (tile.id > 0)
					tile.type = Block;
				else
					tile.type = Empty;

				m_map.push_back(tile);
			}
		}

	}

	TileMap::~TileMap()
	{
	}

	void TileMap::draw()
	{
		for (auto& tile : m_map)
		{
			m_tiles->draw(tile.posititon, tile.id);
			Renderer::drawRect(tile.posititon.x, tile.posititon.y, m_tileSize, m_tileSize, tile.type == Block ? RED : GREEN);
		}
	}

	float TileMap::getTileSize() const
	{
		return m_tileSize;
	}

	int TileMap::getMapTileYAtPoint(float y)
	{
		return static_cast<int>(std::floor(y / m_tileSize));
	}

	int TileMap::getMapTileXAtPoint(float x)
	{
		return static_cast<int>(std::floor(x / m_tileSize));
	}

	TileType TileMap::getTileType(int x, int y) const
	{
		if (x < 0 || x > m_width || y <= 0 || y >= m_height)
			return Block;

		return m_map.at(y * m_width + x).type;
	}

	bool TileMap::isObstacle(int x, int y) const
	{
		return (getTileType(x, y) == Block);
	}

	bool TileMap::isGround(int x, int y) const
	{
		return (getTileType(x, y) == OneWay || getTileType(x, y) == Block);
	}

	bool TileMap::isOneWay(int x, int y) const
	{
		return  (getTileType(x, y) == OneWay);
	}

	bool TileMap::isEmtpy(int x, int y) const
	{
		return  (getTileType(x, y) == Empty);
	}
}