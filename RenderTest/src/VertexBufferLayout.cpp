#include "VertexBufferLayout.h"

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

void VertexBufferLayout::Bind() const
{
	unsigned int offset = 0;
	for (unsigned int i = 0; i < m_Elements.size(); ++i)
	{
		const VertexBufferElement& element = m_Elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, m_Stride, (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexBufferLayout::Unbind() const
{
}

void VertexBufferLayout::Push(unsigned int type, unsigned int count)
{
	m_Elements.emplace_back(type, count, GL_FALSE);
	m_Stride += count * VertexBufferElement::GetSizeOfType(type);
}
