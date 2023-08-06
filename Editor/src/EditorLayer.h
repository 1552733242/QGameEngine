#pragma once
#include "QGame.h"
#include "Panels/SceneHierarchyPanel.h"
namespace QGame {
	class EditorLayer :public Layer {

	public:
		EditorLayer();
		virtual ~EditorLayer() = default;
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		void OnUpdate(Timestep ts)override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event & e) override; 

	private:
		OrthographicCameraController m_CameraController;

		Ref<Texture2D> m_CheckborardTexture;

		Ref<FrameBuffer>m_FrameBuffer;

		Ref<Scene>m_ActiveScene;
		Entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCameraEntity;
		bool m_ViewPortFocused = false;
		bool m_ViewPortHovered = false;
		glm::vec2 m_ViewPortSize = { 0.0f,0.0f };

		//glm::vec4 m_SquareColor = { 0.2f,0.3f,0.8f,1.0f };

		SceneHierarchyPanel m_SceneHierarchyPanel;
	};
}