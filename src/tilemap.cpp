#include "tilemap.h"

#include "tools.h"

using namespace chst;

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

			tile.posititon = glm::vec2(j, m_height - i - 1) * m_tileSize;
			tile.id = std::stoi(tiles.at(i * m_width + j));

			if (contains<std::string>(solidTiles, toString(tile.id)))
				tile.type = Block;
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
}

void TileMap::draw() const
{
	for (auto& tile : m_tiles)
	{
		m_image->draw(tile.posititon, tile.id);
	}
}

void TileMap::debugDraw() const
{
	for (auto& tile : m_tiles)
	{
		if (tile.type == Block)
			Renderer::drawRect(tile.posititon.x, tile.posititon.y, m_tileSize, m_tileSize, RED);
		else if (tile.type == OneWay)
			Renderer::drawRect(tile.posititon.x, tile.posititon.y, m_tileSize, m_tileSize, BLUE);
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

glm::ivec2 TileMap::getMapTileAtPoint(float x, float y) const
{
	return glm::ivec2(static_cast<int>(std::floor(x / m_tileSize)), static_cast<int>(std::floor(y / m_tileSize)));
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