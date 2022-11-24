#pragma once
#include"glm/glm.hpp"
#include"CDGUI/Renderer/Shader.h"

namespace cdgui
{
		class OpenGLShader : public Shader 
		{
		public:
			OpenGLShader(const std::string& filepath);
			OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
			virtual ~OpenGLShader();

			virtual const std::string GetName() const override { return m_Name; }

			virtual void Bind() const override;
			virtual void Unbind() const override;

			void UploadUniformInt(const std::string& name, const int value);
			void UploadUniformFloat(const std::string& name, const float value);
			void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
			void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
			void UploadUniformFloat4(const std::string& name, const glm::vec4& value);
			void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

		private:
			std::string ReadFile(const std::string& filepath);
			std::unordered_map<unsigned int, std::string> PreProcess(const std::string& source);
			void Compile(std::unordered_map<unsigned int, std::string>& ShaderSources);
		private:
			unsigned int m_RendererID;
			std::string m_Name;
		};
}