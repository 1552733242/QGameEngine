#pragma once
#include "QGame/Renderer/FrameBuffer.h"

namespace QGame {

	class OpenGLFrameBuffer : public FrameBuffer {

	public:
		OpenGLFrameBuffer(const FrameBufferSpecification& spec);
		virtual ~OpenGLFrameBuffer();

		void Invalidate();
		virtual void Bind()const override;
		virtual void UnBind()const override;
		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual uint32_t GetColorAttachmentRendererID()const override{ return m_ColorAttachment; }
		virtual const FrameBufferSpecification& GetSpecification()const override { return m_Specification; }
		 
	private:

		uint32_t m_RendererID = 0;
		
		uint32_t m_ColorAttachment = 0 , m_DepthAttachment = 0;
		FrameBufferSpecification m_Specification;

	};


}