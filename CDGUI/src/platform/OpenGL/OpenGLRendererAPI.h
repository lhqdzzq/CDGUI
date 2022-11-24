#pragma once
#include"CDGUI/Renderer/RendererAPI.h"

namespace cdgui
{
	class OpenGLRendererAPI :public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void SetClearColor(const glm::vec4 color) override;
		virtual void SetMode(const unsigned int mode) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	private:
		unsigned int m_Mode;
	};
}