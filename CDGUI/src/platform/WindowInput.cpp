#include "cgpch.h"
#include "WindowInput.h"

#include"CDGUI/Core/Application.h"
#include<GLFW/glfw3.h>
namespace cdgui
{
	Input* Input::s_Instance = new WindowInput();

	bool WindowInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		bool state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS;
	}
	bool WindowInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		bool state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}
	std::pair<float, float> WindowInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos ,(float)ypos };
	}
	float WindowInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}
	float WindowInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}
}