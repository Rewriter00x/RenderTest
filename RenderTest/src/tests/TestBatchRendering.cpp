#include "TestBatchRendering.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"

namespace test {

	TestBatchRendering::TestBatchRendering()
	{
		float vertices[] = {
			-.5f,  0.f, .2f, .6f, 1.f,
			 .5f,  0.f, 1.f, .3f, .2f,
			 .5f,  .5f, 1.f, .3f, .2f,
			-.5f,  .5f, .2f, .6f, 1.f,

			-.5f, -.5f, 1.f, .9f, .2f,
			 .5f, -.5f, .1f, .1f, .1f,
			 .5f,  0.f, .1f, .1f, .1f,
			-.5f,  0.f, 1.f, .9f, .2f,
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0,

			4, 5, 6,
			6, 7, 4,
		};

		VertexBufferLayout layout({ { GL_FLOAT, 2 }, { GL_FLOAT, 3 } });

		m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(indices[0]));
		m_VertexArray = std::make_unique<VertexArray>(*m_VertexBuffer, layout, *m_IndexBuffer);
		m_Shader = std::make_unique<Shader>("res/shaders/Batch.shader");
	}

	void TestBatchRendering::OnRender()
	{
		renderer.Clear();
		renderer.Draw(*m_VertexArray, *m_Shader);
	}

}