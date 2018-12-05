#include "frost.h"

int main(int argc, char* argv[])
{
	Frost game("Frost", 1600, 960, 16.0f, 9.6f);

	game.showFPS(true);
	
	game.run();

	return 0;
}