#include "frost.h"

int main(int argc, char* argv[])
{
	Frost game("Tilemap", 1200, 900, 8, 6);

	for (int i = 0; i < argc; i++)
	{
		if (stringCompare(argv[i], "-fps"))
			game.showFPS(true);
		else if (stringCompare(argv[i], "-debug"))
			game.setDebug(true);
	}
		
	game.run();

	return 0;
}