#include "Chestnut.h"
#include "Chestnut\Components.h"

using namespace chst;

class Frost : public Game
{
private:
	TileMap* m_map;
	Entity* m_entity;
public:
	Frost() : Game("Frost", 1200, 800, 800, 600)
	{
		Renderer::AddShader("default", new Shader("res/shader/shader.vert", "res/shader/shader.frag"));

		Renderer::SetClearColor(0.2, 0.2, 0.2, 1.0);
		Renderer::EnableBlend(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		setExitKey(GLFW_KEY_ESCAPE);
		
		//m_map = new TileMap("res/images/tiles.png", 20, 15, 0.4f, "res/maps/map.txt");
		m_map = new TileMap("res/images/tiles.png", 60, 30, 20, "res/maps/map2.txt");

		m_entity = new Entity("player", 400, 300, 20, 20);

		m_entity->addComponent(new PhysicsComponent(m_map->createBody(400, 300, 30, 60)));
		m_entity->addComponent(new AnimationComponent(new Image("res/images/player.png", 40, 60, 4, 6),
			{
				AnimationDef("idle", new Animation(0, 4, 0.2f)),
				AnimationDef("walk", new Animation(6, 6, 0.125f)),
				AnimationDef("jump", new Animation(12, 3, 0.3f)),
				AnimationDef("fall", new Animation(18, 2, 0.4f))
			}));
		m_entity->addComponent(new PlayerComponent(400, 800));
	}

	~Frost()
	{
		SAFE_DELETE(m_map);
		SAFE_DELETE(m_entity);
	}

	void onUpdate() override
	{
		if (Input::MouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			glm::vec2 mouse = Renderer::GetView()->fromScreen(Input::MousePosition());
			
			if (m_map->getTile(mouse)->type == Empty)
				m_map->changeTile(mouse, 18, Solid);
			else if (m_map->getTile(mouse)->id == 18)
				m_map->changeTile(mouse, 0, Empty);
		}

		if (Input::MouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
		{
			glm::ivec2 pos = m_map->getTilePos(Renderer::GetView()->fromScreen(Input::MousePosition()));

			CHST_INFO("Mouse: {}, {}", pos.x, pos.y);
		}

		m_map->onUpdate();

		m_entity->onInput();
		m_entity->onUpdate();
	}
	
	void onRender() const override
	{
		m_map->onRender();
		m_entity->onRender();

		m_map->onRenderDebug();
		m_entity->onRenderDebug();
	}
};

chst::Game* chst::CreateGame()
{
	Log::Init("Frost");

	return new Frost();
}

