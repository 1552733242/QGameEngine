#include "qgpch.h"
#include "Renderer.h"


namespace QGame {

	
	void Renderer::BeginScene(OrthgraphicCamera& camera)
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RendererCommand::DrawIndexed(vertexArray);
	}

}

