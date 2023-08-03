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
	{
		QG_PROFILE_SCOPE("Renderer Prep");

		QGame::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		QGame::RendererCommand::Clear();
	}

	{
		QG_PROFILE_SCOPE("Renderer Draw");
		QGame::Renderer2D::BeginScene(m_CameraController.GetCamera());
		//QGame::Renderer2D::DrawQuare({ -1.f,0.f }, { 0.8f,0.8f }, { 0.8f,0.2f,0.3f,1.f });
		
		//QGame::Renderer2D::DrawQuare({ 0.5f,-0.5f }, { 0.5f,0.75f }, { 0.2f,0.3f,0.8f,1.f });
		QGame::Renderer2D::DrawQuare({ 0.5f,-0.5f }, { 0.5f,0.75f }, { 0.2f,0.3f,0.8f,1.f });
		//QGame::Renderer2D::DrawQuare({ 0.5f,-0.5f }, { 0.5f,0.75f }, { 0.2f,0.3f,0.8f,1.f });
		//QGame::Renderer2D::DrawQuare({ 0.5f,-0.5f }, { 0.5f,0.75f }, { 0.2f,0.3f,0.8f,1.f });
		//QGame::Renderer2D::DrawQuare({ 0.0f,0.0f,-0.1f }, { 10.0f,10.0f }, m_CheckborardTexture, 10.f);
		QGame::Renderer2D::EndScene();
	}
	
}

void Sandbox2D::OnImGuiRender()
{
	QG_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Squre Color", glm::value_ptr(m_SquareColor));


	ImGui::End();

}

void Sandbox2D::OnEvent(QGame::Event& e)
{
	m_CameraController.OnEvent(e);
}
