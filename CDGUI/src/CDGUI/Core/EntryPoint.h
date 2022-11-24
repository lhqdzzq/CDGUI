#pragma once

#ifdef CG_PLATFORM_WINDOWS

extern cdgui::Application* cdgui::CreateApplication();

int main(int argc, int** argv)
{
	cdgui::Log::Init();
	auto app = cdgui::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif // CG_PLATFORM_WINDOWS
