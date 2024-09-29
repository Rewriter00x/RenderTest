#pragma once

#include "RenderObjectBase.h"

class VertexBuffer;
class VertexBufferLayout;
class IndexBuffer;

class VertexArray : public RenderObjectBase
{
public:
	VertexArray();
	VertexArray(const VertexBuffer& vb, const VertexBufferLayout& layout);
	VertexArray(const VertexBuffer& vb, const VertexBufferLayout& layout, const IndexBuffer& ib);
	~VertexArray();

	inline unsigned int GetIndexCount() const { return m_IndexCount; }

	virtual void Bind() const override;
	virtual void Unbind() const override;

	void AddVertexBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void AddIndexBuffer(const IndexBuffer& ib);

private:
	unsigned int m_IndexCount = -1;

};

