#pragma once

#include "Renderer.h"
#include "imgui/imgui.h"

namespace test {

	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}

	protected:
		Renderer renderer;
		ImGuiIO& io = ImGui::GetIO();
		
	};

}

