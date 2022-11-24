#include "cgpch.h"
#include "WindowsWindow.h"

#include "CDGUI/Core/Log.h"
#include "CDGUI/Event/KeyEvent.h"
#include "CDGUI/Event/MouseEvent.h"
#include "CDGUI/Event/ApplicationEvent.h"

#include"platform/OpenGL/OpenGLContext.h"

#include"glad/glad.h"
#include"GLFW/glfw3.h"
namespace cdgui
{
	static unsigned int s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		CG_CORE_ERROR("CDGUI Error ({0} , {1})", error, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	cdgui::WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	cdgui::WindowsWindow::~WindowsWindow()
	{
		Shoutdown();
	}

	void cdgui::WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		if (s_GLFWWindowCount == 0) 
		{
			int success = glfwInit();
			CG_CORE_ASSERTS(success, "初始化OpenGL出错！");
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);
		s_GLFWWindowCount++;

		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();
		

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		//设置GLFW回调函数
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
			data.Width = width;
			data.Height = height;

			WindowResizeEvent e(width, height);
			data.EventCallback(e);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
			WindowCloseEvent e;
			data.EventCallback(e);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int modes)
		{
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent e(key, 0);
					data.EventCallback(e);
					break;
				}					
				case GLFW_RELEASE:
				{
					KeyReleasedEvent e(key);
					data.EventCallback(e);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent e(key, 1);
					data.EventCallback(e);
					break;
				}
			}
		});
		
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
			KeyTypedEvent e(keycode);
			data.EventCallback(e);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int modes)
		{
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent e(button);
					data.EventCallback(e);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent e(button);
					data.EventCallback(e);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

			MouseScrolledEvent e((float)xOffset, (float)yOffset);
			data.EventCallback(e);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) 
		{
			WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

			MouseMovedEvent e((float)xPos, (float)yPos);
			data.EventCallback(e);
		});


	}

	void cdgui::WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	std::pair<float, float> WindowsWindow::GetCursorPos() const
	{
		double xpos, ypos;
		glfwGetCursorPos(m_Window, &xpos, &ypos);
		return std::pair<float, float>((float)xpos, (float)ypos);
	}

	void cdgui::WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}

		m_Data.VSync = enabled;
	}

	bool cdgui::WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void cdgui::WindowsWindow::Shoutdown()
	{
		glfwDestroyWindow(m_Window);
	}
}
