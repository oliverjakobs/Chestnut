#pragma once

#include "chestnut2D.h"
#include "map\tilemap.h"

#include "physics\physics.h"

using namespace chestnut2D;
using namespace chestnutPhysics;

class Frost : public Game
{
private:
	TileMap* m_map;
	Body* m_body;
public:
	Frost(const std::string& title, int width, int height, float viewW, float viewH);
	~Frost();

	void update(float deltaTime) override;
	void draw() override;
	void debugDraw();
};
