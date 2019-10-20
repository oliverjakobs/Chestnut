#include "Sandbox2D.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Chestnut/Graphics/Renderer2D.h"

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_cameraController(chst::Application::GetWindow().GetAspectRatio())
{
	
}

void Sandbox2D::OnAttach()
{
	m_vertexArray = chst::CreateRef<chst::VertexArray>();

	float vertices[3 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	chst::Ref<chst::VertexBuffer> vao;
	vao = chst::CreateRef<chst::VertexBuffer>(vertices, sizeof(vertices));
	vao->SetLayout({ 
		{ chst::ShaderDataType::Float3, "a_Position" }
	});
	m_vertexArray->AddVertexBuffer(vao);

	uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
	chst::Ref<chst::IndexBuffer> ibo;
	ibo = chst::CreateRef<chst::IndexBuffer>(indices, sizeof(indices) / sizeof(uint32_t));
	m_vertexArray->SetIndexBuffer(ibo);

	m_shader = chst::CreateRef<chst::Shader>("res/shaders/color.vert", "res/shaders/color.frag");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(chst::Timestep ts)
{
	m_cameraController.OnUpdate(ts);
}

void Sandbox2D::OnRender()
{
	chst::Renderer::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	chst::Renderer::Clear();

	chst::Renderer2D::BeginScene(m_cameraController.GetCamera());

	chst::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });

	chst::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", &m_squareColor[0]);
	ImGui::End();
}

void Sandbox2D::OnEvent(chst::Event& e)
{
	m_cameraController.OnEvent(e);
}
