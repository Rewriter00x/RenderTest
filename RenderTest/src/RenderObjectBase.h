#pragma once

class RenderObjectBase
{
public:
	virtual ~RenderObjectBase() {}

	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

protected:
	unsigned int m_RendererID = -1;

};

