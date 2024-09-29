#include "TestTwoObjectsUniform.h"

#include "Renderer.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

#include "imgui/imgui.h"

namespace test {

	TestTwoObjectsUniform::TestTwoObjectsUniform()
	{
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		texture.BindToSlot(0);
		shader.SetUniform1i("u_Texture", 0);

		va.Unbind();
		shader.Unbind();
		vb.Unbind();
		layout.Unbind();
		ib.Unbind();
	}

	TestTwoObjectsUniform::~TestTwoObjectsUniform()
	{
	}

	void TestTwoObjectsUniform::OnUpdate(float deltaTime)
	{
	}

	void TestTwoObjectsUniform::OnRender()
	{
		renderer.Clear();

		{
			glm::mat4 model = glm::translate(glm::mat4(1.f), translationA); // object transform
			glm::mat4 mvp = proj * view * model;

			shader.SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(va, shader);
		}

		{
			glm::mat4 model = glm::translate(glm::mat4(1.f), translationB); // object transform
			glm::mat4 mvp = proj * view * model;

			shader.SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(va, shader);
		}
	}

	void TestTwoObjectsUniform::OnImGuiRender()
	{
		ImGui::SliderFloat("TranslationA X", &translationA.x, 0.0f, 1920.0f);
		ImGui::SliderFloat("TranslationA Y", &translationA.y, 0.0f, 1080.0f);
		ImGui::SliderFloat("TranslationB X", &translationB.x, 0.0f, 1920.0f);
		ImGui::SliderFloat("TranslationB Y", &translationB.y, 0.0f, 1080.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	}

}