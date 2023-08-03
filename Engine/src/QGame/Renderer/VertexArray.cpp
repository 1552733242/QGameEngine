#include"qgpch.h"
#include "VertexArray.h"
#include "QGame/Platform/OpenGL/OpenGLVertexArray.h"
#include "Renderer.h"

namespace QGame {
	Ref<VertexArray> VertexArray::Create() {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: GAME_CORE_ASSERT(false, "RendererAPI:: None is currently not supported "); return nullptr;
		case RendererAPI::API::OpenGL:											return std::make_shared<OpenGLVertexArray>();
		}

		GAME_CORE_ASSERT(false, "Unknown RenderAPI")
			return nullptr;
	}

}