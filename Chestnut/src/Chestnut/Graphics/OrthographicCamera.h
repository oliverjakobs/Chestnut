#pragma once

#include <glm/glm.hpp>

namespace chst
{
	class OrthographicCamera
	{
	private:
		glm::mat4 m_projection;
		glm::mat4 m_view;
		glm::mat4 m_viewProjection;

		glm::vec3 m_position = glm::vec3();
		float m_rotation = 0.0f;

	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetProjection(float left, float right, float bottom, float top);

		void SetPosition(const glm::vec3& position) { m_position = position; RecalculateViewMatrix(); }
		void SetRotation(float rotation) { m_rotation = rotation; RecalculateViewMatrix(); }

		const glm::vec3& GetPosition() const { return m_position; }
		const float GetRotation() const { return m_rotation; }

		const glm::mat4& GetProjectionMatrix() const { return m_projection; }
		const glm::mat4& GetViewMatrix() const { return m_view; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_viewProjection; }

	private:
		void RecalculateViewMatrix();
	};
}
