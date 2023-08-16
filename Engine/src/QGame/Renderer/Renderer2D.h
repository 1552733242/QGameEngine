#pragma once

#include "QGame/Renderer/RendererCommand.h"
#include "QGame/Renderer/OrthgraphicCamera.h"
#include "QGame/Renderer/Shader.h"
#include "QGame/Renderer/Texture.h"
#include "QGame/Renderer/SubTexture2D.h"
#include "QGame/Renderer/Camera.h"
namespace QGame {



	class Renderer2D {

	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera, const glm::mat4 transform);

		static void BeginScene(const OrthographicCamera& camera);// TODO: Remove;
		static void EndScene();
		static void Flush();


	
		static void DrawQuare(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuare(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuare(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f);
		static void DrawQuare(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f);
		static void DrawQuare(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D>& subtexture, float tilingFactor = 1.0f);
		static void DrawQuare(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D>& subtexture, float tilingFactor = 1.0f);

		static void DrawQuare(const glm::mat4& transform, const glm::vec4& color);
		static void DrawQuare(const glm::mat4& transform, const Ref<Texture2D>& texture, float tilingFactor = 1.0f);


		static void DrawQuare(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawQuare(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawQuare(const glm::vec2& position, const glm::vec2& size, float rotation,const Ref<Texture2D>& texture, float tilingFactor = 1.0f);
		static void DrawQuare(const glm::vec3& position, const glm::vec2& size, float rotation,const Ref<Texture2D>& texture, float tilingFactor = 1.0f);
		static void DrawQuare(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& subtexture, float tilingFactor = 1.0f);
		static void DrawQuare(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& subtexture, float tilingFactor = 1.0f);


		struct Staistics {
			uint32_t DrawCount = 0;
			uint32_t QuadCount = 0;
			uint32_t GetTotalVertexCount() { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() { return QuadCount * 6; }
		};
		static void RestStats();
		static Staistics GetStats();


	private:
		static void FlshAndReset();
	};
}