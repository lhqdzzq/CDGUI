#include"cgpch.h"
#include"Scroll.h"
#include<GLFW/glfw3.h>
#include<glad/glad.h>

namespace cdgui
{
	Scroll::Scroll(glm::vec2 pos)
		:m_Range(0.5f), m_MousePressed(false), m_Mode(GL_TRIANGLES)
	{
		m_Scroll.reset(new Button(pos, { 0.05f,0.8f }));
		m_SlidingKnob.reset(new Button(pos, { 0.05f,0.05f }, { 0.2f,0.2f,0.2f }));
	}
	Scroll::Scroll(glm::vec2 pos, glm::vec2 size)
		: m_Range(0.5f), m_MousePressed(false), m_Mode(GL_TRIANGLES)
	{
		m_Scroll.reset(new Button(pos, size));
		m_SlidingKnob.reset(new Button(pos, size));
	}
	void Scroll::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseButtonPressedEvent>(CG_BIND_EVENT_FN(Scroll::OnMouseButtonPressedEventEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(CG_BIND_EVENT_FN(Scroll::OnMouseMouseButtonReleasedEvent));
	}
	float Scroll::GetRange() const
	{
		return m_Range;
	}
	float Scroll::Dragged()
	{
		if (m_MousePressed) {
			std::pair<float, float> mousePos = Input::GetMousePosition();
			float normalYOffst = (mousePos.second - m_LastMousePos.second)
				/ static_cast<float>(Application::Get().GetWindow().GetHeight() / 2);

			float scollBottomY = m_Scroll.get()->GetPosition().y - m_Scroll.get()->GetSize().y;
			float scollTopY = m_Scroll.get()->GetPosition().y + m_Scroll.get()->GetSize().y;
			float slidingKnobBottomY = m_SlidingKnob.get()->GetPosition().y - m_SlidingKnob.get()->GetSize().y - normalYOffst;
			float slidingKnobTopY = m_SlidingKnob.get()->GetPosition().y + m_SlidingKnob.get()->GetSize().y - normalYOffst;
			
			if (scollBottomY <= slidingKnobBottomY && slidingKnobTopY <= scollTopY)
			{
				float slidingKnobNewY = m_SlidingKnob.get()->GetPosition().y - normalYOffst;
				if (scollBottomY > slidingKnobBottomY) {
					slidingKnobNewY = scollBottomY + m_SlidingKnob.get()->GetSize().y;
				}
				if (scollTopY < slidingKnobTopY) {
					slidingKnobNewY = scollTopY - m_SlidingKnob.get()->GetSize().y;
				}
				m_SlidingKnob.get()->SetPosition({ m_SlidingKnob.get()->GetPosition().x, slidingKnobNewY });
				m_Range = (scollTopY - slidingKnobTopY) / m_Scroll.get()->GetSize().y / 2;
			}
			m_LastMousePos = mousePos;
		}
		return m_Range;
	}
	void Scroll::Draw()
	{
		m_Scroll.get()->Draw();
		m_SlidingKnob.get()->Draw();
	}
	void Scroll::SetMode(unsigned int mode)
	{
		m_Mode = mode;
	}
	void Scroll::Update()
	{
	}
	bool Scroll::WithinScope()
	{
		std::pair<float, float> mousePos = Input::GetMousePosition();
		float winWidth = Application::Get().GetWindow().GetWidth();
		float winHeight = Application::Get().GetWindow().GetHeight();

		float left = (m_SlidingKnob.get()->GetPosition().x - m_SlidingKnob.get()->GetSize().x) * (winWidth / 2) + winWidth / 2;
		float right = (m_SlidingKnob.get()->GetPosition().x + m_SlidingKnob.get()->GetSize().x) * (winWidth / 2) + winWidth / 2;
		float bottom = (-(m_SlidingKnob.get()->GetPosition().y - m_SlidingKnob.get()->GetSize().y)) * (winHeight / 2) + winHeight / 2;
		float top = (-(m_SlidingKnob.get()->GetPosition().y + m_SlidingKnob.get()->GetSize().y)) * (winHeight / 2) + winHeight / 2;

		if (left <= static_cast<float>(mousePos.first) && static_cast<float>(mousePos.first) <= right &&
			top <= static_cast<float>(mousePos.second) && static_cast<float>(mousePos.second) <= bottom) {
			return true;
		}
		return false;
	}
	bool Scroll::OnMouseButtonPressedEventEvent(MouseButtonPressedEvent& e)
	{
		if (WithinScope()) {
			if (e.GetMouseButton() == CG_MOUSE_BUTTON_LEFT) {
				m_MousePressed = true;
				double xpos, ypos;
				glfwGetCursorPos((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow(), &xpos, &ypos);
				m_LastMousePos.first = static_cast<float>(xpos);
				m_LastMousePos.second = static_cast<float>(ypos);
			}
			//CG_INFO("Scroll OnMouseButtonPressedEventEvent");
		}
		return false;
	}
	bool Scroll::OnMouseMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		if (e.GetMouseButton() == CG_MOUSE_BUTTON_LEFT) {
			m_MousePressed = false;
		}
		return false;
	}
}