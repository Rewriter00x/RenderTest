#pragma once

#include "Test.h"

#include "glm/glm.hpp"
#include "glm/ext/matrix_clip_space.hpp"

#include <memory>

class VertexBuffer;
class IndexBuffer;

namespace test {

	class TestBatchRendering : public Test
	{
	public:
		TestBatchRendering();

		virtual void OnRender() override;

	private:
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexArray> m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		
	};

}

