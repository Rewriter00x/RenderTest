#pragma once

#include "Test.h"

#include <array>

class VertexBuffer;
class IndexBuffer;
class VertexArray;
class Shader;
class Texture;

namespace test {

	class TestBatchObjects : public Test
	{
	public:
		TestBatchObjects();

		virtual void OnRender() override;

	private:
		std::array<std::unique_ptr<Texture>, 2> m_Textures;

		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexArray> m_VertexArray;
		std::unique_ptr<Shader> m_Shader;

	};

}

