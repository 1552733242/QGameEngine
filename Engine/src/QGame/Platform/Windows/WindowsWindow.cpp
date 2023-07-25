#include "qgpch.h"
#include "glad/glad.h"
#include "QGame/Log.h"
#include "QGame/Core.h"
#include "WindowsWindow.h"
#include "QGame/Events/AppliccationEvent.h"
#include "QGame/Events/KeyEvent.h"
#include "QGame/Events/MouseEvent.h"
#include "QGame/Platform/OpenGL/OpenGLContext.h"
namespace QGame {

	static bool s_GLFWInitialized = false;
	static void GLFWErrorCallback(int error ,const char* desciption) 
	{
		//glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE);
		QG_CORE_ERROR("GLFW Error {0} {1}", error, desciption);
	}
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

		m_Context->SwapBuffers();

		
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

			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true; 
		}
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
	
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();
		
	
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);	

		


		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowResizeEvent event(width, height);
				data.EventCallback(event);
				data.Width = width;
				data.Height = height;
			});
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) 
			{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window,int key,int scancode,int action,int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleaseEvent event(key);
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1);
						data.EventCallback(event);
						break;
					}
				}
			});
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypeEvent event(keycode);
			data.EventCallback(event);
			});
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window,int button,int action,int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS: 
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleaseEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
			});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);

			});
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMoveEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
			});
		


	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

}