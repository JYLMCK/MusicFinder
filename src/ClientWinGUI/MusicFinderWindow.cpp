#include "MusicFinderWindow.h"

MusicFinderWindow::MusicFinderWindow()
{
	constexpr const wchar_t* CLASS_NAME = L"Music Finder Window";
	_wc.cbSize = sizeof(_wc);
	_wc.hInstance = nullptr;
	_wc.lpfnWndProc = HandleMsgSetup;
	_wc.lpszClassName = CLASS_NAME;
	_wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);

	RegisterClassExW(&_wc);

	_hMenuBar = CreateMenu();
	_hMenu = CreateMenu();
	AppendMenuW(_hMenu, MF_STRING, 0, L"About Music Finder");
	AppendMenuW(_hMenu, MF_STRING, 1, L"Support JYLMCK");
	AppendMenuW(_hMenuBar, MF_POPUP, (UINT_PTR)_hMenu, L"Help");
	
	int nWidth = GetSystemMetrics(SM_CXSCREEN);
	int nHeight = GetSystemMetrics(SM_CYSCREEN);
	int buttonWidth = 90;
	int buttonHeight = 25;

	_mainHWND = CreateWindowExW(0, CLASS_NAME, L"Music Finder", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
	                            CW_USEDEFAULT, nWidth / 2, nHeight / 2, nullptr, _hMenuBar,
	                            nullptr, nullptr);
	_editWin = CreateWindowExW(0, L"EDIT", L"", WS_CHILD | WS_BORDER, nWidth / 8, nHeight / 8,
	                           nWidth / 4 - buttonWidth - 10, buttonHeight, _mainHWND, nullptr,
	                           nullptr, nullptr);
	_searchBtn = CreateWindowExW(0, L"BUTTON", L"Search!", WS_CHILD | BS_DEFPUSHBUTTON,
	                            nWidth * 3 / 8 - buttonWidth, nHeight / 8, buttonWidth,
	                            buttonHeight, _mainHWND, nullptr, nullptr, nullptr);

	HFONT hFont = CreateFontW(0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L"Calibri Light");
	SendMessageW(_editWin, WM_SETFONT, (WPARAM)hFont, 0);
	SendMessageW(_searchBtn, WM_SETFONT, (WPARAM)hFont, 0);

	ShowWindow(_mainHWND, SW_SHOWDEFAULT);
	ShowWindow(_editWin, SW_SHOWDEFAULT);
	ShowWindow(_searchBtn, SW_SHOWDEFAULT);
}

LRESULT CALLBACK MusicFinderWindow::HandleMsgSetup(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_NCCREATE)
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		MusicFinderWindow* const pWnd = static_cast<MusicFinderWindow*>(pCreate->lpCreateParams);
		SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtrW(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&MusicFinderWindow::HandleMsgThunk));
		return pWnd->HandleMessage(hWnd, uMsg, wParam, lParam);
	}
	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK MusicFinderWindow::HandleMsgThunk(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	MusicFinderWindow* const pWnd = reinterpret_cast<MusicFinderWindow*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
	return pWnd->HandleMessage(hWnd, uMsg, wParam, lParam);
}

LRESULT MusicFinderWindow::HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT	ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_BACKGROUND));
		EndPaint(hWnd, &ps);
		return 0;
	}

	case WM_COMMAND:
	{
		if (HIWORD(wParam) == 0 && LOWORD(wParam) == 1 && lParam == 0)
		{
			MessageBoxW(hWnd,
			            L"You can support JYLMCK by donating! We accept donations at\n\nWoori "
			            L"1002-059-453022",
			            L"Support JYLMCK", MB_OK);
		}
	}
	}
	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

