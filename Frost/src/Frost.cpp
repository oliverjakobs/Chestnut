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
		if (Input::KeyPressed(GLFW_KEY_W))
		{
			CHST_CORE_INFO("Up");
		}

		if (Input::KeyPressed(GLFW_KEY_A))
		{
			CHST_CORE_INFO("Left");
		}

		if (Input::KeyPressed(GLFW_KEY_S))
		{
			CHST_CORE_INFO("Down");
		}

		if (Input::KeyPressed(GLFW_KEY_D))
		{
			CHST_CORE_INFO("Right");
		}
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

