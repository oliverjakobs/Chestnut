#pragma once

#include "graphics.h"
#include "graphics\framebuffer.h"

using namespace chst;

enum TileType
{
	Empty = 0,
	Solid = 1,
	OneWay = 2,
	SlopeLeft = 3,
	SlopeRight = 4,
	CeilLeft = 5,
	CeilRight = 6
};

struct Tile
{
	unsigned int id;
	glm::vec2 position;
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

	FrameBuffer* m_frameBuffer;

	void updateFrameBuffer();
public:
	TileMap(const std::string& imagePath, int width, int height, float tileSize, const std::vector<int>& map);
	TileMap(const std::string& imagePath, int width, int height, float tileSize, const std::string& map);
	TileMap(const std::string& image, const std::string& map);
	~TileMap();

	void draw() const;
	void debugDraw() const;

	float getTileSize() const;

	glm::ivec2 getMapTileAtPoint(float x, float y) const;
	glm::ivec2 getMapTileAtPoint(const glm::vec2& pos) const;

	std::vector<Tile*> getAdjacentTiles(float x, float y, float w, float h);
	std::vector<Tile*> getAdjacentTiles(const glm::vec2& pos, const glm::vec2& size);

	Tile* getTile(int x, int y);
	Tile* getTile(const glm::ivec2& pos);
};