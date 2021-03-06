#pragma once
#include "ChiliWin.h"
#include "ChiliException.h"
#include "Keyboard.h"
#include "Mouse.h"

using namespace std;

class Window
{
public:
	class Exception :public ChiliException {
	public:
		Exception(int line, const char*file,HRESULT hr) noexcept;
		char const* what()const noexcept override;
		virtual const char* GetType()const noexcept override;
		static std::string TranslateErrorCode(HRESULT hr)noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
	private:
		HRESULT hr;
	};
private:
	// singleton manages registration/cleanup of window class
	class WindowClass
	{
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr const char* wndClassName = "Chili Direct3D Engine Window";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};
public:
	Window(int width, int height, const char* name);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	void SetTitle(const std::string& title);
private:
	
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
public:
	Keyboard keboard;
	Mouse mouse;
private:
	bool cursorEnabled = true;
	int width;
	int height;
	HWND hWnd;
};

#define CHWWD_EXCEPT(hr) Window::Exception(__LINE__,__FILE__,hr)
#define CHWWD_LAST_EXEP() Window::Exception(__LINE__,__FILE__,GetLastError())