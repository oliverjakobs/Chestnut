#pragma once

#include "graphics.h"

using namespace chst;

enum TileType
{
	Empty = 0,
	Block = 1,
	OneWay = 2
};

struct Tile
{
	unsigned int id;
	glm::vec2 posititon;
	TileType type;
};

class TileMap
{
private:
	Image* m_image;

	unsigned int m_width;
	unsigned int m_height;

	float m_tileSize;

	std::vector<Tile> m_tiles;
public:
	TileMap(const std::string& image, const std::string& map);
	~TileMap();

	void draw() const;
	void debugDraw() const;

	float getTileSize() const;

	int getMapTileYAtPoint(float y);
	int getMapTileXAtPoint(float x);

	glm::ivec2 getMapTileAtPoint(float x, float y) const;

	std::vector<Tile*> getAdjacentTiles(float x, float y, float w, float h);
	std::vector<Tile*> getAdjacentTiles(const glm::vec2& pos, const glm::vec2& size);

	Tile* getTile(int x, int y);
};