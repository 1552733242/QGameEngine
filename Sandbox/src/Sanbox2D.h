#pragma once
#include <QGame.h>

class Sandbox2D :public QGame::Layer {

public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	void OnUpdate(QGame::Timestep ts)override;
	virtual void OnImGuiRender() override;
	void OnEvent(QGame::Event& e) override;

private:
	QGame::OrthographicCameraController m_CameraController;

	QGame::Ref<QGame::VertexArray> m_SquareVA;
	QGame::Ref<QGame::Shader> m_Shader;
	QGame::Ref<QGame::Texture2D> m_CheckborardTexture;


	
	glm::vec4 m_SquareColor = { 0.2f,0.3f,0.8f,1.0f };


};