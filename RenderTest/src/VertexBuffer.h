#pragma once

#include "RenderObjectBase.h"

#include <GL/glew.h>

class VertexBuffer : public RenderObjectBase
{
public:
	VertexBuffer(const void* data, unsigned int size, unsigned int mode = GL_STATIC_DRAW);
	~VertexBuffer();

	virtual void Bind() const override;
	virtual void Unbind() const override;

	void Refill(const void* data, unsigned int size) const;

};
