#include "chstpch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace chst
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
	{
		m_projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_view = glm::mat4(1.0f);

		m_viewProjection = m_projection * m_view;
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		m_projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_viewProjection = m_projection * m_view;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::mat4(1.0f);

		transform = glm::translate(transform, m_position);
		transform = glm::rotate(transform, glm::radians(m_rotation), glm::vec3(0, 0, 1));

		m_view = glm::inverse(transform);
		m_viewProjection = m_projection * m_view;
	}
}