#pragma once

#include "RenderObjectBase.h"

class VertexBuffer : public RenderObjectBase
{
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	virtual void Bind() const override;
	virtual void Unbind() const override;

};
