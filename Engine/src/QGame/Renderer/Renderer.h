#pragma once

#include "QGame/Renderer/RendererCommand.h"
#include "QGame/Renderer/OrthgraphicCamera.h"
namespace QGame {



	class Renderer {

	public:
		static void BeginScene(OrthgraphicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }


	};
}