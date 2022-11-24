#define _CRT_SECURE_NO_WARNINGS

#include<cdgui.h>
#include"glm/glm.hpp"

using namespace std;

class exampleLayer :public cdgui::Layer
{
public:
    exampleLayer() 
        :Layer("example"),m_Camera(-1.0f, 1.0f, -1.0f, 1.0f), scroll({ 0.9f,0.0f })
    {
		m_CameraPosition = m_Camera.GetPosition();
		m_CameraRotation = m_Camera.GetRotation();
		//Vertex Array
		m_ShandBoxVertexArray = cdgui::VertexArray::Create();
		//Vertex Buffer
		float vertices[4 * 5] = {
			-0.5f,-0.5f,0.0f,	0.0f, 0.0f,//×óÏÂ
			 0.5f,-0.5f,0.0f,	1.0f, 0.0f,//ÓÒÏÂ
			 0.5f,0.5f,0.0f,	1.0f, 1.0f,
			 -0.5f,0.5f,0.0f,	0.0f, 1.0f
		};
		std::shared_ptr<cdgui::VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(cdgui::VertexBuffer::Create(vertices, sizeof(vertices)));
		cdgui::BufferLayout layout = {
			{cdgui::ShaderDataType::Float3,"a_Position"},
			{cdgui::ShaderDataType::Float2,"a_TexCoord"}
		};
		m_VertexBuffer->SetLayout(layout);
		m_ShandBoxVertexArray->AddVertexBuffer(m_VertexBuffer);

		//Index Buffer
		unsigned int indices[6] = {
			0,1,2,
			2,3,0
		};
		std::shared_ptr<cdgui::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(cdgui::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));
		m_ShandBoxVertexArray->SetIndexBuffer(m_IndexBuffer);


		//texture(u_Texture, v_TexCoord)
		//m_Shader.reset(cdgui::Shader::Create(vertexSource, fragmentSource));
		m_ShandBoxShader = cdgui::Shader::Create("F:/code/CDcode/IntegratedDesignOfElectronicInformationSystems/CDGUI_Course/CDGUI/assets/shaders/texture.glsl");

		m_Texture = cdgui::Texture2D::Create("F:/code/CDcode/IntegratedDesignOfElectronicInformationSystems/CDGUI_Course/CDGUI/assets/textures/323640.jpg");
		//m_BackTexture = cdgui::Texture2D::Create("F:/code/CGcode/IntegratedDesignOfElectronicInformationSystems/CGGUI/CGGUI/assets/textures/QQÍ¼Æ¬20200719104654.jpg");
		std::dynamic_pointer_cast<cdgui::OpenGLShader>(m_ShandBoxShader)->Bind();
		std::dynamic_pointer_cast<cdgui::OpenGLShader>(m_ShandBoxShader)->UploadUniformInt("u_Texture", 0);
		
		radioButtons.AddRadioButton(new cdgui::RadioButtons::RadioButton());
		radioButtons.AddRadioButton(new cdgui::RadioButtons::RadioButton({ -0.3f,0.5f }));

		checkBoxes.AddCheckBox(new cdgui::CheckBoxes::CheckBox());
		checkBoxes.AddCheckBox(new cdgui::CheckBoxes::CheckBox({ 0.3f,-0.5f }));
	}
    void OnUpdate(cdgui::Timestep ts) override
    {
		//CG_CORE_INFO("Delta time {0}s, ({1})ms", ts.GetSeconds(), ts.GetMilliSeconds());

		if (cdgui::Input::IsKeyPressed(CG_KEY_LEFT)) {
			m_CameraPosition.x -= 1.1f * ts;
		}
		else if (cdgui::Input::IsKeyPressed(CG_KEY_RIGHT)) {
			m_CameraPosition.x += 1.1f * ts;
		}
		if (cdgui::Input::IsKeyPressed(CG_KEY_UP)) {
			m_CameraPosition.y -= 1.1f * ts;
		}
		else if (cdgui::Input::IsKeyPressed(CG_KEY_DOWN)) {
			m_CameraPosition.y += 1.1f * ts;
		}

		if (cdgui::Input::IsKeyPressed(CG_KEY_A)) {
			m_CameraRotation += 30.0f * ts;
		}
		else if (cdgui::Input::IsKeyPressed(CG_KEY_D)) {
			m_CameraRotation -= 30.0f * ts;
		}
        cdgui::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        cdgui::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		//m_Camera.SetPosition({ 0.5f, 0.5f, 0.0f });
		//m_Camera.SetRotation(45.0f);


        cdgui::Renderer::BeginScene(m_Camera);

		//m_Texture->Bind();
        //cdgui::Renderer::Submit(m_ShandBoxShader, m_ShandBoxVertexArray);

		scroll.Draw();
		float range = scroll.Dragged();

		cdgui::Button bt({ 0.0f,0.0f });
		bt.SetColor({ range * 0.2f,range * 0.5f,range * 0.8f });
		bt.Draw();
		if (bt.IsPressed()) {
			CG_INFO("buttom is pressed");
		}

		cdgui::Circle cc({ -0.5f,0.5f }, 0.2f);
		cc.Draw();

		radioButtons.Draw();

		checkBoxes.Draw();
		//m_BackTexture->Bind();
		//cdgui::Renderer::Submit(m_Shader, m_VertexArray);

        cdgui::Renderer::EndScene();
    }

    void OnEvent(cdgui::Event& e) override
    {
        if (e.GetEventType() == cdgui::EventType::KeyPressed) {
            cdgui::KeyPressedEvent& event = (cdgui::KeyPressedEvent&)e;
            if (event.GetKeyCode() == CG_KEY_A) {
                //CG_TRACE("A key is pressed!");
            }
        }
		scroll.OnEvent(e);
		radioButtons.OnEvent(e);
		checkBoxes.OnEvent(e);
    }
private:
    std::shared_ptr<cdgui::Shader> m_ShandBoxShader;
    std::shared_ptr<cdgui::VertexArray> m_ShandBoxVertexArray;
	cdgui::Ref<cdgui::Texture2D> m_Texture, m_BackTexture;

	cdgui::Scroll scroll;
	cdgui::RadioButtons radioButtons;
	cdgui::CheckBoxes checkBoxes;

	cdgui::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation;
};

class SandBox:public cdgui::Application
{
public:
    SandBox() {
        PushLayer(new exampleLayer());
    }
    ~SandBox()
    {

    }
};


cdgui::Application* cdgui::CreateApplication()
{
    return new SandBox();
}

