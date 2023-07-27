#include "qgpch.h"
#include "Buffer.h"
#include "Renderer.h"

#include "QGame/Platform/OpenGL/OpenGLBuffer.h"

namespace QGame {




	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: GAME_CORE_ASSERT(false, "RendererAPI:: None is currently not supported "); return nullptr;
		case RendererAPI::API::OpenGL:											return new OpenGLVertexBuffer(vertices, size);
		}

		GAME_CORE_ASSERT(false,"Unknown RenderAPI")
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: GAME_CORE_ASSERT(false, "RendererAPI:: None is currently not supported "); return nullptr;
		case RendererAPI::API::OpenGL:											return new OpenGLIndexBuffer(indices, size);
		}

		GAME_CORE_ASSERT(false, "Unknown RenderAPI")
			return nullptr;
	}

}