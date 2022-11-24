#include"cgpch.h"
#include"OpenGLRendererAPI.h"
#include"glad/glad.h"

namespace cdgui
{
	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_Mode = GL_TRIANGLES;
	}
	void OpenGLRendererAPI::SetClearColor(const glm::vec4 color)
	{
		glClearColor(color.r, color.g, color.b, color.r);
	}
	void OpenGLRendererAPI::SetMode(const unsigned int mode)
	{
		m_Mode = mode;
	}
	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		glDrawElements(m_Mode, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}