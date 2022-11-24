#pragma once
#include"Button.h"
#include"Circle.h"
#include"CDGUI/Event/MouseEvent.h"
#include<string>
#include<unordered_map>
namespace cdgui
{
	//多选按钮类，管理具体的每个单选按钮
	class CheckBoxes : public Component
	{
	public:
		//每个具体多选按钮，以圆的位置作为整个按钮的位置
		class CheckBox :public Component
		{
		public:
			CheckBox();
			CheckBox(glm::vec2 pos);

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
		CheckBoxes();
		CheckBoxes(glm::vec2 pos);

		void OnEvent(Event& e);
		void AddCheckBox(CheckBox* checkBox);
		virtual void Draw() override;
		virtual void SetMode(unsigned int mode);

	private:
		virtual void Update() override;
		virtual bool WithinScope() override;
		bool OnMouseButtonPressedEventEvent(MouseButtonPressedEvent& e);
	private:
		unsigned int m_Mode;
		unsigned int m_Sequence;
		std::unordered_map<std::string, std::shared_ptr<CheckBox*>> m_CheckBoxes;
		std::unordered_map<std::string, bool> m_ActiveCheckBoxes;
	};
}