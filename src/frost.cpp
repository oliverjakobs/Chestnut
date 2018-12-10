#include "frost.h"

using namespace chst;

Frost::Frost(const std::string& title, int width, int height, float viewW, float viewH)
	: Game("Tilemap", 1200, 900, 8, 6)
{
	Renderer::addShader("default", new Shader(readFile("res/shader/shader.vert").c_str(), readFile("res/shader/shader.frag").c_str()));
	Renderer::setClearColor(glm::vec4(0.2, 0.2, 0.2, 1.0));

	setExitKey(GLFW_KEY_ESCAPE);
	setDebugKey(GLFW_KEY_F7);

	std::vector<int> map =
	{
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 1, 5, 5, 5, 5, 2, 0,
		0, 6, 0, 0, 0, 0, 6, 0,
		0, 6, 0, 0, 0, 0, 6, 0,
		0, 3, 5, 5, 5, 5, 4, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
	};

	m_map = new TileMap("res/images/tiles.png", 20, 15, 0.4f, "res/maps/map.txt");
	//m_map = new TileMap("res/images/tiles.png", 40, 30, 0.2f, "res/maps/map2.txt");

	m_body = new Body(m_map, 4.0f, 3.0f, 0.4f, 0.6f);
}

Frost::~Frost()
{
	
}

void Frost::update(float deltaTime)
{
	float movementSpeed = 4.0f;
	float jumpPower = 8.0f;

	glm::vec2 velocity = glm::vec2(0.0f, m_body->getVelocity().y);
	
	if (m_input->keyDown(GLFW_KEY_A))
		velocity.x += -movementSpeed;
	if (m_input->keyDown(GLFW_KEY_D))
		velocity.x += movementSpeed;

	if (m_input->keyDown(GLFW_KEY_SPACE) && m_body->collidesBottom())
		velocity.y = jumpPower;
	else if (m_input->keyUp(GLFW_KEY_SPACE))
		if (m_body->getVelocity().y > 0)
			velocity.y = (m_body->getVelocity().y * 0.5f);
	
	m_body->setVelocity(velocity);

	if (m_input->keyDown(GLFW_KEY_S))
		m_body->drop();

	if (m_input->mouseButtonHit(GLFW_MOUSE_BUTTON_LEFT))
	{
		glm::vec2 mouse = Renderer::getView()->fromScreen(m_input->getMousePosition());
		glm::ivec2 pos = m_map->getMapTileAtPoint(mouse);
		DEBUG_MESSAGE("Tile at: " << pos.x << ", " << pos.y << ": " << m_map->getTile(pos)->type);
	}

	m_body->update(deltaTime);
}

void Frost::draw()
{	
	m_map->draw();

	m_body->draw();
}

void Frost::debugDraw()
{
	m_map->debugDraw();
}
