#include "VertexBufferLayout.h"

#include "Renderer.h"

unsigned int VertexBufferElement::GetSize() const
{
	return count * GetSizeOfType(type);;
}

unsigned int VertexBufferElement::GetSizeOfType(unsigned int type)
{
	switch (type)
	{
	case GL_FLOAT:
		return sizeof(float);
	case GL_UNSIGNED_INT:
		return sizeof(unsigned int);
	default:
		ASSERT(false);
		return 0;
	}
}

VertexBufferLayout::VertexBufferLayout()
{
}

VertexBufferLayout::VertexBufferLayout(const VertexBufferElement& element)
{
	Push(element);
}

VertexBufferLayout::VertexBufferLayout(const std::vector<VertexBufferElement>& elements)
	: m_Elements(elements)
{
	for (const VertexBufferElement& element : m_Elements)
	{
		m_Stride += element.GetSize();
	}
}

void VertexBufferLayout::Bind() const
{
	unsigned int offset = 0;
	for (unsigned int i = 0; i < m_Elements.size(); ++i)
	{
		const VertexBufferElement& element = m_Elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, m_Stride, (const void*)offset));
		offset += element.GetSize();
	}
}

void VertexBufferLayout::Unbind() const
{
	for (unsigned int i = 0; i < m_Elements.size(); ++i)
	{
		GLCall(glDisableVertexAttribArray(i));
	}
}

void VertexBufferLayout::Push(const VertexBufferElement& element)
{
	m_Elements.emplace_back(element);
	m_Stride += element.GetSize();
}

void VertexBufferLayout::Push(const std::vector<VertexBufferElement>& elements)
{
	for (const VertexBufferElement& element : m_Elements)
	{
		Push(element);
	}
}
