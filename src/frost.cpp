#include "frost.h"

using namespace chst;

Frost::Frost(const std::string& title, int width, int height, float viewW, float viewH)
	: Game(title, width, height, viewW, viewH)
{
	Renderer::addShader("default", new Shader("res/shader/shader.vert", "res/shader/shader.frag"), DEFAULT);
	Renderer::addShader("kernel", new Shader("res/shader/shader.vert", "res/shader/kernel.frag"), KERNEL);

	Renderer::setClearColor(glm::vec4(0.2, 0.2, 0.2, 1.0));

	setExitKey(GLFW_KEY_ESCAPE);
	setDebugKey(GLFW_KEY_F7);
	
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

Frost::~Frost()
{
	
}

void Frost::update(float deltaTime)
{
	if (m_input->mouseButtonHit(GLFW_MOUSE_BUTTON_LEFT))
	{
		glm::vec2 mouse = Renderer::getView()->fromScreen(m_input->getMousePosition());

		if (m_map->getTile(mouse)->type == Empty)
			m_map->changeTile(mouse, 18, Solid);
		else if (m_map->getTile(mouse)->id == 18)
			m_map->changeTile(mouse, 0, Empty);
	}
	
	m_map->update(deltaTime);

	m_entity->handleInput(m_input);

	m_entity->update(deltaTime);
}

void Frost::draw()
{	
	m_map->draw();

	m_entity->draw();
}

void Frost::debugDraw()
{
	m_map->debugDraw();

	m_entity->debugDraw();
}
