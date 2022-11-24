#include"cgpch.h"
#include"VertexArray.h"

#include"Renderer.h"
#include"platform/OpenGL/OpenGLVertexArray.h"

namespace cdgui
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		CG_CORE_ASSERTS(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLVertexArray>();
		}
		return nullptr;
	}
}