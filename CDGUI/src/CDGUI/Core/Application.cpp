#include"cgpch.h"
#include"Application.h"
#include"CDGUI/Core/Input.h"
#include"CDGUI/Core/Timestep.h"

#include"CDGUI/Renderer/Renderer.h"

#include<GLFW/glfw3.h>
namespace cdgui {

	Application* Application::s_Instance = nullptr;


	cdgui::Application::Application()
	{
		CG_CORE_ASSERTS(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Runing = true;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(CG_BIND_EVENT_FN(Application::OnEvent));
		Renderer::Init();

	}

	cdgui::Application::~Application()
	{
	}

	void cdgui::Application::Run()
	{

		while (m_Runing)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;
			//从前往后渲染
			for (auto layer : m_LayerStack) {
				layer->OnUpdate(timestep);
			}
			m_Window->OnUpdate();

		}
	}

	void cdgui::Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(CG_BIND_EVENT_FN(Application::OnWindowClose));

		//从后往前传递事件
		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); it++) {
			if (e.Handled) {
				break;
			}
			(*it)->OnEvent(e);
		}
	}

	void cdgui::Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void cdgui::Application::PushOverLayer(Layer* overlayer)
	{
		m_LayerStack.PushOverLayer(overlayer);
		overlayer->OnAttach();
	}

	bool cdgui::Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Runing = false;
		return true;
	}

}
