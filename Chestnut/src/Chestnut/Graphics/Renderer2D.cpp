#include "chstpch.h"
#include "Renderer2D.h"

#include <glad/glad.h>

#include "VertexArray.h"
#include "Shader.h"

namespace chst
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> VertexArray;
		Ref<Shader> Shader;
	};

	static Renderer2DStorage* RenderData;

	void Renderer2D::Init()
	{
		RenderData = new Renderer2DStorage();

		RenderData->VertexArray = CreateRef<VertexArray>();

		float vertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		Ref<VertexBuffer> vao;
		vao = CreateRef<VertexBuffer>(vertices, sizeof(vertices));
		vao->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
			});
		RenderData->VertexArray->AddVertexBuffer(vao);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> ibo;
		ibo = CreateRef<IndexBuffer>(indices, sizeof(indices) / sizeof(uint32_t));
		RenderData->VertexArray->SetIndexBuffer(ibo);

		RenderData->Shader = CreateRef<Shader>("res/shaders/color.vert", "res/shaders/color.frag");
	}

	void Renderer2D::Destroy()
	{
		delete RenderData;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		RenderData->Shader->Use();
		RenderData->Shader->SetUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		RenderData->Shader->SetUniformMat4("u_Transform", glm::mat4(1.0f));
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		RenderData->Shader->Use();
		RenderData->Shader->SetUniform4f("u_Color", color);

		RenderData->VertexArray->Bind();
		glDrawElements(GL_TRIANGLES, RenderData->VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}
