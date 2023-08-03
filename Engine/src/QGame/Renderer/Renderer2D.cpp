#include "qgpch.h"
#include "QGame/Renderer/Renderer2D.h"
#include "QGame/Renderer/RendererCommand.h"
#include <glm/ext/matrix_transform.hpp>

namespace QGame {

	struct QuadVertex {
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
	};

	struct Renderer2DStorage {

		const uint32_t MaxQuads = 10000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;


		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader>  TextureShader;
		Ref<Texture2D>WhiteTexture;


		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;


	};
	static Renderer2DStorage s_Data;

	void Renderer2D::Init()
	{

		s_Data.QuadVertexArray = VertexArray::Create();

		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));

		s_Data.QuadVertexBuffer->SetLayout( {

			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"},
			{ShaderDataType::Float2, "a_TexCoord"},

			});
		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];



		uint32_t* quadIndex = new uint32_t[s_Data.MaxIndices];
		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6) {

			quadIndex[i + 0] = offset + 0;
			quadIndex[i + 1] = offset + 1;
			quadIndex[i + 2] = offset + 2;
			quadIndex[i + 3] = offset + 2;
			quadIndex[i + 4] = offset + 3;
			quadIndex[i + 5] = offset + 0;
			offset += 4;
		}


		Ref<IndexBuffer> squareIB = IndexBuffer::Create(quadIndex,  s_Data.MaxIndices * sizeof(uint32_t));
		s_Data.QuadVertexArray->SetIndexBuffer(squareIB);
		delete[] quadIndex;



		s_Data.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));



		s_Data.TextureShader = Shader::Create("shaders/Texture.glsl");
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetInt("u_Texture", 0);


	}

	void Renderer2D::Shutdown()
	{
	}


	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{

		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
	}

	void Renderer2D::EndScene()
	{
		uint32_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;

		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);
		Flush();
	}

	void Renderer2D::Flush()
	{
		RendererCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
	}


	void Renderer2D::DrawQuare(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuare({ position.x,position.y,0.0f }, size, color);
	}

	void Renderer2D::DrawQuare(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{

		s_Data.QuadVertexBufferPtr->Position = position;
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f,0.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x,position.y,0.0f };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f,0.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x,position.y + size.y ,0.0f };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f,1.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x,position.y + size.y,0.0f };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f,1.0f };
		s_Data.QuadVertexBufferPtr++;


		s_Data.QuadIndexCount += 6;

		/*s_Data.WhiteTexture->Bind();

		s_Data.TextureShader->SetFloat("u_TilingFactor", 1.0f);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data.TextureShader->SetMat4("u_Transform", transform);

		s_Data.QuadVertexArray->Bind();
		RendererCommand::DrawIndexed(s_Data.QuadVertexArray);*/
	}
	void Renderer2D::DrawQuare(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture, float tilingFactor)
	{
		DrawQuare({ position.x,position.y,0.0f }, size, texture, tilingFactor);
	}
	void Renderer2D::DrawQuare(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture, float tilingFactor)
	{
		s_Data.TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));
		s_Data.TextureShader->SetFloat("u_TilingFactor", tilingFactor);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data.TextureShader->SetMat4("u_Transform", transform);

		texture->Bind();
		s_Data.QuadVertexArray->Bind();
		RendererCommand::DrawIndexed(s_Data.QuadVertexArray);
	}
}