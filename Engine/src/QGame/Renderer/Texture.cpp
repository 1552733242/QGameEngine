#include "qgpch.h"
#include "Texture.h"
#include "Renderer.h"
#include "QGame/Platform/OpenGL/OpenGLTexture2D.h"
namespace QGame {
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: GAME_CORE_ASSERT(false, "RendererAPI:: None is currently not supported "); return nullptr;
		case RendererAPI::API::OpenGL:											return std::make_shared<OpenGLTexture2D>(path);
		}

		GAME_CORE_ASSERT(false, "Unknown RenderAPI")
			return nullptr;
	}
}