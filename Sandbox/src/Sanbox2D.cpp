#include "Sanbox2D.h"
#include "imgui.h"
#include <glm/gtc/type_ptr.hpp>


Sandbox2D::Sandbox2D()
	:Layer("Sanbox2D"), m_CameraController(1280.0f/720.0f)
{

}

void Sandbox2D::OnAttach()
{
	
	m_CheckborardTexture = QGame::Texture2D::Create("assets/textures/Checkerboard.png");
	m_SpriteSheet  = QGame::Texture2D::Create("assets/game/textures/RPGpack_sheet_2X.png") ;

	m_TextureStairs = QGame::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 7,6 }, { 128,128 }, { 1,1 });
	m_TextureTree = QGame::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2,1 }, { 128,128 }, { 1,2 });


	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd   = { 254 / 255.0f, 108 / 255.0f,  41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 1.0f;
	m_Particle.Velocity = { 0.0f,0.0f };
	m_Particle.VelocityVariation = { 3.0f,1.0f };
	m_Particle.Position = { 0.0f,0.0f };


}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(QGame::Timestep ts)
{
	QG_PROFILE_FUNCTION();
	
	//Update
	{
		m_CameraController.OnUpdata(ts);
		QG_PROFILE_SCOPE("CameraController::OnUpdata");
	}
	//Render
	QGame::Renderer2D::RestStats();
	{
		QG_PROFILE_SCOPE("Renderer Prep");

		QGame::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		QGame::RendererCommand::Clear();
	}
#if 0
	{
		QG_PROFILE_SCOPE("Renderer Draw");
		QGame::Renderer2D::BeginScene(m_CameraController.GetCamera());
		static float rotation = 0.0f;
		rotation += ts * 10.f;
		QGame::Renderer2D::DrawQuare({ 0.0f,0.0f,-0.1f }, { 20.0f,20.0f }, m_CheckborardTexture, 10.f);
		QGame::Renderer2D::DrawQuare({ 0.0f,0.0f }, { 1.0f,1.0f },rotation, m_CheckborardTexture, 10.f);
	
		QGame::Renderer2D::EndScene();
	}
#endif
	if (QGame::Input::IsMousePressed(QG_MOUSE_BUTTON_LEFT)) {
		auto [x, y] = QGame::Input::GetMousePosition();
		auto width = QGame::Application::Get().GetWindow().GetWidth();
		auto height = QGame::Application::Get().GetWindow().GetHeight();

		auto bounds = m_CameraController.GetBounds();
		auto pos = m_CameraController.GetCamera().GetPosition();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		m_Particle.Position = { x + pos.x,y + pos.y };
		for (int i = 0; i < 50; i++) {	
			m_ParticleSystem.Emit(m_Particle);
		}
	}





	
	
	


	m_ParticleSystem.OnUpdate(ts);
	m_ParticleSystem.OnRender(m_CameraController.GetCamera());

	QGame::Renderer2D::BeginScene(m_CameraController.GetCamera());
	QGame::Renderer2D::DrawQuare({ 0.0f,0.0f,0.5f }, { 1.0f,1.0f }, m_TextureStairs);
	QGame::Renderer2D::DrawQuare({ -1.0f,0.0f,0.5f }, { 1.0f,2.0f }, m_TextureTree);
	QGame::Renderer2D::EndScene();

}

void Sandbox2D::OnImGuiRender()
{
	QG_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	auto stats = QGame::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Start:");
	ImGui::Text("Draw Calls: %d",stats.DrawCount);
	ImGui::Text("Quad: %d", stats.QuadCount);
	ImGui::Text("Vertex: %d", stats.GetTotalVertexCount());
	
	ImGui::ColorEdit3("Squre Color", glm::value_ptr(m_SquareColor));
	ImGui::End();

}

void Sandbox2D::OnEvent(QGame::Event& e)
{
	m_CameraController.OnEvent(e);
}
