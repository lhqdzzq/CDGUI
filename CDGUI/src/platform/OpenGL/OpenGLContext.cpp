#include"cgpch.h"
#include"OpenGLContext.h"

#include<GLFW/glfw3.h>
#include<glad/glad.h>

namespace cdgui
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		CG_CORE_ASSERTS(windowHandle, "WindowHandle is NULL!");
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CG_CORE_ASSERTS(status, "Glad ≥ı ºªØ ß∞‹£°");
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}