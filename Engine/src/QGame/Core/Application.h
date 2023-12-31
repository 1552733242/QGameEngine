#pragma once
#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "QGame/ImGui/ImGuiLayer.h"
#include "QGame/Events/ApplicationEvent.h"
#include "QGame/Core/Timestep.h"
namespace QGame {

	class Application
	{
	public:
		Application(const std::string& name = "QGame");
		~Application();
		void Run();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);


	private:
		std::unique_ptr<Window>m_Window;
		ImGuiLayer*m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFramTime = 0.0f;

	private:
		static Application* s_Instance;
	};
	Application* CreateApplication();
}

