#include "EasyWindow.h"

EzWnd::Window::Window() {

	Wnd_i.hInstance = GetModuleHandle(NULL);
	
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	GetStartupInfo(&si);

	if (si.dwFlags & STARTF_USESHOWWINDOW) {
		Wnd_i.nCmdShow = si.wShowWindow;
	}
	else {
		Wnd_i.nCmdShow = SW_SHOWDEFAULT;
	}

}

int EzWnd::Window::Init() {
	
	const wchar_t CLASS_NAME[] = L"Window Class";
	WNDCLASS windowclass = {};

	windowclass.lpfnWndProc = WindowEvents;
	windowclass.hInstance = Wnd_i.hInstance;
	windowclass.lpszClassName = CLASS_NAME;

	RegisterClass(&windowclass);

	HWND hwnd = CreateWindowEx(
		Wnd_i.WindowOptionalStyle,
		Wnd_i.ClassName,
		Wnd_i.WindowTitle,
		Wnd_i.WindowStyle,
		Wnd_i.X, Wnd_i.Y,
		Wnd_i.Width, Wnd_i.Height,
		Wnd_i.WindowParent,
		Wnd_i.WindowSon,
		Wnd_i.hInstance,
		Wnd_i.lParam
	);

	if (hwnd == NULL) {
		return 0;
	}

	SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	ShowWindow(hwnd, Wnd_i.nCmdShow);

	MSG msg = { };

	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

void EzWnd::Window::Config(LPCTSTR WindowTitle) {
	Wnd_i.WindowTitle = WindowTitle;
}

void EzWnd::Window::AddEvent(const Event& NewEvent) {
	EventList.push_back(NewEvent);
}

LRESULT CALLBACK EzWnd::Window::WindowEvents(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	Window* pThis = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

	if (!pThis) {
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	for (int i = 0; i < pThis->EventList.size(); i++) {
		if (uMsg == pThis->EventList[i].Trigger && pThis->EventList[i].Action) {
			pThis->EventList[i].Action(hwnd);
		}
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
