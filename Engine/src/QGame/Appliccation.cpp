#include <glad/glad.h>
#include "Appliccation.h"
#include <QGame/Events/AppliccationEvent.h>
#include <ostream>

namespace QGame {
	#define BIND_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)

	Application::Application()
	{
		
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1200, 720);

		if (e.IsInCategory(EventCategoryApplication)) {
			QG_TRACE(e.ToString());
		}
		if (e.IsInCategory(EventCategoryInput)) {
			
			QG_TRACE(e.ToString());
		}

		while (m_Running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{

		QG_CORE_INFO("{0}", e.ToString());


	}

}




