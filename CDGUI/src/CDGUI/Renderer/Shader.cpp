#include"cgpch.h"
#include"Shader.h"

#include"Renderer.h"
#include"platform/OpenGL/OpenGLShader.h"
namespace cdgui
{
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		CG_CORE_ASSERTS(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLShader>(filepath);
		}
		return nullptr;
	}
	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		CG_CORE_ASSERTS(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}
		return nullptr;
	}
	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		CG_CORE_ASSERTS(!Exist(name), "shader has already exist!");
		m_Shaders[name] = shader;
	}
	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}
	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		CG_CORE_ASSERTS(Exist(name), "shader not found!");
		return m_Shaders[name];
	}
	bool ShaderLibrary::Exist(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}