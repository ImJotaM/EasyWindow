#include <iostream>
#include <EasyWindow.h>

void function(HWND hwnd) {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

	EndPaint(hwnd, &ps);
}

int main() {

	EzWnd::Window window;

	window.Config(L"Azul");

	EzWnd::Event MyEvent;
	MyEvent.Trigger = WM_PAINT;
	MyEvent.Action = function;

	window.AddEvent(MyEvent);

	window.Init();

	return 0;
}