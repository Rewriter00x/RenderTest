#include "TestBatchObjects.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/ext/matrix_clip_space.hpp"

#include <array>

struct Vertex
{
	struct Vec2
	{
		float v0, v1;
	};

	Vec2 pos;
	Vec2 texCoord;
	float texIndex;
};

static std::array<Vertex, 4> CreateQuad(float x, float y, float texIndex)
{
	constexpr float size = 2.f;

	Vertex v0 {};
	v0.pos = { x,		 y };
	v0.texCoord = { 0.f, 0.f };
	v0.texIndex = texIndex;

	Vertex v1 {};
	v1.pos = { x + size, y };
	v1.texCoord = { 1.f, 0.f };
	v1.texIndex = texIndex;

	Vertex v2 {};
	v2.pos = { x + size, y + size };
	v2.texCoord = { 1.f, 1.f };
	v2.texIndex = texIndex;

	Vertex v3 {};
	v3.pos = { x,		 y + size };
	v3.texCoord = { 0.f, 1.f };
	v3.texIndex = texIndex;

	return { v0, v1, v2, v3 };
}

namespace test {

	TestBatchObjects::TestBatchObjects()
	{
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		float rawVertices[] = {
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

		Vertex vertices[8];
		memcpy(vertices, rawVertices, sizeof(vertices));

		pos1[0] = vertices[0].pos.v0;
		pos1[1] = vertices[0].pos.v1;
		pos2[0] = vertices[4].pos.v0;
		pos2[1] = vertices[4].pos.v1;

		VertexBufferLayout layout({ { GL_FLOAT, 2 }, { GL_FLOAT, 2 }, { GL_FLOAT, 1 } });

		m_Textures.push_back(new Texture("res/textures/apple.png"));
		m_Textures.push_back(new Texture("res/textures/banana.png"));
		
		m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices), GL_DYNAMIC_DRAW);
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(indices[0]));
		m_VertexArray = std::make_unique<VertexArray>(*m_VertexBuffer, layout, *m_IndexBuffer);
		m_Shader = std::make_unique<Shader>("res/shaders/BatchTex.shader");

		glm::mat4 proj = glm::ortho(-4.f, 4.f, -2.f, 2.f, -1.f, 1.f);
		m_Shader->SetUniformMat4f("u_MVP", proj);

		int samplers[] = { 0, 1 };
		m_Shader->SetUniform1iv("u_Textures", samplers);
	}

	TestBatchObjects::~TestBatchObjects()
	{
		for (Texture* texture : m_Textures)
		{
			delete texture;
		}
	}

	void TestBatchObjects::OnRender()
	{
		renderer.Clear();

		std::array<Vertex, 4> Quad1 = CreateQuad(pos1[0], pos1[1], 0.f);
		std::array<Vertex, 4> Quad2 = CreateQuad(pos2[0], pos2[1], 1.f);

		Vertex vertices[8];
		memcpy(vertices,				Quad1.data(), Quad1.size() * sizeof(Vertex));
		memcpy(vertices + Quad1.size(), Quad2.data(), Quad2.size() * sizeof(Vertex));

		m_VertexBuffer->Refill(vertices, sizeof(vertices));
		
		for (unsigned int i = 0; i < m_Textures.size(); ++i)
		{
			m_Textures[i]->BindToSlot(i);
		}

		renderer.Draw(*m_VertexArray, *m_Shader);
	}

	void TestBatchObjects::OnImGuiRender()
	{
		ImGui::DragFloat2("Apple", pos1, .1f);
		ImGui::DragFloat2("Banana", pos2, .1f);
	}

}
