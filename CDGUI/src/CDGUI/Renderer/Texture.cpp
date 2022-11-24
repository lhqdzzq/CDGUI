#include"cgpch.h"
#include"Texture.h"

#include"Renderer.h"
#include"platform/OpenGL/OpenGLTexture2D.h"
namespace cdgui
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		CG_CORE_ASSERTS(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLTexture2D>(path);
		}
		return nullptr;
	}
}