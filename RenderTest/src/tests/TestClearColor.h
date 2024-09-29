#pragma once

#include "Test.h"

namespace test {

	class TestClearColor : public Test
	{
	public:
		virtual void OnRender() override;
		virtual void OnImGuiRender() override;

	private:
		float m_ClearColor[4] = { .2f, .3f, .8f, 1.f };

	};

}

