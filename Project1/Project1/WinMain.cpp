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
		//test
		MSG msg;
		BOOL gRegsult;
		while ((gRegsult = GetMessage(&msg, nullptr, 0, 0)) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			
			while (!wnd.mouse.IsEmpty())
			{
				const auto e= wnd.mouse.Read();
				switch (e->GetType())
				{
				case Mouse::Event::Type::Leave:
					wnd.SetTitle("在窗口外");
					break;
				case Mouse::Event::Type::Move: {
					std::ostringstream oss;
					oss << "在窗口内移动:(" << wnd.mouse.GetPosX() << "," << wnd.mouse.GetPosY() << ")";
					wnd.SetTitle(oss.str());

					break; }
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