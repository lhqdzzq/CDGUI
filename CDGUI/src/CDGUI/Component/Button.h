#pragma once
#include"Component.h"
#include"platform/OpenGL/OpenGLShader.h"
#include"platform/WindowInput.h"
#include"platform/WindowsWindow.h"
#include"CDGUI/Renderer/Renderer.h"
#include"CDGUI/Core/Application.h"
#include"CDGUI/Renderer/Shader.h"
#include"CDGUI/Renderer/VertexArray.h"
#include"CDGUI/Core/MouseButtonCode.h"

#include<string>
namespace cdgui
{
	class Button : public Component
	{
	public:
		Button(glm::vec2 pos);
		Button(glm::vec2 pos, glm::vec2 size);
		Button(glm::vec2 pos, glm::vec2 size, glm::vec3 color);
		~Button();
		void SetPosition(glm::vec2 pos) ;
		glm::vec2 GetPosition() ;
		void SetColor(glm::vec3 color) ;
		glm::vec3 GetColor();
		void SetSize(glm::vec2 size) ;
		glm::vec2 GetSize() ;


		bool IsPressed();
		virtual void Draw();
		virtual void SetMode(unsigned int mode);

	private:
		virtual void Update();
		virtual bool WithinScope();
	private:
		glm::vec2 m_Position;//x y
		glm::vec2 m_Size;//m_Size.x=Width, m_Size.y=Height
		glm::vec3 m_Color;//R G B
		std::string text;
		unsigned int m_Mode;

		std::shared_ptr<cdgui::Shader> m_ButtonShader;
		std::shared_ptr<cdgui::VertexArray> m_ButtonVertexArray;
	};
}