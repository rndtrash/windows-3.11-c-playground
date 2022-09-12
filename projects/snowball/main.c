#include <windows.h>

#include "snowball.h"

long FAR PASCAL _export WndProc(HWND, UINT, UINT, LONG);

HANDLE g_hInstance;

int PASCAL WinMain(HANDLE hInstance, HANDLE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	static char szAppName[] = "Hamptre";
	HWND hWnd;
	MSG msg;
	WNDCLASS wndClass;

	if (!hPrevInstance)
	{
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc = WndProc;
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 0;
		wndClass.hInstance = hInstance;
		wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndClass.hbrBackground = GetStockObject(WHITE_BRUSH);
		wndClass.lpszMenuName = NULL;
		wndClass.lpszClassName = szAppName;

		RegisterClass(&wndClass);
	}

	g_hInstance = hInstance;

	// god gracious
	hWnd = CreateWindow(szAppName, "Hamptrer :D", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

long FAR PASCAL _export WndProc(HWND hWnd, UINT message, UINT wParam, LONG lParam)
{
	static HBITMAP hRotundSpecimens;

	HDC hdc, hdcMem;
	PAINTSTRUCT ps;
	RECT rect;
	HGDIOBJ hOldBitmap;
	BITMAP rotundSpecimens;

	switch (message)
	{
	case WM_CREATE:
		hRotundSpecimens = LoadBitmap(g_hInstance, "hampterers");

		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		hdcMem = CreateCompatibleDC(hdc);
		hOldBitmap = SelectObject(hdcMem, hRotundSpecimens);

		rotundSpecimens;
		GetObject(hRotundSpecimens, sizeof(rotundSpecimens), &rotundSpecimens);
		BitBlt(hdc, 0, 0, rotundSpecimens.bmWidth, rotundSpecimens.bmHeight, hdcMem, 0, 0, SRCCOPY);

		SelectObject(hdcMem, hOldBitmap);
		DeleteDC(hdcMem);

		GetClientRect(hWnd, &rect);
		DrawText(hdc, "hamptre", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		EndPaint(hWnd, &ps);

		return 0;
	case WM_DESTROY:
		// clean up!
		DeleteObject(hRotundSpecimens);
		PostQuitMessage(0);

		return 0;
	default:
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
