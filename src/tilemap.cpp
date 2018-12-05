#include "tilemap.h"

#include "tools.h"

using namespace chst;

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
			else if (tile.id > 12)
				tile.type = OneWay;
			else if (tile.id > 0)
				tile.type = Solid;
			else
				tile.type = Empty;

			m_tiles.push_back(tile);
		}
	}
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
}

void TileMap::draw() const
{
	for (auto& tile : m_tiles)
	{
		m_image->draw(tile.position, tile.id);
	}
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
			Renderer::drawPolygon({ tile.position, tile.position + glm::vec2(m_tileSize, 0.0f),  tile.position + glm::vec2(0.0f, m_tileSize) }, BLUE);
		else if (tile.type == SlopeRight)
			Renderer::drawPolygon({ tile.position, tile.position + glm::vec2(m_tileSize, 0.0f),  tile.position + glm::vec2(m_tileSize) }, BLUE);
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