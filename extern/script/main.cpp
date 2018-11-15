#include "parser.h"

using namespace chestnutScript;

int main()
{
	Parser parser = Parser();

	parser.loadObjects(chestnut2D::read_file("chestnut.chst"));

	parser.print();

	int x;
	std::cin >> x;

	return 0;
}