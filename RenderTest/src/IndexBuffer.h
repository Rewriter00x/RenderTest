#pragma once

#include "RenderObjectBase.h"

class IndexBuffer : public RenderObjectBase
{
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	inline unsigned int GetCount() const { return m_Count; }

	virtual void Bind() const override;
	virtual void Unbind() const override;

private:
	unsigned int m_Count;

};
