#pragma once
#include"CDGUI/Core/Core.h"
#include"CDGUI/Renderer/GraphicsContext.h"

struct GLFWwindow;
namespace cdgui
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}