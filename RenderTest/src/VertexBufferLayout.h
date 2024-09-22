#pragma once

#include <vector>

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type);
};

class VertexBufferLayout
{
public:
	VertexBufferLayout() {}

	inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }

	void Bind() const;
	void Unbind() const;

	void Push(unsigned int type, unsigned int count);

private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride = 0;

};

