#pragma once
#include <Windows.h>

class Window
{
protected:
	WNDCLASSEX _wc{0};
	HWND _mainHWND;

public:
};

class MusicFinderWindow : public Window
{
private:
	HWND _editWin, _searchBtn;
	HMENU _hMenuBar, _hMenu;

public:
	MusicFinderWindow();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};
