#pragma once

#include "Test.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace test {

	class TestTwoObjectsUniform : public Test
	{
	public:
		TestTwoObjectsUniform();
		~TestTwoObjectsUniform();

		virtual void OnUpdate(float deltaTime) override;
		virtual void OnRender() override;
		virtual void OnImGuiRender() override;

	private:
		float positions[16] = {
			-50.f,  -50.f,  0.f,  0.f,
			 50.f,  -50.f,  1.f,  0.f,
			 50.f,   50.f,  1.f,  1.f,
			-50.f,   50.f,  0.f,  1.f,
		};

		unsigned int indices[6] = {
			0, 1, 2,
			2, 3, 0,
		};

		VertexBuffer vb = VertexBuffer(positions, 16 * sizeof(float));
		VertexBufferLayout layout = VertexBufferLayout({ { GL_FLOAT, 2 }, { GL_FLOAT, 2 } });
		IndexBuffer ib = IndexBuffer(indices, 6);
		VertexArray va = VertexArray(vb, layout, ib);
		Shader shader = Shader("res/shaders/Basic.shader");
		Texture texture = Texture("res/textures/apple.png");

		glm::mat4 proj = glm::ortho(0.f, 1920.f, 0.f, 1080.f, -1.f, 1.f); // our space
		glm::mat4 view = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 0.f)); // our pov

		glm::vec3 translationA = glm::vec3(200.f, 200.f, 0.f);
		glm::vec3 translationB = glm::vec3(400.f, 200.f, 0.f);

	};

}

