#include"cgpch.h"
#include"RadioButton.h"
#include<GLFW/glfw3.h>
#include<glad/glad.h>
namespace cdgui
{
	RadioButtons::RadioButton::RadioButton()
	{
		m_Name = "RadioButton";
		m_CheckToBoardDistance = 0.2f;
		m_Check.reset(new Circle({ -0.3f,0.7f }, 0.05f));
		m_Board.reset(new Button({ m_Check.get()->GetPosition().x + m_CheckToBoardDistance, m_Check.get()->GetPosition().y }, { 0.1f, m_Check.get()->GetRadius()}));
	}
	RadioButtons::RadioButton::RadioButton(glm::vec2 pos)
	{
		m_Name = "RadioButton";
		m_CheckToBoardDistance = 0.2f;
		m_Check.reset(new Circle(pos, 0.05f));
		m_Board.reset(new Button({ m_Check.get()->GetPosition().x + m_CheckToBoardDistance, m_Check.get()->GetPosition().y }, { 0.1f, m_Check.get()->GetRadius() }));
	}
	const std::string RadioButtons::RadioButton::GetName() const
	{
		return m_Name;
	}
	void RadioButtons::RadioButton::SetName(std::string name)
	{
		m_Name = name;
	}
	const std::shared_ptr<Button>& RadioButtons::RadioButton::GetBoard() const
	{
		return m_Board;
	}
	const std::shared_ptr<Circle>& RadioButtons::RadioButton::GetCheck() const
	{
		return m_Check;
	}
	void RadioButtons::RadioButton::Draw()
	{
		m_Check.get()->Draw();
		m_Board.get()->Draw();
	}
	void RadioButtons::RadioButton::SetMode(unsigned int mode)
	{
		m_Mode = mode;
	}
	void RadioButtons::RadioButton::Update()
	{

	}
	bool RadioButtons::RadioButton::WithinScope()
	{
		return false;
	}
	RadioButtons::RadioButtons()
		:m_Sequence(0)
	{
	}
	RadioButtons::RadioButtons(glm::vec2 pos)
		: m_Sequence(0)
	{
	}
	RadioButtons::RadioButtons(glm::vec2 pos, glm::vec2 size)
		: m_Sequence(0)
	{
	}
	void RadioButtons::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseButtonPressedEvent>(CG_BIND_EVENT_FN(RadioButtons::OnMouseButtonPressedEventEvent));
	}
	void RadioButtons::AddRadioButton(RadioButton* button)
	{
		button->SetName(button->GetName() + std::to_string(m_Sequence));
		m_RadioButtons.emplace(button->GetName(), std::make_shared<cdgui::RadioButtons::RadioButton*>(button));
		m_Sequence++;
	}

	const std::shared_ptr<cdgui::RadioButtons::RadioButton*>& RadioButtons::GetRadioButton(std::string name) const
	{
		return m_RadioButtons.at(name);
	}

	void RadioButtons::Draw()
	{
		for (auto e : m_RadioButtons) {
			(*(e.second.get()))->Draw();
		}
	}
	void RadioButtons::SetMode(unsigned int mode)
	{
		m_Mode = mode;
	}
	void RadioButtons::Update()
	{
	}
	bool RadioButtons::WithinScope()
	{
		std::pair<float, float> mousePos = Input::GetMousePosition();
		float winWidth = Application::Get().GetWindow().GetWidth();
		float winHeight = Application::Get().GetWindow().GetHeight();

		mousePos.first = (mousePos.first - winWidth / 2.0f) / (winWidth / 2.0f);//noramlize x
		mousePos.second = -((mousePos.second - winHeight / 2.0f) / (winHeight / 2.0f));//noramlize y

		for (auto e : m_RadioButtons) {
			float r = (*(e.second.get()))->GetCheck().get()->GetRadius();
			float rSquare = r * r;
			float checkX = (*(e.second.get()))->GetCheck().get()->GetPosition().x;
			float checkY = (*(e.second.get()))->GetCheck().get()->GetPosition().y;
			float distance = (checkX - mousePos.first) * (checkX - mousePos.first) +
				(checkY - mousePos.second) * (checkY - mousePos.second);
			if (distance <= rSquare){
				if (m_ActiveButtonName != "") {
					(*(m_RadioButtons.at(m_ActiveButtonName).get()))->GetCheck()->SetMode(GL_LINE_STRIP);
				}
				m_ActiveButtonName = e.first;
				(*(m_RadioButtons.at(m_ActiveButtonName).get()))->GetCheck()->SetMode(GL_TRIANGLE_FAN);
				return true;
			}
		}

		return false;
	}
	bool RadioButtons::OnMouseButtonPressedEventEvent(MouseButtonPressedEvent& e)
	{
		if (WithinScope()) {
			return true;
		}
		return false;
	}
}