#pragma once

#include "QGame/Renderer/OrthgraphicCamera.h"
#include "QGame/Core/Timestep.h"
#include "QGame/Events/AppliccationEvent.h"
#include "QGame/Events/MouseEvent.h"
namespace QGame {
	struct OrthographicCameraBounds
	{
		float Left, Right;
		float Bottom, Top;
		float GetWidth() { return Right - Left; }
		float GetHeight() { return Top - Bottom; }


	};

	class OrthographicCameraController {

	public:

		OrthographicCameraController(float aspectRatio, bool rotation = false);


		void OnUpdata(Timestep ts);
		void OnEvent(Event& e);
		OrthographicCamera& GetCamera() { return m_Camera; };
		const OrthographicCamera& GetCamera()const { return m_Camera; } 
		const OrthographicCameraBounds& GetBounds()const { return m_Bounds; }

		inline float GetZoomLevel()const { return m_ZoomLevel; }
		inline void SetZoomLevel(float level);
		
	
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;
		OrthographicCameraBounds m_Bounds;

		bool m_Rotation = false;
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 1.0f, m_CameraRotationSpeed = 1.0f;
	};

}