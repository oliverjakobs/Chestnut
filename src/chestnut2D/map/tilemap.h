#pragma once

#include "graphics.h"
#include "physics\body.h"

namespace chestnut2D
{
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
		Image* m_tiles;

		unsigned int  m_width;
		unsigned int  m_height;

		float m_tileSize;

		std::vector<Tile> m_map;
		std::vector<int> m_solidTiles;
	public:
		TileMap(const std::string& tiles, float tileSize, unsigned int width, unsigned int  height);
		~TileMap();

		void draw();

		float getTileSize() const;

		int getMapTileYAtPoint(float y);
		int getMapTileXAtPoint(float x);

		TileType getTileType(int x, int y) const;
		bool isObstacle(int x, int y) const;
		bool isGround(int x, int y) const;
		bool isOneWay(int x, int y) const;
		bool isEmtpy(int x, int y) const;
	};
}