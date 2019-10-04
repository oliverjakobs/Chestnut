#pragma once

#ifdef CHST_PLATFORM_WINDOWS

extern chst::Application* chst::CreateApplication();

int main(int argc, char** argv)
{
	auto app = chst::CreateApplication();
	app->Run();
	delete app;
}

#endif