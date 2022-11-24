#include"cgpch.h"
#include"RenderCommand.h"

#include"platform/OpenGL/OpenGLRendererAPI.h"
namespace cdgui
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}