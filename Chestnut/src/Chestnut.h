#pragma once

// For use by Chestnut applications
#include "Chestnut/Application.h"
#include "Chestnut/Log.h"

#include "Chestnut/Events/ApplicationEvent.h"
#include "Chestnut/Events/KeyEvent.h"
#include "Chestnut/Events/MouseEvent.h"

#include "Chestnut/Input.h"

// ---Entry Point---------------------
#ifdef CHST_PLATFORM_WINDOWS

extern chst::Application* chst::CreateApplication();

int main(int argc, char** argv)
{
	chst::Log::Init();

	auto app = chst::CreateApplication();
	app->Run();
	delete app;
}

#endif
// -----------------------------------