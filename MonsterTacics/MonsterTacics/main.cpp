#include "System/Application.h"
#include <Windows.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	auto& application = Application::Instance();

	if (!application.Initialize())
	{
		return -1;
	}

	application.Run();
	application.Terminate();

	return 0;
}