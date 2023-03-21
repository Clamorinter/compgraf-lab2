#include "WinRender.h"

WinRender::WinRender(int x, int y)
{
	initwindow(x, y, "Figures");
	setbkcolor(15);
	bitmap = (void*)malloc(imagesize(0, 0, x, y));
	xscreen = x;
	yscreen = y;
	setvisualpage(0);
	setcolor(0);
}
WinRender::~WinRender()
{
	closegraph();
	for (int i = numOfElements-1; i >= 0; i--)
	{
		delete figures.arr[i];
		figures.decrease();
	}
}

void WinRender::doAMouse()
{
	if (mouseProcessing())
	{
		if (createflag && !moveflag && !dragflag)
		{
			createmode();
		}
		if (!createflag && !moveflag && !dragflag)
		{
			choosing();
		}
		if (!createflag && !moveflag && chooseflag && choosed != -1)
		{
			dragmode();
		}
		if (!createflag && !dragflag && chooseflag && choosed != -1)
		{
			movemode();
		}
	}
}
void WinRender::doAKey()
{
	if (kbhit())
	{
		key = (char)getch();
		switch (key)
		{
		case 'n':
			if (!createflag && !moveflag && !dragflag)
			{
				createkey();
			}
			break;
		case 'w':
		case 'a':
		case 's':
		case 'd':
			if (chooseflag && !createflag && !moveflag && !dragflag)
			{
				movekey();
			}
			break;
		case 'q':
		case 'e':
			if (chooseflag && !createflag && !moveflag && !dragflag)
			{
				rotatekey();
			}
			break;
		case '-':
		case '=':
			if (chooseflag && !createflag && !moveflag && !dragflag)
			{
				zoomkey();
			}
			break;
		case 'r':
		case 'f':
			if (chooseflag && !createflag && !moveflag && !dragflag)
			{
				choosekey();
			}
			break;
		case '`':
			if (!createflag && !moveflag && !dragflag)
			{
				chooseallkey();
			}
			break;
		case '\\':
			if (chooseflag && !createflag && !moveflag && !dragflag)
			{
				deletekey();
			}
			break;
		case '0':
			exitkey();
		}
	}
}

void WinRender::doAChange()
{
	setactivepage(1);

	bgiout << mousex() << " " << mousey();
	outstreamxy(10, 10);
	//some activities

	getimage(0, 0, xscreen, yscreen, bitmap);
	clearviewport();
	setactivepage(0);
	putimage(0, 0, bitmap, COPY_PUT);
}

void WinRender::createmode()
{
	std::cout << "It's createmode!!" << std::endl;
}
void WinRender::movemode()
{
	std::cout << "It's movemode!!" << std::endl;
}
void WinRender::dragmode()
{
	std::cout << "It's dragmode!!" << std::endl;
}
void WinRender::choosing()
{
	std::cout << "It's choosing!!" << std::endl;
}
bool WinRender::mouseProcessing()
{
	int start_x = x;
	int start_y = y;
	if (ismouseclick(WM_LBUTTONDOWN))
	{
		getmouseclick(WM_LBUTTONDOWN, x, y);
		clickflag = true;
		return true;
	}
	if (ismouseclick(WM_LBUTTONUP))
	{
		clearmouseclick(WM_LBUTTONUP);
		clickflag = false;
		return false;
	}
	if (ismouseclick(WM_MOUSEMOVE) && clickflag)
	{
		getmouseclick(WM_MOUSEMOVE, x, y);
		if (start_x != x && start_y != y)
		{
			return true;
		}
	}
	return false;
}

void WinRender::movekey()
{
	std::cout << "It's movekey!!" << std::endl;
}
void WinRender::createkey()
{
	std::cout << "It's createkey!!" << std::endl;
}
void WinRender::choosekey()
{
	std::cout << "It's choosekey!!" << std::endl;
}
void WinRender::chooseallkey()
{
	std::cout << "It's chooseallkey!!" << std::endl;
}
void WinRender::rotatekey()
{
	std::cout << "It's rotatekey!!" << std::endl;
}
void WinRender::zoomkey()
{
	std::cout << "It's zoomkey!!" << std::endl;
}
void WinRender::deletekey()
{
	std::cout << "It's deletekey!!" << std::endl;
}
void WinRender::exitkey()
{
	exitflag = true;
}

void WinRender::menu()
{
	std::cout << "It's menu!!" << std::endl;
}
bool WinRender::isExit()
{
	return exitflag;
}

