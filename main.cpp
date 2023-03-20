#include <Windows.h>
#include "figure.h"
#include <iostream>
int main(void)
{
	void* bitmap = nullptr;
	HWND hwnd;
	initwindow(600, 600, "Lines");
	hwnd = FindWindowA(0, "Lines");
	bitmap = (void*)malloc(imagesize(0, 0, 600, 600));
	setvisualpage(0);
	while (1)
	{
		Sleep(1);
		setactivepage(1);
		std::cout << "Page 1" << std::endl;
		line(100, 100, 400, 400);
		line(100, 200, 200, 100);
		line(400, 100, 100, 400);
		getimage(0, 0, 600, 600, bitmap);
		clearviewport();
		setactivepage(0);
		std::cout << "Page 0" << std::endl;
		putimage(0, 0, bitmap, COPY_PUT);
	}
}