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
		case RendererAPI::API::OpenGL:											return CreateRef<OpenGLTexture2D>(path);
		}

		GAME_CORE_ASSERT(false, "Unknown RenderAPI")
			return nullptr;
	}
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: GAME_CORE_ASSERT(false, "RendererAPI:: None is currently not supported "); return nullptr;
		case RendererAPI::API::OpenGL:											return CreateRef<OpenGLTexture2D>(width,height);
		}

		GAME_CORE_ASSERT(false, "Unknown RenderAPI")
			return nullptr;
	}
}