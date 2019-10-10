#pragma once

#include <Chestnut.h>

class Sandbox2D : public chst::Layer
{
private:
	chst::OrthographicCameraController m_cameraController;

	chst::Ref<chst::VertexArray> m_vertexArray;
	chst::Ref<chst::Shader> m_shader;

	glm::vec4 m_squareColor = glm::vec4(0.2f, 0.3f, 0.8f, 1.0f);

public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(chst::Timestep ts) override;
	void OnRender() override;
	void OnImGuiRender() override;
	void OnEvent(chst::Event& e) override;
};