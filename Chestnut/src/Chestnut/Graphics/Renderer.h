#pragma once

#include "OrthographicCamera.h"
#include "Shader.h"
#include "VertexArray.h"

namespace chst
{
	class Renderer
	{
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<SceneData> s_SceneData;

	public:
		static void Init();
		static void OnWindowResize(uint32_t width, uint32_t height);

		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		static void SetClearColor(const glm::vec4& color);
		static void SetClearColor(float r, float g , float b, float a);

		static void Clear();

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
	};
}
