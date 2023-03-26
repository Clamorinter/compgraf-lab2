//#include <Windows.h>
#include "WinRender.h"
#include <iostream>

#define X_SCREEN 1200
#define Y_SCREEN 800


int main(void)
{

	WinRender graphscreen(X_SCREEN, Y_SCREEN);

	//HWND hwnd = GetConsoleWindow();
	//ShowWindow(hwnd, SW_SHOW);

	while (!graphscreen.isExit())
	{
		delay(18);

		graphscreen.doAMouse();

		graphscreen.doAKey();

		graphscreen.doAChange();
	}
}