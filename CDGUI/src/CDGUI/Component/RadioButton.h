#pragma once
#include"Button.h"
#include"Circle.h"
#include"CDGUI/Event/MouseEvent.h"
#include<string>
#include<unordered_map>
namespace cdgui
{
	//单选按钮类，管理具体的每个单选按钮
	class RadioButtons : public Component
	{
	public:
		//每个具体单选按钮，以圆的位置作为整个按钮的位置
		class RadioButton :public Component
		{
		public:
			RadioButton();
			RadioButton(glm::vec2 pos);

			const std::string GetName() const;
			void SetName(std::string name);
			const std::shared_ptr<Button>& GetBoard() const;
			const std::shared_ptr<Circle>& GetCheck() const;
			virtual void Draw() override;
			virtual void SetMode(unsigned int mode);

		private:
			virtual void Update() override;
			virtual bool WithinScope() override;
		private:
			unsigned int m_Mode;
			std::string m_Name;
			std::shared_ptr<Button> m_Board;
			std::shared_ptr<Circle> m_Check;

			float m_CheckToBoardDistance;
		};

	public:
		RadioButtons();
		RadioButtons(glm::vec2 pos);
		RadioButtons(glm::vec2 pos, glm::vec2 size);

		void OnEvent(Event& e);
		void AddRadioButton(RadioButton* button);
		const std::shared_ptr<RadioButton*>& GetRadioButton(std::string name) const;
		virtual void Draw() override;
		virtual void SetMode(unsigned int mode);

	private:
		virtual void Update() override;
		virtual bool WithinScope() override;
		bool OnMouseButtonPressedEventEvent(MouseButtonPressedEvent& e);
	private:
		unsigned int m_Mode;
		std::string m_ActiveButtonName;
		unsigned int m_Sequence;
		std::unordered_map<std::string, std::shared_ptr<RadioButton*>> m_RadioButtons;
	};
}