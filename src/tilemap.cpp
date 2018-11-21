#include "tilemap.h"

#include "tools.h"

using namespace chestnut2D;

TileMap::TileMap(const std::string& tiles, float tileSize, unsigned int width, unsigned int  height)
	: m_width(width), m_height(height), m_tileSize(tileSize)
{
	m_image = new Image(tiles, tileSize, tileSize, 8, 8);

	std::vector<int> solidTiles = { 1, 2, 3, 8, 9, 11, 17, 18, 19 };
	std::vector<int> oneWayTiles = { 4, 5, 6 };

	auto lines = cutString(",", readFile("res/maps/tilemap.tile"));

	for (unsigned int i = 0; i < height; i++)
	{
		for (unsigned int j = 0; j < width; j++)
		{
			Tile tile;

			tile.posititon = glm::vec2(j, height - i - 1) * m_tileSize;
			tile.id = std::stoi(lines.at(i * width + j));

			if (contains<int>(solidTiles, tile.id))
				tile.type = Block;
			else if (contains<int>(oneWayTiles, tile.id))
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