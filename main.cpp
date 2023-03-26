#include <Windows.h>
#include "WinRender.h"

#define X_SCREEN 1200
#define Y_SCREEN 800


int main(void)
{
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_HIDE);

	WinRender graphscreen(X_SCREEN, Y_SCREEN);

	while (!graphscreen.isExit())
	{
		delay(18);

		graphscreen.doAMouse();

		graphscreen.doAKey();

		graphscreen.doAChange();
	}

	ShowWindow(hwnd, SW_SHOW);
	return 0;
}