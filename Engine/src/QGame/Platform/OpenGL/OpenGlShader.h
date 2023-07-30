#pragma once

#include "QGame/Renderer/Shader.h"

#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace QGame {

	class OpenGLShader :public Shader {

	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();
		virtual void Bind()const override;
		virtual void UnBind()const override;

		virtual const std::string& GetName()const override { return m_Name; }

		void UploadUinformFloat(const std::string& name, const float& value);
		void UploadUinformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUinformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values);
		
		void UploadUinformInt(const std::string& name, const int& value);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		std::string Readfile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};


}