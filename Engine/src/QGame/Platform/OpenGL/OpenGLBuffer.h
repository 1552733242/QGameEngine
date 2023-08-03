#pragma once
#include "QGame/Renderer/Buffer.h"



namespace QGame {

	class OpenGLVertexBuffer :public VertexBuffer {
	public:
		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* verices, uint32_t size);

		virtual ~OpenGLVertexBuffer();
		virtual void Bind()const override;
		virtual void UnBind()const override;
		
		virtual void SetData(const void* data, uint32_t size)override;
		virtual void SetLayout(const BufferLayout& layout)override { m_Layout = layout; }
		virtual const BufferLayout& GetLayout()const override { return m_Layout; } 

		virtual  uint32_t GetCount()const override { return m_Count; }
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
		BufferLayout m_Layout;
	};
	class OpenGLIndexBuffer :public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t * verices, uint32_t size);
		virtual ~OpenGLIndexBuffer();
		virtual void Bind()const;
		virtual void UnBind()const;
		virtual uint32_t GetCount()const override { return m_Count; }

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;

	};

}