#pragma once

#include "chestnut2D.h"

using namespace chst;

class Frost : public Game
{
private:
	TileMap* m_map;
	Entity* m_entity;
public:
	Frost(const std::string& title, int width, int height, float viewW, float viewH);
	~Frost();

	void update(float deltaTime) override;
	void draw() override;
	void debugDraw();
};
