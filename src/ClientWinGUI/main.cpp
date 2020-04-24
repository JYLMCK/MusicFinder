#include "MusicFinderWindow.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, int)
{
	MusicFinderWindow mainWindow;

	MSG msg;
	while (GetMessageA(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}

	return 0;
}
