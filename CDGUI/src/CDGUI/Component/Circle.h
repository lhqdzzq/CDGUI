#pragma once
#include"CDGUI/Core/Core.h"
#include"Component.h"
#include"CDGUI/Renderer/Shader.h"
#include"CDGUI/Renderer/VertexArray.h"
#include"CDGUI/Core/MouseButtonCode.h"

namespace cdgui
{
	class Circle :public Component
	{
	public:
		Circle(const float radius);
		Circle(glm::vec2 pos, const float radius);

		void SetRadius(unsigned int radius);
		float GetRadius() const;
		void SetPosition(glm::vec2 pos);
		glm::vec2 GetPosition();

		virtual void Draw();
		virtual void SetMode(unsigned int mode);
	private:
		virtual void Update();
		virtual bool WithinScope();
	private:
		unsigned int m_Mode;
		glm::vec2 m_Position;//x y
		glm::vec3 m_Color;//R G B
		float m_Radius;
		float m_Accuracy;
		const double PI = acos(-1.0);

		std::shared_ptr<cdgui::Shader> m_CircleShader;
		std::shared_ptr<cdgui::VertexArray> m_CircleVertexArray;
	};
}