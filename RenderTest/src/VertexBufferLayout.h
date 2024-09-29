#pragma once

#include <vector>

#include "RenderObjectBase.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	unsigned int GetSize() const;

	static unsigned int GetSizeOfType(unsigned int type);
};

class VertexBufferLayout : public RenderObjectBase
{
public:
	VertexBufferLayout();
	VertexBufferLayout(const VertexBufferElement& element);
	VertexBufferLayout(const std::vector<VertexBufferElement>& elements);

	inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }

	virtual void Bind() const override;
	virtual void Unbind() const override;

	void Push(const VertexBufferElement& element);
	void Push(const std::vector < VertexBufferElement>& elements);

private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride = 0;

};

