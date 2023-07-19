#include"QGame/Log.h"
#include "WindowsWindow.h"

namespace QGame {

	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& props) 
	{

		return new WindowsWindow(props);
	}
	
	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}
	WindowsWindow::WindowsWindow(const WindowProps&	props) 
	{
		Init(props);
	}
	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}
		m_Data.VSync = enabled;

	}

	bool WindowsWindow::IsVSync() const
	{
		return false;
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		QG_CORE_INFO("Creating Window {0} {1} {2}", props.Title, props.Width, props.Height);
		
		if (!s_GLFWInitialized) {
			int success = glfwInit();
			
			GAME_ASSERT(success, "Could not intialize GLFW");
			s_GLFWInitialized = true; 
		}

	
		
		
		
		
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);	


		int res = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				glfwGetWindowUserPointer(window);
			});

	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

}