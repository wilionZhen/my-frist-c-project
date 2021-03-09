#include "window.h"
#include<iostream>
#include<sstream>
using namespace std;
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam) {
	static string s;
		ostringstream oss ;

	switch (msg)
	{
	case WM_CLOSE:
			PostQuitMessage(69);
			break;
	case WM_KEYDOWN:
		
		break;
	case WM_CHAR:
		s.push_back((char)wParam);
		SetWindowText(hwnd, s.c_str());
	case WM_LBUTTONDOWN:
		const POINTS pt = MAKEPOINTS(lParam);
		oss << pt.x << "," << pt.y ;
		SetWindowText(hwnd, oss.str().c_str());
		break;
	default:
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int creatWindow(HINSTANCE hInstance) {
	const auto pClassName = "MyClassName";
	WNDCLASSEXA wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hIcon = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = pClassName;
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);
	HWND hwnd = CreateWindowEx(0, pClassName, "hello",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		0, 0, 500, 500,
		nullptr, nullptr, hInstance, nullptr
	);
	MSG msg;
	ShowWindow(hwnd, SW_SHOW);
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (gResult == -1)
	{
		return -1;
	}
	else
	{
		return msg.wParam;
	}
}
int CALLBACK  WinMain(
	 HINSTANCE hInstance, HINSTANCE hPrevInstance,
	  LPSTR lpCmdLine, int nCmdShow) {
	try
	{
		//注册窗口
		Window wnd(800, 300, "window fix");
		//Window wnd2(300, 600, "window fi2");

		MSG msg;
		BOOL gRegsult;
		while ((gRegsult = GetMessage(&msg, nullptr, 0, 0)) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (wnd.keboard.KeyIsPressed(VK_MENU)) {
				MessageBox(nullptr, "按下按键", "alt", MB_OK | MB_ICONEXCLAMATION);
			}
		}
		if (gRegsult == -1) {
			return -1;
		}
		return msg.wParam;
	}
	catch (const ChiliException& e)
	{
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
}