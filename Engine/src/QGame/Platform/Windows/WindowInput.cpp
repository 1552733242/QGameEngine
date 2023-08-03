#include "qgpch.h"
#include <GLFW/glfw3.h>
#include "QGame/Platform/Windows/WindowInput.h"
#include "QGame/Core/Appliccation.h"


namespace QGame {

	Input* Input::s_Instance = new WindowInput;

	bool WindowInput::IsKeyPressedImpl(int keycode)
	{

		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());


		auto state = glfwGetKey(window, keycode);


		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowInput::IsMousePressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());


		auto state = glfwGetMouseButton(window, button);


		return state == GLFW_PRESS;
	}

	float WindowInput::GetMouseXImpl()
	{

		auto [x, y] = GetMousePositionImpl();

		return (float)x;
	}

	float WindowInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();

		return (float)y;
	}

	std::pair<float, float>WindowInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return std::pair<float, float>(xpos, ypos);
	}

}