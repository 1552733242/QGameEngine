#pragma once

#include "QGame/Renderer/Shader.h"
namespace QGame {

	class OpenGLShader :public Shader {

	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();
		virtual void Bind()const override;
		virtual void UnBind()const override;

		void UploadUinformFloat(const std::string& name, const float& value);
		void UploadUinformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUinformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values);
		
		void UploadUinformInt(const std::string& name, const int& value);

		void UploadUniformMat3(const std::string& name, const glm::mat4& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:

		uint32_t m_RendererID;
	};


}