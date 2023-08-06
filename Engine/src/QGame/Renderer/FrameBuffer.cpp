#include "qgpch.h"
#include "FrameBuffer.h"
#include "QGame/Renderer/Renderer.h"
#include "QGame/Platform/OpenGL/OpenGLFrameBuffer.h"


namespace QGame {

	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: GAME_CORE_ASSERT(false, "RendererAPI:: None is currently not supported "); return nullptr;
		case RendererAPI::API::OpenGL:											return CreateRef<OpenGLFrameBuffer>(spec);
		}

		GAME_CORE_ASSERT(false, "Unknown RenderAPI")
			return nullptr;
	}

}