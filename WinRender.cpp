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
	if (mouseProcessing() && !menuflag)
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
		counter1 = 0;
		counter2 = 0;
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
			if (!createflag && !moveflag && !dragflag && !menuflag)
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
			if (chooseflag && !createflag && !moveflag && !dragflag && !menuflag)
			{
				movekey();
			}
			break;
		case 'q':
		case 'e':
			if (chooseflag && !createflag && !moveflag && !dragflag && !menuflag)
			{
				rotatekey();
			}
			break;
		case '-':
		case '=':
			if (chooseflag && !createflag && !moveflag && !dragflag && !menuflag)
			{
				zoomkey();
			}
			break;
		case 'r':
		case 'f':
			if (chooseflag && !createflag && !moveflag && !dragflag && !menuflag)
			{
				choosekey();
			}
			break;
		case '`':
			if (!createflag && !moveflag && !dragflag && !menuflag)
			{
				chooseallkey(); //need work
			}
			break;
		case '\\':
			if (chooseflag && !createflag && !moveflag && !dragflag && !menuflag)
			{
				deletekey();
			}
			break;
		case 'c':
			if (!createflag && !moveflag && !dragflag)
			{
				if (menuflag)
				{
					menuflag = false;
				}
				else
				{
					menuflag = true;
				}
			}
			break;
		case '0':
			exitkey();
			break;
		}
	}
}

void WinRender::doAChange()
{
	setactivepage(1);
	//some activities start
	setcolor(0);
	menu();
	if (!menuflag)
	{
		for (int i = 0; i < numOfElements; i++)
		{
			figures.arr[i]->draw();
		}
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
			counter2 = 0;
			counter1 = 0;
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
			counter1 = 0;
			counter2 = 0;
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
void WinRender::dragmode()
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
					else
					{
						counter1 = 0;
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
				if (counter1 != -1)
				{
					figures.arr[counter1]->setColor(0);
				}
				else
				{
					for (int i = 0; i < numOfElements; i++)
					{
						figures.arr[i]->setColor(0);
					}
				}
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

void WinRender::movekey() 
{
	switch (key)
	{
	case 'w':
		if (choosed != -1)
		{
			figures.arr[choosed]->move(0, -5);
		}
		else
		{
			for (int i = 0; i < numOfElements; i++)
			{
				figures.arr[i]->move(0, -5);
			}
		}
		break;
	case 's':
		if (choosed != -1)
		{
			figures.arr[choosed]->move(0, 5);
		}
		else
		{
			for (int i = 0; i < numOfElements; i++)
			{
				figures.arr[i]->move(0, 5);
			}
		}
		break;
	case 'a':
		if (choosed != -1)
		{
			figures.arr[choosed]->move(-5, 0);
		}
		else
		{
			for (int i = 0; i < numOfElements; i++)
			{
				figures.arr[i]->move(-5, 0);
			}
		}
		break;
	case 'd':
		if (choosed != -1)
		{
			figures.arr[choosed]->move(5, 0);
		}
		else
		{
			for (int i = 0; i < numOfElements; i++)
			{
				figures.arr[i]->move(5, 0);
			}
		}
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
			if (choosed != -1)
			{
				figures.arr[choosed++]->setColor(0);
			}
			else
			{
				choosed = numOfElements - 1;
				for (int i = 0; i < numOfElements; i++)
				{
					figures.arr[i]->setColor(0);
				}
			}
			figures.arr[choosed]->setColor(9);
		}
		break;
	case 'f':
		if (choosed != 0)
		{
			if (choosed != -1)
			{
				figures.arr[choosed--]->setColor(0);
			}
			else
			{
				choosed = 0;
				for (int i = 0; i < numOfElements; i++)
				{
					figures.arr[i]->setColor(0);
				}
			}
			figures.arr[choosed]->setColor(9);
		}
		break;
	}
}
void WinRender::chooseallkey()
{
	if (numOfElements >= 2)
	{
		chooseflag = true;
		choosed = -1;
		for (int i = 0; i < numOfElements; i++)
		{
			figures.arr[i]->setColor(9);
		}
	}
}
void WinRender::rotatekey()
{
	int centerx;
	int centery;
	switch (key)
	{
	case 'q':
		if (choosed != -1)
		{
			centerx = figures.arr[choosed]->findCenter('x');
			centery = figures.arr[choosed]->findCenter('y');
			figures.arr[choosed]->rotate((float)0.05, centerx, centery);
		}
		else
		{
			centerx = mousex();
			centery = mousey();
			for (int i = 0; i < numOfElements; i++)
			{
				figures.arr[i]->rotate((float)0.05, centerx, centery);
			}
		}
		break;
	case 'e':
		if (choosed != -1)
		{
			centerx = figures.arr[choosed]->findCenter('x');
			centery = figures.arr[choosed]->findCenter('y');
			figures.arr[choosed]->rotate((float)-0.05, centerx, centery);
		}
		else
		{
			centerx = mousex();
			centery = mousey();
			for (int i = 0; i < numOfElements; i++)
			{
				figures.arr[i]->rotate((float)-0.05, centerx, centery);
			}
		}
	}
}
void WinRender::zoomkey()
{
	int centerx;
	int centery;
	switch (key)
	{
	case '=':
		if (choosed != -1)
		{
			centerx = figures.arr[choosed]->findCenter('x');
			centery = figures.arr[choosed]->findCenter('y');
			figures.arr[choosed]->zoom((float)1.10, centerx, centery);
		}
		else
		{
			centerx = mousex();
			centery = mousey();
			for (int i = 0; i < numOfElements; i++)
			{
				figures.arr[i]->zoom((float)1.10, centerx, centery);
			}
		}
		break;
	case '-':
		if (choosed != -1)
		{
			centerx = figures.arr[choosed]->findCenter('x');
			centery = figures.arr[choosed]->findCenter('y');
			figures.arr[choosed]->zoom((float)(1.0 / 1.10), centerx, centery);
		}
		else
		{
			bool zoomminflag = true;
			int zoommin = 100;
			int xcheck, ycheck;
			for (int i = 0; i < numOfElements; i++)
			{
				for (int j = 0; j < figures.arr[i]->getNumOfAngles() - 1; j++)
				{
					xcheck = figures.arr[i]->getX(j);
					ycheck = figures.arr[i]->getY(j);
					xcheck = abs(xcheck - figures.arr[i]->getX(1+j));
					ycheck = abs(ycheck - figures.arr[i]->getY(1+ j));
					if (xcheck < zoommin && ycheck < zoommin)
					{
						zoomminflag = false;
					}
				}
			}
			if (zoomminflag)
			{
				centerx = mousex();
				centery = mousey();
				for (int i = 0; i < numOfElements; i++)
				{
					figures.arr[i]->zoom((float)(1.0 / 1.10), centerx, centery);
				}
			}
		}
		break;
	}
}
void WinRender::deletekey()
{
	if (choosed != -1)
	{
		delete figures.arr[choosed];
		for (int i = choosed; i < numOfElements - 1; i++)
		{
			figures.arr[i] = figures.arr[i + 1];
		}
		figures.decrease();
		numOfElements--;
	}
	else
	{
		for (int i = numOfElements - 1; i >= 0; i--)
		{
			delete figures.arr[i];
			figures.decrease();
		}
		numOfElements = 0;
	}
	chooseflag = false;
}
void WinRender::exitkey()
{
	exitflag = true;
}

void WinRender::menu()
{
	if (!menuflag)
	{
		bgiout << mousex() << " " << mousey();
		outstreamxy(10, 10);
		bgiout << "Mouse process: ";
		if (createflag)
		{
			bgiout << "Creating figure.";
		}
		else if (dragflag)
		{
			bgiout << "Dragging the fragment of figure.";
		}
		else if (moveflag)
		{
			bgiout << "Moving the figure.";
		}
		else
		{
			bgiout << "None.";
		}
		outstreamxy(10, 30);
		bgiout << "Key process: ";
		switch (key)
		{
		case 'w':
		case 'a':
		case 's':
		case 'd':
			if (chooseflag && !createflag && !moveflag && !dragflag)
			{
				bgiout << "Moving the figure.";
			}
			key = ' ';
			break;
		case 'q':
		case 'e':
			if (chooseflag && !createflag && !moveflag && !dragflag)
			{
				bgiout << "Rotation of the figure.";
			}
			key = ' ';
			break;
		case '-':
		case '=':
			if (chooseflag && !createflag && !moveflag && !dragflag)
			{
				bgiout << "Zooming the figure.";
			}
			key = ' ';
			break;
		default:
			bgiout << "None.";
			break;
		}
		outstreamxy(10, 50);
		bgiout << "Press 'c' to see the controls.";
		outstreamxy(990, 10);
	}
	else
	{
		bgiout << "The keys of program:" << std::endl << std::endl;
		bgiout << "n - enter in create mode" << std::endl;
		bgiout << "1-9 - choose a number of angles" << std::endl;
		bgiout << "r/f - select next/previous figure" << std::endl;
		bgiout << "w/a/s/d - move selected figure" << std::endl;
		bgiout << "q/e - rotate selected figure" << std::endl;
		bgiout << "-/= - zoom selected figure" << std::endl;
		bgiout << "\\ - delete selected figure" << std::endl;
		bgiout << "` - choose all figures" << std::endl;
		bgiout << "c - exit controls" << std::endl;
		bgiout << "0 - exit the program" << std::endl;
		outstreamxy(500, 200);
	}
}

bool WinRender::isExit()
{
	return exitflag;
}

