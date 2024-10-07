#include <iostream>
#include <EasyWindow.h>

void function() {
	PAINTSTRUCT ps;
}

int main() {

	EzWnd::Window window;

	window.Name(L"Azul");

	EzWnd::Event MyEvent;
	MyEvent.Trigger = WM_PAINT;
	MyEvent.Action = function;

	window.AddEvent(MyEvent);

	window.Init();

	return 0;
}