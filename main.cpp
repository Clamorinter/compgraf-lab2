#include <Windows.h>
#include "figure.h"

int main(void)
{
	HWND Buffer_window, Active_window;
	HDC source, active, compatible;
	PAINTSTRUCT ps;
	HBITMAP hbmactive;
	initwindow(600, 600, "Lines"); // поменять местами
	Active_window = FindWindowA(0, "Lines");
	active = GetDC(Active_window);
	initwindow(600, 600, "Buffer");
	Buffer_window = FindWindowA(0, "Buffer");
	source = GetDC(Buffer_window);

	ShowWindow(Buffer_window, SW_HIDE);
	//compatible = CreateCompatibleDC(active);
	//hbmactive = CreateCompatibleBitmap(compatible, 600, 600);
	//HGDIOBJ hype = SelectObject(compatible, hbmactive);
	//cleardevice();
	//PrintWindow(Buffer_window, compatible, PW_CLIENTONLY);
	//SelectObject(compatible, hype);

	SetWindowLong(Buffer_window, GWL_EXSTYLE, GetWindowLong(Buffer_window, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(Buffer_window, 0, 1, LWA_ALPHA);
	while (1)
	{
		Sleep(37);
		cleardevice();
		line(100, 100, 400, 400);
		line(100, 200, 200, 100);
		line(400, 100, 100, 400);
		ShowWindow(Buffer_window, SW_SHOW);
		BitBlt(active, 0, 0, 600, 600, source, 0, 0, SRCCOPY);
		ShowWindow(Buffer_window, SW_HIDE);
	}
}