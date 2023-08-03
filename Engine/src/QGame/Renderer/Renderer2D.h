#pragma once

#include "QGame/Renderer/RendererCommand.h"
#include "QGame/Renderer/OrthgraphicCamera.h"
#include "QGame/Renderer/Shader.h"
#include "QGame/Renderer/Texture.h"
namespace QGame {



	class Renderer2D {

	public:
		static void Init();
		static void Shutdown();

		
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Flush();


	
		static void DrawQuare(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuare(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuare(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture, float tilingFactor = 1.0f);
		static void DrawQuare(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture, float tilingFactor = 1.0f);

	};
}