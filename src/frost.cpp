#include "frost.h"

using namespace chst;

Frost::Frost(const std::string& title, int width, int height, float viewW, float viewH)
	: Game("Tilemap", 800, 600, 8, 6)
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

	//m_body = new Body(8.0f, 4.8f, 0.6f, 1.2f);
	//m_body->setMap(m_map);
}

Frost::~Frost()
{
	
}

void Frost::update(float deltaTime)
{
	/*float movementSpeed = 8.0f;
	float jumpPower = 8.0f;

	float velocity = 0.0f;

	if (m_input->keyDown(GLFW_KEY_A))
		velocity += -1.0f;
	if (m_input->keyDown(GLFW_KEY_D))
		velocity += 1.0f;

	m_body->setVelocityX(velocity * movementSpeed);

	if (m_input->keyDown(GLFW_KEY_S))
		m_body->drop();

	if (m_input->keyDown(GLFW_KEY_SPACE) && m_body->collidesBottom())
		m_body->setVelocityY(jumpPower);
	else if (m_input->keyUp(GLFW_KEY_SPACE))
		if (m_body->getVelocity().y > 0)
			m_body->setVelocityY(m_body->getVelocity().y * 0.5f);
	
	if (m_input->mouseButtonHit(GLFW_MOUSE_BUTTON_LEFT))
	{
		glm::vec2 mouse = Renderer::getView()->fromScreen(m_input->getMousePosition());

		int x = m_map->getMapTileYAtPoint(mouse.x);
		int y = m_map->getMapTileYAtPoint(mouse.y);

		DEBUG_MESSAGE("Tile at: " << x << ", " << y << ": " << m_map->getTile(x, y)->type);
	}

	m_body->update(deltaTime);*/
}

void Frost::draw()
{	
	m_map->draw();

	//m_body->draw();
}

void Frost::debugDraw()
{
	m_map->debugDraw();
}
