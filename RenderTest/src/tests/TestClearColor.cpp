#include "TestClearColor.h"

#include "Renderer.h"
#include "imgui/imgui.h"

namespace test {

	void TestClearColor::OnRender()
	{
		renderer.Clear();
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
	}

	void TestClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
	}

}