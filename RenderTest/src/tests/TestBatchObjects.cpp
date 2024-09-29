#include "TestBatchObjects.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/ext/matrix_clip_space.hpp"

namespace test {

	TestBatchObjects::TestBatchObjects()
	{
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		float vertices[] = {
			-3.f, -1.f, 0.f, 0.f, 0.f,
			-1.f, -1.f, 1.f, 0.f, 0.f,
			-1.f,  1.f, 1.f, 1.f, 0.f,
			-3.f,  1.f, 0.f, 1.f, 0.f,

			 1.f, -1.f, 0.f, 0.f, 1.f,
			 3.f, -1.f, 1.f, 0.f, 1.f,
			 3.f,  1.f, 1.f, 1.f, 1.f,
			 1.f,  1.f, 0.f, 1.f, 1.f,
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0,

			4, 5, 6,
			6, 7, 4,
		};

		VertexBufferLayout layout({ { GL_FLOAT, 2 }, { GL_FLOAT, 2 }, { GL_FLOAT, 1 } });

		m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(indices[0]));
		m_VertexArray = std::make_unique<VertexArray>(*m_VertexBuffer, layout, *m_IndexBuffer);
		m_Shader = std::make_unique<Shader>("res/shaders/BatchTex.shader");

		glm::mat4 proj = glm::ortho(-4.f, 4.f, -2.f, 2.f, -1.f, 1.f);
		m_Shader->SetUniformMat4f("u_MVP", proj);

		int samplers[] = { 0, 1 };
		m_Shader->SetUniform1iv("u_Textures", samplers);
		
		m_Textures[0] = std::make_unique<Texture>("res/textures/apple.png");
		m_Textures[1] = std::make_unique<Texture>("res/textures/banana.png");
	}

	void TestBatchObjects::OnRender()
	{
		renderer.Clear();
		
		for (unsigned int i = 0; i < m_Textures.size(); ++i)
		{
			m_Textures[i]->BindToSlot(i);
		}

		renderer.Draw(*m_VertexArray, *m_Shader);
	}

}
