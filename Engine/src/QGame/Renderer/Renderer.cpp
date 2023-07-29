#include "qgpch.h"
#include "Renderer.h"
#include "QGame/Platform/OpenGL/OpenGlShader.h"

namespace QGame {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		RendererCommand::Init();
	}

	void Renderer::BeginScene(OrthgraphicCamera& camera)
	{
		m_SceneData->ViewPojectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, glm::mat4 transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewPojectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);
		vertexArray->Bind();
		RendererCommand::DrawIndexed(vertexArray);
	}

}

