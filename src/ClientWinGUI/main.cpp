#include <Windows.h>
#include <stdio.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT	ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_BACKGROUND));
		EndPaint(hwnd, &ps);
		return 0;
	}
	}
	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, int)
{
	const wchar_t* CLASS_NAME = L"Window Class";

	WNDCLASSEXW wc = { 0 };
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;
	wc.cbSize = sizeof(wc);

	RegisterClassExW(&wc);

	HMENU hMenuBar = CreateMenu();
	HMENU hMenu = CreateMenu();
	AppendMenuW(hMenu, MF_STRING, 0, L"About Music Finder");
	AppendMenuW(hMenu, MF_STRING, 0, L"Support JYLMCK");
	AppendMenuW(hMenuBar, MF_POPUP, (UINT_PTR)hMenu, L"Help");

	int nWidth = GetSystemMetrics(SM_CXSCREEN);
	int nHeight = GetSystemMetrics(SM_CYSCREEN);
	int buttonWidth = 60;

	HWND mainWin = CreateWindowExW(0, CLASS_NAME, L"Music Finder",
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX, CW_USEDEFAULT,
		CW_USEDEFAULT, nWidth / 2, nHeight / 2, nullptr, hMenuBar, hInstance, nullptr);

	HWND editWin = CreateWindowExW(0, L"EDIT", L"", WS_CHILD | WS_BORDER, nWidth / 8, nHeight / 8, nWidth / 4 - buttonWidth - 10, 25, mainWin,
		nullptr, hInstance, nullptr);
	
	HWND searchBtn = CreateWindowExW(0, L"BUTTON", L"Search!", WS_CHILD | BS_DEFPUSHBUTTON, nWidth * 3 / 8 - buttonWidth,
	                    nHeight / 8, buttonWidth, 25, mainWin, nullptr, hInstance, nullptr);

	ShowWindow(mainWin, SW_SHOWDEFAULT);
	ShowWindow(editWin, SW_SHOWDEFAULT);
	ShowWindow(searchBtn, SW_SHOWDEFAULT);

	MSG msg;
	while (GetMessageW(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return 0;
}
