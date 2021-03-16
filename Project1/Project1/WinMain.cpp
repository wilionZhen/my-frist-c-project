#include "window.h"
#include<iostream>
#include<sstream>
using namespace std;

int CALLBACK  WinMain(
	 HINSTANCE hInstance, HINSTANCE hPrevInstance,
	  LPSTR lpCmdLine, int nCmdShow) {
	try
	{
		//注册窗口
		Window wnd(800, 300, "window fix");

		MSG msg;
		BOOL gRegsult;
		while ((gRegsult = GetMessage(&msg, nullptr, 0, 0)) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (wnd.keboard.KeyIsPressed(VK_SPACE)) {
				MessageBox(nullptr, "按下按键", "alt", MB_OK | MB_ICONEXCLAMATION);
			}
			while (!wnd.mouse.IsEmpty())
			{
				const auto e= wnd.mouse.Read();
				if (e->GetType() == Mouse::Event::Type::Move) {
					std::ostringstream oss;
					oss << "Mouse Position:(" << e->GetPosX() << "," << e->GetPosY();
					wnd.SetTitle(oss.str());
				}
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