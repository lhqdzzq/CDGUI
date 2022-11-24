#include"cgpch.h"
#include"Button.h"
#include<GLFW/glfw3.h>
#include"glad/glad.h"
namespace cdgui
{
	Button::Button(glm::vec2 pos)
		:m_Size({ 0.2f, 0.1f }), m_Color({ 0.8f, 0.8f, 0.8f }), text(std::string()), m_Mode(GL_TRIANGLES)
	{
		m_Position = pos;
		m_ButtonShader = Shader::Create("F:/code/CDcode/IntegratedDesignOfElectronicInformationSystems/CDGUI_Course/CDGUI/assets/shaders/basis.glsl");
		//顶点数组
		m_ButtonVertexArray = VertexArray::Create();
		Update();
	}
	Button::Button(glm::vec2 pos, glm::vec2 size)
		:m_Color({ 0.8f, 0.8f, 0.8f }), text(std::string()), m_Mode(GL_TRIANGLES)
	{
		m_Position = pos;
		m_Size = size;
		m_ButtonShader = Shader::Create("F:/code/CDcode/IntegratedDesignOfElectronicInformationSystems/CDGUI_Course/CDGUI/assets/shaders/basis.glsl");
		//顶点数组
		m_ButtonVertexArray = VertexArray::Create();
		Update();
	}
	Button::Button(glm::vec2 pos, glm::vec2 size, glm::vec3 color)
		:m_Mode(GL_TRIANGLES)
	{
		m_Position = pos;
		m_Size = size;
		m_Color = color;
		m_ButtonShader = Shader::Create("F:/code/CDcode/IntegratedDesignOfElectronicInformationSystems/CDGUI_Course/CDGUI/assets/shaders/basis.glsl");
		//顶点数组
		m_ButtonVertexArray = VertexArray::Create();
		Update();
	}
	Button::~Button()
	{
	}
	void Button::SetPosition(glm::vec2 pos)
	{
		m_Position = pos;
		Update();
	}
	glm::vec2 Button::GetPosition()
	{
		return m_Position;
	}
	void Button::SetColor(glm::vec3 color)
	{
		m_Color = color;
		Update();
	}
	glm::vec3 Button::GetColor()
	{
		return m_Color;
	}
	void Button::SetSize(glm::vec2 size)
	{
		m_Size = size;
		Update();
	}
	glm::vec2 Button::GetSize()
	{
		return m_Size;
	}
	bool Button::IsPressed()
	{
		if (Input::IsMouseButtonPressed(CG_MOUSE_BUTTON_LEFT)) {
			//CG_TRACE("IsMouseButtonPressed");
			if (WithinScope()) {
				return true;
			}
		}
		return false;
	}
	void Button::Update()
	{
		//Vertex Buffer
		float vertices[4 * 6] = {
			m_Position.x - m_Size.x,m_Position.y - m_Size.y, 0.0f,	m_Color.r, m_Color.g, m_Color.b,//左下
			m_Position.x + m_Size.x,m_Position.y - m_Size.y, 0.0f,	m_Color.r, m_Color.g, m_Color.b,//右下
			m_Position.x + m_Size.x,m_Position.y + m_Size.y, 0.0f,	m_Color.r, m_Color.g, m_Color.b,//右上
			m_Position.x - m_Size.x,m_Position.y + m_Size.y, 0.0f,	m_Color.r, m_Color.g, m_Color.b //左上
		};
		//Index Buffer
		unsigned int indices[6] = {
			0,1,2,
			2,3,0
		};

		//顶点buffer
		std::shared_ptr<cdgui::VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(cdgui::VertexBuffer::Create(vertices, sizeof(vertices)));
		cdgui::BufferLayout layout = {
			{cdgui::ShaderDataType::Float3,"a_Position"},
			{cdgui::ShaderDataType::Float3,"a_color"}
		};
		m_VertexBuffer->SetLayout(layout);
		m_ButtonVertexArray->AddVertexBuffer(m_VertexBuffer);
		//索引buffer
		std::shared_ptr<cdgui::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(cdgui::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));
		m_ButtonVertexArray->SetIndexBuffer(m_IndexBuffer);

	}
	bool Button::WithinScope()
	{
		std::pair<float,float> mousePos = Input::GetMousePosition();
		CG_INFO("x{0}, y{1}", mousePos.first, mousePos.second);
		float winWidth = Application::Get().GetWindow().GetWidth();
		float winHeight = Application::Get().GetWindow().GetHeight();

		float left = (m_Position.x - m_Size.x) * (winWidth / 2) + winWidth / 2;
		float right = (m_Position.x + m_Size.x) * (winWidth / 2) + winWidth / 2;
		float bottom = (-(m_Position.y - m_Size.y)) * (winHeight / 2) + winHeight / 2;
		float top = (-(m_Position.y + m_Size.y)) * (winHeight / 2) + winHeight / 2;

		if (left <= static_cast<float>(mousePos.first) && static_cast<float>(mousePos.first) <= right &&
			top <= static_cast<float>(mousePos.second) && static_cast<float>(mousePos.second) <= bottom) {
			return true;
		}
		return false;
	}
	void Button::Draw()
	{
		Renderer::SetMode(m_Mode);
		Renderer::Submit(m_ButtonShader, m_ButtonVertexArray);
	}
	void Button::SetMode(unsigned int mode)
	{
		m_Mode = mode;
	}
}