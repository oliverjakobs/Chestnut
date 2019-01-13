#pragma once

#include "Chestnut\Game.h"
#include "Chestnut\Log.h"

// ---Entry Point---------------------
extern chst::Game* chst::CreateGame();

int main(int argc, char** argv)
{
	auto game = chst::CreateGame();
	game->run();
	delete game;
}
// -----------------------------------