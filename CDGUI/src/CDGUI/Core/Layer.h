#pragma once
#include"Core.h"
#include"CDGUI/Event/Event.h"
#include"CDGUI/Core/Timestep.h"
namespace cdgui
{
	class CDGUI_API Layer
	{
	public:
		Layer(const std::string name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate(Timestep ts) {};
		virtual void OnEvent(Event& e) {};

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}
