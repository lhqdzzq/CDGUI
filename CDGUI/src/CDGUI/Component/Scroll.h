#pragma once
#include"Component.h"
#include"Button.h"
#include"CDGUI/Renderer/Shader.h"
#include"CDGUI/Renderer/VertexArray.h"
#include"CDGUI/Core/MouseButtonCode.h"
#include"CDGUI/Event/MouseEvent.h"
namespace cdgui
{
	class Scroll: public Component
	{
	public:
		Scroll(glm::vec2 pos);
		Scroll(glm::vec2 pos, glm::vec2 size);

		void OnEvent(Event& e);
		float GetRange()const;
		float Dragged();
		virtual void Draw();
		virtual void SetMode(unsigned int mode);

	private:
		virtual void Update();
		virtual bool WithinScope();
		bool OnMouseButtonPressedEventEvent(MouseButtonPressedEvent& e);
		bool OnMouseMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
	private:
		unsigned int m_Mode;
		float m_Range;
		bool m_MousePressed;//��¼����Ƿ�һֱ���£����Ƿ����϶�
		std::pair<float, float> m_LastMousePos;

		std::shared_ptr<Button> m_SlidingKnob;
		std::shared_ptr<Button> m_Scroll;
	};
}