#include "Chestnut.h"

using namespace chst;

class Frost : public Game
{
public:
	Frost() //: Game("Frost", 1200, 800, 1200, 800)
	{

	}

	~Frost()
	{

	}

	void onUpdate() override
	{

	}
	
	void onRender() const override
	{

	}
};

chst::Game* chst::CreateGame()
{
	Log::Init("Frost");

	return new Frost();
}

