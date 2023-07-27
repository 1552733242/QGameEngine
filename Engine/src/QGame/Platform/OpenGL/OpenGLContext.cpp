
#include "qgpch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace QGame {




	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) :m_WindowHandle(windowHandle)
	{
		GAME_ASSERT(m_WindowHandle, "Window Handle is NULL");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GAME_ASSERT(status, "GLAD Counld find Adresss");
		QG_CORE_INFO("OpenGL Info:");
		QG_CORE_INFO("	Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		QG_CORE_INFO("	Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		QG_CORE_INFO("	Version: {0}", (const char*)glGetString(GL_VERSION));
	
	}

	void OpenGLContext::SwapBuffers() 
	{
		glfwSwapBuffers(m_WindowHandle); 
	}

}