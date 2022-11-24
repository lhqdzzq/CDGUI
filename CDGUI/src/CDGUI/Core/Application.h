#pragma once
#include"Core.h"
#include"Log.h"
#include"Window.h"
#include"LayerStack.h"
#include"CDGUI/Event/Event.h"
#include"CDGUI/Event/ApplicationEvent.h"
#include"platform/WindowsWindow.h"

#include"CDGUI/Renderer/Shader.h"
#include"CDGUI/Renderer/Buffer.h"
#include"CDGUI/Renderer/VertexArray.h"

namespace cdgui
{
	 class CDGUI_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverLayer(Layer* overlayer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Runing;
		LayerStack m_LayerStack;
		float m_LastFrameTime;
	private:
		static Application* s_Instance;
	};

	 Application* CreateApplication();
}