#pragma once

#include "QGame/Renderer/RendererCommand.h"
#include "QGame/Renderer/OrthgraphicCamera.h"
#include "QGame/Renderer/Shader.h"
namespace QGame {



	class Renderer {

	public:
		static void Init();
		static void BeginScene(OrthgraphicCamera& camera);
		static void EndScene();
		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, glm::mat4 transform = glm::mat4(1.0f));
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewPojectionMatrix;

		};
		static SceneData* m_SceneData;
	};
}