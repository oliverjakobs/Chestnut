#include <Chestnut.h>

#include "imgui/imgui.h"

class ExampleLayer : public chst::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (chst::Input::IsKeyPressed(CHST_KEY_TAB))
			CHST_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}

	void OnEvent(chst::Event& event) override
	{
		if (event.GetEventType() == chst::EventType::KeyPressed)
		{
			chst::KeyPressedEvent& e = (chst::KeyPressedEvent&)event;
			if (e.GetKeyCode() == CHST_KEY_TAB)
				CHST_TRACE("Tab key is pressed (event)!");

			CHST_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

};

class Sandbox : public chst::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

chst::Application* chst::CreateApplication()
{
	return new Sandbox();
}