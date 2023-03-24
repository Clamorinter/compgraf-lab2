#include "WinRender.h"

#include <iostream>

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
	else if (dragflag || moveflag)
	{
		dragflag = false;
		moveflag = false;
		figures.arr[choosed]->setColor(9);
	}
}
void WinRender::doAKey()
{
	if (kbhit())
	{
		key = (char)getch();
		while (kbhit())
		{
			getch();
		}
		switch (key)
		{
		case 'n':
			if (!createflag && !moveflag && !dragflag)
			{
				createkey();
			}
			break;
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			if (createflag)
			{
				counter1 = key - '0';
				counter2 = 0;
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
				chooseallkey(); //need work
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
	//some activities start
	setcolor(0);
	bgiout << mousex() << " " << mousey();
	outstreamxy(10, 10);

	for (int i = 0; i < numOfElements; i++)
	{
		figures.arr[i]->draw();
	}
	//some activities end
	getimage(0, 0, xscreen, yscreen, bitmap);
	clearviewport();
	setactivepage(0);
	putimage(0, 0, bitmap, COPY_PUT);
}

void WinRender::createmode()
{
	if (counter1 == 1)
	{
		figures.append(new Dot(x, y));
		numOfElements++;
		createflag = false;
		return;
	} 
	if (counter1 == 2)
	{
		if (counter2 == 0)
		{
			figures.append(new Line);
			past_x = 0;
			past_y = 0;
		}
		if (past_x != x || past_y != y)
		{
			figures.arr[numOfElements]->moveFragment(x, y, counter2);
			past_x = x;
			past_y = y;
			counter2++;
		}
		if (counter2 == counter1)
		{
			numOfElements++;
			createflag = false;
			return;
		}
	}
	if (counter1 > 2 && counter1 <= 9)
	{
		if (counter2 == 0)
		{
			figures.append(new Polygone(counter1));
			past_x = 0;
			past_y = 0;
		}
		if (past_x != x || past_y != y)
		{
			figures.arr[numOfElements]->moveFragment(x, y, counter2);
			past_x = x;
			past_y = y;
			counter2++;
		}
		if (counter2 == counter1)
		{
			numOfElements++;
			createflag = false;
			return;
		}
	}
}
void WinRender::movemode()
{
	const int error = 10;
	if (!moveflag)
	{
		for (int i = x - error; i <= x + error; i++)
		{
			for (int j = y - error; j <= y + error; j++)
			{
				if (figures.arr[choosed]->isOnFigure(i, j))
				{
					moveflag = true;
					past_x = x;
					past_y = y;
					figures.arr[choosed]->setColor(1);
					break;
				}
			}
			if (moveflag)
			{
				break;
			}
		}
	}
	else
	{
		figures.arr[choosed]->move(x - past_x, y - past_y);
		past_x = x;
		past_y = y;
	}
}
void WinRender::dragmode() // search process needs optimization
{
	const int error = 10;
	if (!dragflag)
	{
		for (int i = x - error; i <= x + error; i++)
		{
			for (int j = y - error; j <= y + error; j++)
			{
				counter2 = figures.arr[choosed]->isOnFragment(i, j);
				if (counter2 != -1)
				{
					dragflag = true;
					counter1 = counter2;
					figures.arr[choosed]->setColor(12);
					past_x = x;
					past_y = y;
					if (counter2 < figures.arr[choosed]->getNumOfAngles()) break;
				}
			}
			if (counter2 < figures.arr[choosed]->getNumOfAngles() && counter2 != -1) break;
		}
	}
	else
	{
		figures.arr[choosed]->moveFragment(x-past_x, y-past_y, counter1);
		past_x = x;
		past_y = y;
	}
}
bool WinRender::isDotOnFigure()
{
	const int error = 10;

	for (int n = 0; n < numOfElements; n++)
	{
		for (int i = x - error; i <= x + error; i++)
		{
			for (int j = y - error; j <= y + error; j++)
			{
				if (figures.arr[n]->isOnFigure(i, j))
				{
					if (chooseflag)
					{
						counter1 = choosed;
					}
					choosed = n;
					return true;
				}
			}
		}
	}
	return false;
}
void WinRender::choosing()
{
	if (isDotOnFigure())
	{
		if (chooseflag)
		{
			if (choosed != counter1)
			{
				figures.arr[counter1]->setColor(0);
			}
		}
		chooseflag = true;
		figures.arr[choosed]->setColor(9);
	}

}
bool WinRender::mouseProcessing()
{
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
	if (clickflag)
	{
		x = mousex();
		y = mousey();
		return true;
	}
	return false;
}

void WinRender::movekey() // delay problem
{
	switch (key)
	{
	case 'w':
		figures.arr[choosed]->move(0, -5);
		break;
	case 's':
		figures.arr[choosed]->move(0, 5);
		break;
	case 'a':
		figures.arr[choosed]->move(-5, 0);
		break;
	case 'd':
		figures.arr[choosed]->move(5, 0);
		break;
	}
}
void WinRender::createkey()
{
	createflag = true;
}
void WinRender::choosekey()
{
	switch (key)
	{
	case 'r':
		if (choosed != numOfElements - 1)
		{
			figures.arr[choosed++]->setColor(0);
			figures.arr[choosed]->setColor(9);
		}
		break;
	case 'f':
		if (choosed != 0)
		{
			figures.arr[choosed--]->setColor(0);
			figures.arr[choosed]->setColor(9);
		}
		break;
	}
}
void WinRender::chooseallkey()
{

}
void WinRender::rotatekey()
{
	int centerx = figures.arr[choosed]->findCenter('x');
	int centery = figures.arr[choosed]->findCenter('y');
	switch (key)
	{
	case 'q':
		figures.arr[choosed]->rotate((float)0.05, centerx, centery);
		break;
	case 'e':
		figures.arr[choosed]->rotate((float)-0.05, centerx, centery);
	}
}
void WinRender::zoomkey()
{
	int centerx = figures.arr[choosed]->findCenter('x');
	int centery = figures.arr[choosed]->findCenter('y');
	switch (key)
	{
	case '=':

		figures.arr[choosed]->zoom((float)1.10, centerx, centery);
		break;
	case '-':
		figures.arr[choosed]->zoom((float)(1.0 / 1.10), centerx, centery);
		break;
	}
}
void WinRender::deletekey()
{
	delete figures.arr[choosed];
	for (int i = choosed; i < numOfElements - 1; i++)
	{
		figures.arr[i] = figures.arr[i + 1];
	}
	figures.decrease();
	numOfElements--;
	chooseflag = false;
}
void WinRender::exitkey()
{
	exitflag = true;
}

void WinRender::menu()
{

}
bool WinRender::isExit()
{
	return exitflag;
}

