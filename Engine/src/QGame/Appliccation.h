#pragma once
#include"Core.h"
#include"Window.h"

namespace QGame {

	class GAME_API Application
	{
	public:
		Application();
		~Application();
		void Run();


		void OnEvent(Event& e);
	private:
		std::shared_ptr<Window>m_Window;
		bool m_Running = true;
	};
	Application* CreateApplication();
}

