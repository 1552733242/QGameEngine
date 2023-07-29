#include"qgpch.h"
#include "Shader.h"
#include "Renderer.h"
#include "QGame/Platform/OpenGL/OpenGlShader.h"
namespace QGame {
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: GAME_CORE_ASSERT(false, "RendererAPI:: None is currently not supported "); return nullptr;
		case RendererAPI::API::OpenGL:											return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		GAME_CORE_ASSERT(false, "Unknown RenderAPI")
			return nullptr;
	}

}