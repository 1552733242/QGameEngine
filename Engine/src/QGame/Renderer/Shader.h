#pragma once

#include "D:\QGameEngine\QGameEngine\Engine\vendor_src\glm\glm\glm.hpp"
namespace QGame {

	class Shader {
	
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();
		void Bind()const;
		void UnBind()const;

		void UploadUniformMat4(const std::string& name,const glm::mat4& matrix);
	private:
		
		uint32_t m_RendererID;
	};
	

}