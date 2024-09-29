#include "VertexArray.h"

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::VertexArray(const VertexBuffer& vb, const VertexBufferLayout& layout)
	: VertexArray()
{
	AddVertexBuffer(vb, layout);
}

VertexArray::VertexArray(const VertexBuffer& vb, const VertexBufferLayout& layout, const IndexBuffer& ib)
	: VertexArray(vb, layout)
{
	AddIndexBuffer(ib);
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}

void VertexArray::AddVertexBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	layout.Bind();
}

void VertexArray::AddIndexBuffer(const IndexBuffer& ib)
{
	Bind();
	ib.Bind();
	m_IndexCount = ib.GetCount();
}
