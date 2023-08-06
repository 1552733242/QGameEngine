#include "qgpch.h"
#include "Window.h"

#ifdef GAME_PLATFORM_WINDOWS
	#include "QGame/Platform/Windows/WindowsWindow.h"
#endif
namespace QGame {

	Window* Window::Create(const WindowProps& props)
	{
#ifdef GAME_PLATFORM_WINDOWS
		return new WindowsWindow(props);
#else
		GAME_CORE_ASSERT(false, "Unknown platform");
		return nullptr;
#endif 

		
	}



}
