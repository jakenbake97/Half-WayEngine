#pragma once

#include "Basalt/Exception.h"
#include "Basalt/IWindow.h"

namespace Basalt {
	class String;
}

namespace Basalt::Platform
{
	class BASALT_API Window : public IWindow
	{
	private:
		WindowProperties properties;
		HWND handle;
		bool vSync;
		bool focused = true;

	public:
		class WindowException : public Exception
		{
		private:
			HRESULT hr;
		public:
			WindowException(int line, String file, HRESULT hr);
			String GetException() const override;
			String GetType() const override;
			static String TranslateErrorCode(HRESULT hr);
			HRESULT GetErrorCode() const;
			String GetErrorString() const;
		};
	private:
		class WindowClass
		{
		private:
			static WindowClass wndClass;
			HINSTANCE hInst;

		private:
			WindowClass();
			~WindowClass();
		public:
			static const wchar_t* GetName();
			static HINSTANCE GetInstance();

			WindowClass(const WindowClass&) = delete;
			WindowClass& operator=(const WindowClass&) = delete;
		};
	public:
		Window(const WindowProperties& properties);
		~Window() override;
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		Window(Window&& other) noexcept = delete;
		Window& operator=(Window && other) noexcept = delete;

		void OnUpdate() override;
		unsigned int GetWidth() const override;
		unsigned int GetHeight() const override;
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		
	private:
		static void HandleWindowResize(HWND hWnd, UINT width, UINT height);
		
		static LRESULT WINAPI HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static LRESULT WINAPI HandleMsgAdapter(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static WPARAM MapLeftRightKeys(WPARAM vk, LPARAM lParam);
	};
}

#define BE_WND_EXCEPT(hr) Basalt::Platform::Window::WindowException(__LINE__, __FILE__, hr)
#define BE_WND_LAST_EXCEPT() Basalt::Platform::Window::WindowException(__LINE__, __FILE__, GetLastError())
