#define CHST_ENTRY_POINT
#include <Chestnut.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Sandbox2D.h"

using namespace chst;

class ExampleLayer : public Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f, true)
	{
		m_SquareVA = CreateRef<VertexArray>();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> squareVB;
		squareVB = CreateRef<VertexBuffer>(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIB;
		squareIB = CreateRef<IndexBuffer>(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVA->SetIndexBuffer(squareIB);

		m_FlatColorShader = CreateRef<Shader>("res/shaders/color.vert", "res/shaders/color.frag");
		m_TextureShader = CreateRef<Shader>("res/shaders/texture.vert", "res/shaders/texture.frag");

		m_Texture = CreateRef<Texture>("res/textures/Checkerboard.png");
		m_ChernoLogoTexture = CreateRef<Texture>("res/textures/ChernoLogo.png");

		m_TextureShader->Use();
		m_TextureShader->SetUniform1i("u_Texture", 0);
	}

	void OnUpdate(Timestep ts) override
	{
		m_CameraController.OnUpdate(ts);
	}

	void OnRender() override
	{
		Renderer::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		Renderer::Clear();

		Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		m_FlatColorShader->Use();
		m_FlatColorShader->SetUniform4f("u_Color", m_squareColor);

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

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Square Color", &m_squareColor[0]);
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
	glm::vec4 m_squareColor = glm::vec4(0.2f, 0.3f, 0.8f, 1.0f);
};

class Sandbox : public Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
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