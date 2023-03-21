//#include <Windows.h>
#include "figure.h"
#include <iostream>

#define X_SCREEN 1200
#define Y_SCREEN 800

bool mouseprocessing(int& x, int& y, bool& clicked);

int main(void)
{
	dynarr<Figure**> figures;
	int x, y;
	char c;


	bool clickflag = false;
	bool exitflag = false;
	bool createflag = false;
	bool moveflag = false;
	bool changeflag = false;

	initwindow(X_SCREEN, Y_SCREEN, "Lines");
	setbkcolor(15);
	void* bitmap = (void*)malloc(imagesize(0, 0, X_SCREEN, Y_SCREEN));
	setvisualpage(0);
	setcolor(0);

	//HWND hwnd = GetConsoleWindow();
	//ShowWindow(hwnd, SW_SHOW);

	while (1)
	{
		delay(17);

		if (mouseprocessing(x, y, clickflag)) //working probably how I need
		{
			std::cout << x << " " << y << std::endl; 
		}

		if (kbhit())
		{
			c = (char)getch();
			std::cout << c << std::endl;
		}

		setactivepage(1);

		bgiout << mousex() << " " << mousey();
		outstreamxy(10, 10);

		getimage(0, 0, X_SCREEN, Y_SCREEN, bitmap);
		clearviewport();
		setactivepage(0);

		putimage(0, 0, bitmap, COPY_PUT);
	}
}

bool mouseprocessing(int& x, int& y, bool& clicked)
{
	int start_x = x;
	int start_y = y;
	if (ismouseclick(WM_LBUTTONDOWN))
	{
		getmouseclick(WM_LBUTTONDOWN, x, y);
		clicked = true;
		return true;
	}
	if (ismouseclick(WM_LBUTTONUP))
	{
		clearmouseclick(WM_LBUTTONUP);
		clicked = false;
		return false;
	}
	if (ismouseclick(WM_MOUSEMOVE) && clicked)
	{
		getmouseclick(WM_MOUSEMOVE, x, y);
		if (start_x != x && start_y != y)
		{
			return true;
		}
	}
	return false;
}