#pragma once


#include"QGame/Window.h"
#include<GLFW/glfw3.h>



namespace QGame {


	class WindowsWindow :public Window 

	{

	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();
		virtual void OnUpdate() override;

		unsigned int GetWidth() const override { return m_Data.Width; }
		unsigned int GetHeight() const override { return m_Data.Height; }
		inline virtual void* GetNativeWindow() { return m_Window; }
		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override; // 设置是否开启垂直同步 VSync = 垂直同步
		bool IsVSync() const override;


		virtual void* GetNativeWindow()const { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			EventCallbackFn EventCallback;
		};
		
		WindowData m_Data;
	};



}