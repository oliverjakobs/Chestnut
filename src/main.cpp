#include "frost.h"

int main(int argc, char* argv[])
{
	Frost game("Tilemap", 1200, 900, 8, 6);

	game.showFPS(true);
	game.setDebug(true);
	game.lockFPS(false);
		
	game.run();

	return 0;
}