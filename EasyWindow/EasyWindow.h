#pragma once
#include <Windows.h>
#include <vector>
#include "EventList.h"

namespace EzWnd {

	struct Event {
		UINT16 Trigger = 0x0000;
		void (*Action)() = nullptr;
	};

	class Window {

	public:

		Window();

		int Init();
		void Name(LPCTSTR WindowTitle);
		void Color(COLOR16 color);
		void AddEvent(const Event& NewEvent);

	private:

		struct Wnd_info {

			DWORD WindowOptionalStyle = 0;
			LPCTSTR ClassName = L"Window Class";
			LPCTSTR WindowTitle = L"Default Title";
			DWORD WindowStyle = WS_OVERLAPPEDWINDOW;
			int X = CW_USEDEFAULT, Y = CW_USEDEFAULT;
			int Width = CW_USEDEFAULT, Height = CW_USEDEFAULT;
			HWND WindowParent = NULL;
			HMENU WindowSon = NULL;
			HINSTANCE hInstance;
			LPVOID lParam = NULL;

			int nCmdShow;
			HWND hwnd = {};
			COLOR16 WindowColor = 0x0;
		};

		Wnd_info Wnd_i = {};
		std::vector<Event> EventList = { {WM_DESTROY, DestroyWindowFunction} };

		static LRESULT CALLBACK WindowEvents(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		static void DestroyWindowFunction();


		void SetBackGroundColor();
		static void StaticSetBackGroundColor(HWND hwnd);

	};

}