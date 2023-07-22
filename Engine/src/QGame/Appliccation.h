#pragma once
#include"Core.h"
#include"Window.h"
#include"LayerStack.h"
#include"QGame/ImGui/ImGuiLayer.h"
#include"QGame/Events/AppliccationEvent.h"

namespace QGame {

	class GAME_API Application
	{
	public:
		Application();
		~Application();
		void Run();


		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window>m_Window;
		ImGuiLayer*m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		static Application* s_Instance;
	};
	Application* CreateApplication();
}

