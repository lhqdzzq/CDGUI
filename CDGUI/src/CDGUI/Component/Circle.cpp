#include"cgpch.h"
#include"Circle.h"
#include<GLFW/glfw3.h>
#include<glad/glad.h>
#include"platform/OpenGL/OpenGLShader.h"
#include"CDGUI/Renderer/Renderer.h"
#include"CDGUI/Core/Application.h"
namespace cdgui
{
	Circle::Circle(const float radius)
		:m_Position({ 0.0f,0.0f }), m_Color({ 1.0f,1.0f,1.0f }), m_Accuracy(100), m_Mode(GL_LINE_STRIP)
	{
		m_Radius = radius;
		m_CircleShader = Shader::Create("F:/code/CDcode/IntegratedDesignOfElectronicInformationSystems/CDGUI_Course/CDGUI/assets/shaders/basis.glsl");
		//顶点数组
		m_CircleVertexArray = VertexArray::Create();
		Update();
	}
	Circle::Circle(glm::vec2 pos, const float radius)
		: m_Color({ 1.0f,1.0f,1.0f }), m_Accuracy(100), m_Mode(GL_LINE_STRIP)
	{
		m_Position = pos;
		m_Radius = radius;
		m_CircleShader = Shader::Create("F:/code/CDcode/IntegratedDesignOfElectronicInformationSystems/CDGUI_Course/CDGUI/assets/shaders/basis.glsl");
		//顶点数组
		m_CircleVertexArray = VertexArray::Create();
		Update();
	}
	void Circle::SetRadius(unsigned int radius)
	{
		m_Radius = radius;
		Update();
	}
	float Circle::GetRadius() const
	{
		return m_Radius;
	}
	void Circle::SetPosition(glm::vec2 pos)
	{
		m_Position = pos;
		Update();
	}
	glm::vec2 Circle::GetPosition()
	{
		return m_Position;
	}
	void Circle::Draw()
	{
		Renderer::SetMode(m_Mode);
		Renderer::Submit(m_CircleShader, m_CircleVertexArray);
	}
	void Circle::SetMode(unsigned int mode)
	{
		m_Mode = mode;
	}
	void Circle::Update()
	{
		//Vertex Buffer
		std::vector<float> vertices(static_cast<float>(6 * m_Accuracy));
		//Index Buffer
		std::vector<unsigned int> indices(m_Accuracy);

		for (int i = 0; i < 6 * m_Accuracy; i += 6) {
			//pos
			vertices[i] = m_Position.x + m_Radius * cos(2 * PI * i / m_Accuracy);
			vertices[i + 1] = m_Position.y + m_Radius * sin(2 * PI * i / m_Accuracy);
			vertices[i + 2] = 0.0f;
			//color
			vertices[i + 3] = m_Color.r;
			vertices[i + 4] = m_Color.g;
			vertices[i + 5] = m_Color.b;
		}
		for (int i = 0; i < m_Accuracy; i++) {
			indices[i] = i;
		}

		//顶点buffer
		std::shared_ptr<cdgui::VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(cdgui::VertexBuffer::Create(vertices.data(), 6 * m_Accuracy * sizeof(float)));
		cdgui::BufferLayout layout = {
			{cdgui::ShaderDataType::Float3,"a_Position"},
			{cdgui::ShaderDataType::Float3,"a_color"}
		};
		m_VertexBuffer->SetLayout(layout);
		m_CircleVertexArray->AddVertexBuffer(m_VertexBuffer);
		//索引buffer
		std::shared_ptr<cdgui::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(cdgui::IndexBuffer::Create(indices.data(), m_Accuracy));
		m_CircleVertexArray->SetIndexBuffer(m_IndexBuffer);
	}
	bool Circle::WithinScope()
	{
		return false;
	}
}