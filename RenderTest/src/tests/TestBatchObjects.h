#pragma once

#include "Test.h"

#include <vector>

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
		~TestBatchObjects();

		virtual void OnRender() override;
		virtual void OnImGuiRender() override;

	private:
		std::vector<Texture*> m_Textures;

		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexArray> m_VertexArray;
		std::unique_ptr<Shader> m_Shader;

		float pos1[2];
		float pos2[2];

	};

}

