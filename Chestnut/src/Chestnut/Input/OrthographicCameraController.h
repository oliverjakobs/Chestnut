#pragma once

#include "Chestnut/Graphics/OrthographicCamera.h"
#include "Chestnut/Core/Timestep.h"

#include "Chestnut/Events/WindowEvent.h"
#include "Chestnut/Events/MouseEvent.h"

namespace chst
{
	class OrthographicCameraController
	{
	private:
		float m_aspectRatio;
		float m_zoomLevel = 1.0f;
		OrthographicCamera m_camera;

		bool m_rotation;

		float m_translationSpeed;
		float m_rotationSpeed;

	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false, float translationSpeed = 5.0f, float rotationSpeed = 180.0f);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void SetZoomLevel(float level) { m_zoomLevel = level; }
		float GetZoomLevel() const { return m_zoomLevel; }

		OrthographicCamera& GetCamera() { return m_camera; }
		const OrthographicCamera& GetCamera() const { return m_camera; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	};

}