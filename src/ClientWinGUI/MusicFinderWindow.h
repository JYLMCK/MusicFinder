#pragma once
#include <Windows.h>

class MusicFinderWindow
{
private:
	WNDCLASSEX _wc{0};
	HWND _mainHWND, _editWin, _searchBtn;
	HMENU _hMenuBar, _hMenu;
	int _btnWidth, _btnHeight;
	int _width, _height;

public:
	MusicFinderWindow();
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};
