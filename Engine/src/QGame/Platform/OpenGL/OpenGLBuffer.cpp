#include "qgpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace QGame {



	OpenGLVertexBuffer::OpenGLVertexBuffer(float* verices, uint32_t size)
	{
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, verices, GL_STATIC_DRAW);
		m_Count = size / sizeof(float);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//IndexBuffer:


	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* verices, uint32_t size)
	{
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, verices, GL_STATIC_DRAW);
		m_Count = size / sizeof(uint32_t);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::UnBind() const
	{

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}