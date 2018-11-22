#pragma once

#include "chestnut2D.h"
#include "body.h"

using namespace chst;

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
