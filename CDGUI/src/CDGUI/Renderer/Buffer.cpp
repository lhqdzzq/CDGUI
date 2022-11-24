#include"cgpch.h"
#include"CDGUI/Core/Core.h"
#include"Buffer.h"

#include"Renderer.h"
#include"platform/OpenGL/OpenGLBuffer.h"

namespace cdgui
{
	VertexBuffer* VertexBuffer::Create(float* vertices, unsigned int size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		CG_CORE_ASSERTS(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return new OpenGLVertexBuffer(vertices, size);
		}
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(unsigned int* indices, unsigned int count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		CG_CORE_ASSERTS(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return new OpenGLIndexBuffer(indices, count);
		}
		return nullptr;
	}
}
