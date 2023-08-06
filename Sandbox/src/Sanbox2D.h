#pragma once
#include <QGame.h>
#include "ParticleSystem.h"
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
	QGame::Ref<QGame::Texture2D> m_SpriteSheet;
	QGame::Ref<QGame::SubTexture2D> m_TextureStairs;
	QGame::Ref<QGame::SubTexture2D> m_TextureTree;

	glm::vec4 m_SquareColor = { 0.2f,0.3f,0.8f,1.0f };

	ParticleSystem m_ParticleSystem;
	ParticleProps m_Particle;
};