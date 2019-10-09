#include <Chestnut.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace chst;

class ExampleLayer : public Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f, true)
	{
		m_SquareVA.reset(new VertexArray());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> squareVB;
		squareVB.reset(new VertexBuffer(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIB;
		squareIB.reset(new IndexBuffer(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		m_FlatColorShader = std::make_shared<Shader>("res/shaders/color.vert", "res/shaders/color.frag");
		m_TextureShader = std::make_shared<Shader>("res/shaders/texture.vert", "res/shaders/texture.frag");

		m_Texture = std::make_shared<Texture>("res/textures/Checkerboard.png");
		m_ChernoLogoTexture = std::make_shared<Texture>("res/textures/ChernoLogo.png");

		m_TextureShader->Use();
		m_TextureShader->SetUniform1i("u_Texture", 0);
	}

	void OnUpdate(Timestep ts) override
	{
		// Update
		m_CameraController.OnUpdate(ts);

		// Render
		Renderer::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		Renderer::Clear();

		Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		m_FlatColorShader->Use();
		m_FlatColorShader->SetUniform3f("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(x * 0.11f, y * 0.11f, 0.0f)) * scale;
				Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		m_Texture->Bind();
		Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_ChernoLogoTexture->Bind();
		Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", &m_SquareColor[0]);
		ImGui::End();
	}

	void OnEvent(Event& e) override
	{
		m_CameraController.OnEvent(e);
	}
private:
	Ref<Shader> m_FlatColorShader;
	Ref<Shader> m_TextureShader;

	Ref<VertexArray> m_SquareVA;

	Ref<Texture> m_Texture, m_ChernoLogoTexture;

	OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Application* chst::CreateApplication()
{
	obelisk::Logger::SetFormat("[%^%l%$] %v");
	obelisk::Logger::SetLevel(obelisk::LogLevel::Trace);

	return new Sandbox();
}