#include"qgpch.h"
#include "Appliccation.h"
#include "Input.h"
#include "Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace QGame {
	
	Application* Application::s_Instance = nullptr;


	Application::Application() 
	{
		GAME_CORE_ASSERT(!s_Instance, "App	lication already exit");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(QG_BIND_EVENT_FN(Application::OnEvent));
		
		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushLayer(m_ImGuiLayer);
	}

	Application::~Application()	
	{
	}

	void Application::Run()
	{
	
		while (m_Running) {

			float time = (float)glfwGetTime(); 
			Timestep timestep = time - m_LastFramTime;
			m_LastFramTime = time;
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);

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




