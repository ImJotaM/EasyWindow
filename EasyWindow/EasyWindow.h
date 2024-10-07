#pragma once
#include <Windows.h>
#include <vector>
#include "EventList.h"

namespace EzWnd {

	struct Event {
		UINT16 Trigger = 0x0000;
		void (*Action)(HWND) = nullptr;
	};

	class Window {

	public:

		Window();

		int Init();
		void Config(LPCTSTR WindowTitle);
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

		};

		Wnd_info Wnd_i = {};
		std::vector<Event> EventList;

		static LRESULT CALLBACK WindowEvents(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	};

}