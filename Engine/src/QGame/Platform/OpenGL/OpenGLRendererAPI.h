#pragma once

#include "QGame/Renderer/RendererAPI.h"
namespace QGame {

	class OpenGLRendererAPI:public RendererAPI {

	public:
		virtual void Init();
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;


	};


}