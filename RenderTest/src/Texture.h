#pragma once

#include <string>

#include "RenderObjectBase.h"

class Texture : public RenderObjectBase
{
public:
	Texture(const std::string& filepath);
	~Texture();

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

	void BindToSlot(unsigned int slot) const;
	virtual void Bind() const override;
	virtual void Unbind() const override;

private:
	unsigned int m_RendererID;
	int m_Width, m_Height, m_BPP;

#if _DEBUG
	std::string m_Filepath;
#endif
};
