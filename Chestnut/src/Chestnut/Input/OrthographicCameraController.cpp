#include "chstpch.h"
#include "OrthographicCameraController.h"

#include "Chestnut/Input/Input.h"
#include "Chestnut/Input/KeyCodes.h"

#include "Chestnut/Utility/Obelisk.h"

namespace chst
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation, float translationSpeed, float rotationSpeed)
		: m_camera(-aspectRatio * m_zoomLevel, aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel),
		m_aspectRatio(aspectRatio), m_rotation(rotation), m_translationSpeed(translationSpeed), m_rotationSpeed(rotationSpeed)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		glm::vec3 position = m_camera.GetPosition();
		float rotation = m_camera.GetRotation();

		if (Input::KeyPressed(CHST_KEY_A))
		{
			position.x -= cos(glm::radians(rotation)) * m_translationSpeed * ts;
			position.y -= sin(glm::radians(rotation)) * m_translationSpeed * ts;
		}
		else if (Input::KeyPressed(CHST_KEY_D))
		{
			position.x += cos(glm::radians(rotation)) * m_translationSpeed * ts;
			position.y += sin(glm::radians(rotation)) * m_translationSpeed * ts;
		}

		if (Input::KeyPressed(CHST_KEY_W))
		{
			position.x += -sin(glm::radians(rotation)) * m_translationSpeed * ts;
			position.y += cos(glm::radians(rotation)) * m_translationSpeed * ts;
		}
		else if (Input::KeyPressed(CHST_KEY_S))
		{
			position.x -= -sin(glm::radians(rotation)) * m_translationSpeed * ts;
			position.y -= cos(glm::radians(rotation)) * m_translationSpeed * ts;
		}

		m_camera.SetPosition(position);

		if (m_rotation)
		{
			if (Input::KeyPressed(CHST_KEY_Q))
				rotation += m_rotationSpeed * ts;
			if (Input::KeyPressed(CHST_KEY_E))
				rotation -= m_rotationSpeed * ts;

			if (rotation > 180.0f)
				rotation -= 360.0f;
			else if (rotation <= -180.0f)
				rotation += 360.0f;

			m_camera.SetRotation(rotation);
		}

		m_translationSpeed = m_zoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_FUNCTION(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_FUNCTION(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_zoomLevel -= e.GetOffsetY() * 0.25f;
		m_zoomLevel = std::max(m_zoomLevel, 0.25f);
		m_camera.SetProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_camera.SetProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
		return false;
	}
}