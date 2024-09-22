#pragma once

#include <string>

class Texture
{
public:
	Texture(const std::string& filepath);
	~Texture();

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

private:
	unsigned int m_RendererID;
	int m_Width, m_Height, m_BPP;

#if _DEBUG
	std::string m_Filepath;
#endif
};
