#pragma once

#include "Chestnut\Game.h"
#include "Chestnut\Log.h"
#include "Chestnut\Graphics\View.h"

// ---Entry Point---------------------
extern chst::Game* chst::CreateGame();

int main(int argc, char** argv)
{
	auto game = chst::CreateGame();
	game->run();
	delete game;
}
// -----------------------------------