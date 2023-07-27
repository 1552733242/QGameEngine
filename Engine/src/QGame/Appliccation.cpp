#include"qgpch.h"

#include "Appliccation.h"
#include "Input.h"
#include "glad/glad.h"

namespace QGame {
	
	Application* Application::s_Instance = nullptr;
	Application::Application()
	{
		GAME_CORE_ASSERT(!s_Instance, "Application already exit");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(QG_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushLayer(m_ImGuiLayer);

		glGenVertexArrays(1,&m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1,&m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		float vertices[3 * 3]{
			-0.5f,  -0.5f,  0.0f,
			 0.5f,  -0.5f,  0.0f,
			 0.0f,   0.5f,  0.0f
		};				  
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);


		unsigned int indices[] = { 0,1,2 };
		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		std::string vertexSrc = R"(
	#version 330 core
	
	layout(location = 0) in vec3 a_Position;
	
	void main(){
		


	}







)";

		m_Shader = std::make_unique<Shader>();
	}

	Application::~Application()	
	{
	}

	void Application::Run()
	{
	
		while (m_Running) {
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			
			//glViewport(0, 0, s_Instance->GetWindow().GetWidth(), s_Instance->GetWindow().GetHeight());
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
		

			m_ImGuiLayer->Begin();
			
			
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(QG_BIND_EVENT_FN(Application::OnWindowClose));
		
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.IsHandled())
				break;
		}
	}
	bool Application::OnWindowClose(WindowCloseEvent& e) {
			
		m_Running = false;
		
		return true;
	}


	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}


}




