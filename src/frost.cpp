#include "frost.h"

using namespace chestnut2D;

Frost::Frost(const std::string& title, int width, int height, float viewW, float viewH)
	: Game(title, width, height, viewW, viewH)
{
	Renderer::addShader("default", new Shader(readFile("res/shader/shader.vert").c_str(), readFile("res/shader/shader.frag").c_str()));
	Renderer::setClearColor(glm::vec4(0.2, 0.2, 0.2, 1.0));

	setExitKey(GLFW_KEY_ESCAPE);

	m_map = new TileMap("res/images/tiles.png", 0.4f, 40, 24);

	m_body = new Body(8.0f, 4.8f, 0.6f, 1.2f);
	m_body->setMap(m_map);
}

Frost::~Frost()
{
	
}

void Frost::update(float deltaTime)
{
	float movementSpeed = 12.0f;

	glm::vec2 velocity = glm::vec2();

	if (m_input->keyDown(GLFW_KEY_A))
		velocity += glm::vec2(-1.0f, 0.0f);
	if (m_input->keyDown(GLFW_KEY_D))
		velocity += glm::vec2(1.0f, 0.0f);
	if (m_input->keyDown(GLFW_KEY_S))
		velocity += glm::vec2(0.0f, -1.0f);
	if (m_input->keyDown(GLFW_KEY_W))
		velocity += glm::vec2(0.0f, 1.0f);

	m_body->setVelocity(velocity.x * movementSpeed, velocity.y * movementSpeed);
	
	if (m_input->mouseButtonHit(GLFW_MOUSE_BUTTON_LEFT))
	{
		glm::vec2 mouse = Renderer::getView()->fromScreen(m_input->getMousePosition());

		int x = m_map->getMapTileYAtPoint(mouse.x);
		int y = m_map->getMapTileYAtPoint(mouse.y);

		DEBUG_MESSAGE("Tile at: " << x << ", " << y << ": " << m_map->getTileType(x, y));
	}

	//if (m_input->keyDown(GLFW_KEY_SPACE))
		m_body->update(deltaTime);
}

void Frost::draw()
{	
	m_map->draw();

	m_body->draw();
}

void Frost::debugDraw()
{

}
