#include"cgpch.h"
#include"CheckBox.h"
#include<GLFW/glfw3.h>
#include<glad/glad.h>
namespace cdgui
{
	CheckBoxes::CheckBox::CheckBox()
	{
		m_Name = "RadioButton";
		m_CheckToBoardDistance = 0.2f;
		m_Check.reset(new Circle({ 0.3f,-0.7f }, 0.05f));
		m_Board.reset(new Button({ m_Check.get()->GetPosition().x + m_CheckToBoardDistance, m_Check.get()->GetPosition().y }, { 0.1f, m_Check.get()->GetRadius() }));

	}
	CheckBoxes::CheckBox::CheckBox(glm::vec2 pos)
	{
		m_Name = "RadioButton";
		m_CheckToBoardDistance = 0.2f;
		m_Check.reset(new Circle(pos, 0.05f));
		m_Board.reset(new Button({ m_Check.get()->GetPosition().x + m_CheckToBoardDistance, m_Check.get()->GetPosition().y }, { 0.1f, m_Check.get()->GetRadius() }));

	}
	const std::string CheckBoxes::CheckBox::GetName() const
	{
		return m_Name;
	}
	void CheckBoxes::CheckBox::SetName(std::string name)
	{
		m_Name = name;
	}
	const std::shared_ptr<Button>& CheckBoxes::CheckBox::GetBoard() const
	{
		return m_Board;
	}
	const std::shared_ptr<Circle>& CheckBoxes::CheckBox::GetCheck() const
	{
		return m_Check;
	}
	void CheckBoxes::CheckBox::Draw()
	{
		m_Check.get()->Draw();
		m_Board.get()->Draw();
	}
	void CheckBoxes::CheckBox::SetMode(unsigned int mode)
	{
		m_Mode = mode;
	}
	void CheckBoxes::CheckBox::Update()
	{
	}
	bool CheckBoxes::CheckBox::WithinScope()
	{
		return false;
	}
	CheckBoxes::CheckBoxes()
		: m_Sequence(0)
	{
	}
	CheckBoxes::CheckBoxes(glm::vec2 pos)
		: m_Sequence(0)
	{
	}
	void CheckBoxes::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseButtonPressedEvent>(CG_BIND_EVENT_FN(CheckBoxes::OnMouseButtonPressedEventEvent));
	}
	void CheckBoxes::AddCheckBox(CheckBox* checkBox)
	{
		checkBox->SetName(checkBox->GetName() + std::to_string(m_Sequence));
		m_CheckBoxes.emplace(checkBox->GetName(), std::make_shared<cdgui::CheckBoxes::CheckBox*>(checkBox));
		m_ActiveCheckBoxes.emplace(checkBox->GetName(), false);
		m_Sequence++;
	}
	void CheckBoxes::Draw()
	{
		for (auto e : m_CheckBoxes) {
			(*(e.second.get()))->Draw();
		}
	}
	void CheckBoxes::SetMode(unsigned int mode)
	{
		m_Mode = mode;
	}
	void CheckBoxes::Update()
	{
	}
	bool CheckBoxes::WithinScope()
	{
		std::pair<float, float> mousePos = Input::GetMousePosition();
		float winWidth = Application::Get().GetWindow().GetWidth();
		float winHeight = Application::Get().GetWindow().GetHeight();

		mousePos.first = (mousePos.first - winWidth / 2.0f) / (winWidth / 2.0f);//noramlize x
		mousePos.second = -((mousePos.second - winHeight / 2.0f) / (winHeight / 2.0f));//noramlize y

		for (auto e : m_CheckBoxes) {
			float r = (*(e.second.get()))->GetCheck().get()->GetRadius();
			float rSquare = r * r;
			float checkX = (*(e.second.get()))->GetCheck().get()->GetPosition().x;
			float checkY = (*(e.second.get()))->GetCheck().get()->GetPosition().y;
			float distance = (checkX - mousePos.first) * (checkX - mousePos.first) +
				(checkY - mousePos.second) * (checkY - mousePos.second);
			if (distance <= rSquare) {
				if (m_ActiveCheckBoxes.at(e.first) == true) {
					(*(m_CheckBoxes.at(e.first).get()))->GetCheck()->SetMode(GL_LINE_STRIP);
				}
				else {
					(*(m_CheckBoxes.at(e.first).get()))->GetCheck()->SetMode(GL_TRIANGLE_FAN);
				}
				m_ActiveCheckBoxes[e.first] = !m_ActiveCheckBoxes[e.first];
				return true;
			}
		}
		return false;
	}
	bool CheckBoxes::OnMouseButtonPressedEventEvent(MouseButtonPressedEvent& e)
	{
		if (WithinScope()) {
			return true;
		}
		return false;
	}
}