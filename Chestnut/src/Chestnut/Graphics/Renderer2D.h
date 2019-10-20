#pragma once

#include "OrthographicCamera.h"

namespace chst
{
	struct Renderer2D
	{
		static void Init();
		static void Destroy();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		// Primitives
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	};
}
