#include "figure.h"

// Dot
void Dot::draw()
{
	putpixel(x, y, color);
}
void Dot::rotate(float angle) {}
void Dot::zoom(float multiplier) {}
void Dot::move(int dx, int dy) {
	this->x += dx;
	this->y += dy;
}
void Dot::moveFragment(int dx, int dy, int countOfFragment) {}
void Dot::setColor(int color)
{
	this->color = color;
}
bool Dot::isOnFigure(int x, int y)
{
	for (int ix = x - ERROR_OF_POINTER; ix <= x + ERROR_OF_POINTER; ix++)
		for (int iy = y - ERROR_OF_POINTER; iy <= y + ERROR_OF_POINTER; iy++)
		{
			if (this->x == ix && this->y == iy)
			{
				return true;
			}
		}
}
int Dot::isOnFragment(int x, int y)
{
	return '\0';
}
char Dot::figureName()
{
	return 'D';
}
int Dot::getX(int numberOfDot = 0)
{
	if (numberOfDot == 0)
	{
		return x;
	}
	return 0;
}
int Dot::getY(int numberOfDot = 0)
{
	if (numberOfDot == 0)
	{
		return y;
	}
	return 0;
}
int Dot::getNumOfAngles()
{
	return this->numOfAngles;
}
 // Line
void Line::draw()
{
	setcolor(color);
	line(Dots.arr[0]->getX(), Dots.arr[0]->getY(), Dots.arr[1]->getX(), Dots.arr[1]->getY());
}
void Line::rotate(float angle)
{
	int x1 = Dots.arr[0]->getX();
	int y1 = Dots.arr[0]->getY();
	int x2 = Dots.arr[1]->getX();
	int y2 = Dots.arr[1]->getY();
	Dot center((int)round((float)(x1 + x2) / 2.0), (int)round((float)(y1 + y2) / 2.0));
	move(-center.getX(), -center.getY());
	int new_x1 = (int)round((float)x1 * cos(angle)) + (int)round((float)y1 * sin(angle));
	int new_y1 = -(int)round((float)x1 * sin(angle)) + (int)round((float)y1 * cos(angle));
	int new_x2 = (int)round((float)x2 * cos(angle)) + (int)round((float)y2 * sin(angle));
	int new_y2 = -(int)round((float)x2* sin(angle)) + (int)round((float)y2 * cos(angle));
	moveFragment(new_x1 - x1, new_y1 - y1, 0);
	moveFragment(new_x2 - x2, new_y2 - y2, 1);
	move(center.getX(), center.getY());
}
void Line::zoom(float multiplier)
{
	int x1 = Dots.arr[0]->getX();
	int y1 = Dots.arr[0]->getY();
	int x2 = Dots.arr[1]->getX();
	int y2 = Dots.arr[1]->getY();
	
	Dot center((int)round((float)(x1 + x2) / 2.0), (int)round((float)(y1 + y2) / 2.0));
	move(-center.getX(), -center.getY());
	int new_x1 = (int)round((float)x1 * multiplier);
	int new_y1 = (int)round((float)y1 * multiplier);
	int new_x2 = (int)round((float)x2 * multiplier);
	int new_y2 = (int)round((float)y2 * multiplier);
	if (multiplier < 1.0)
	{
		float rad = atan((float)abs(y2-y1) / (float)abs(x2-x1));
		rotate(0.78539 - rad);
		if (abs(new_x1 - x1) <= 1 || abs(new_y1 - y1) <= 1 || abs(new_x2 - x2) <= 1 || abs(new_y2 - y2) <= 1)
		{
			new_x1 = x1;
			new_y1 = y1;
			new_x2 = x2;
			new_y2 = y2;
			
		}
		rotate(rad - 0.78539);
	}
	moveFragment(new_x1 - x1, new_y1 - y1, 0);
	moveFragment(new_x2 - x2, new_y2 - y2, 1);
	move(center.getX(), center.getY());
}
void Line::move(int dx, int dy)
{
	for (int i = 0; i < 2; i++)
	{
		Dots.arr[i]->move(dx, dy);
	}
}
void Line::moveFragment(int dx, int dy, int numberOfFragment)
{
	Dots.arr[numberOfFragment]->move(dx, dy);
}
void Line::setColor(int color)
{
	this->color = color;
}
bool Line::isOnFigure(int x, int y)
{
	int xx;
	int yy;
	int x1 = Dots.arr[0]->getX();
	int y1 = Dots.arr[0]->getY();
	int x2 = Dots.arr[1]->getX();
	int y2 = Dots.arr[1]->getY();
	bool ends;
	for (int i = x - ERROR_OF_POINTER; i <= x + ERROR_OF_POINTER; i++)
	{
		for (int j = y - ERROR_OF_POINTER; j <= y + ERROR_OF_POINTER; j++)
		{
			xx = (i - x1) * (y2 - y1);
			yy = (j - y1) * (x2 - x1);
			ends = true;
			if (abs(xx - yy) <= abs(y2 - y1 + x2 - x1) || abs(xx - yy) <= abs(y2 - y1 - x2 + x1))
			{
				if (x2 - x1 > ERROR_OF_POINTER)
				{
					if (x < x1 || x > x2)
						ends = false;
				}
				else if (x1 - x2 > ERROR_OF_POINTER)
				{
					if (x > x1 || x < x2)
						ends = false;
				}
				if (y2 - y1 > ERROR_OF_POINTER)
				{
					if (y < y1 || y > y2)
						ends = false;
				}
				else if (y1 - y2 > ERROR_OF_POINTER)
				{
					if (y > y1 || y < y2)
						ends = false;
				}
			}
			else
				ends = false;

			if (ends)
				return ends;
		}
	}
	return ends;
}
int Line::isOnFragment(int x, int y)
{
	for (int i = 0; i < 2; i++)
	{
		if (Dots.arr[i]->isOnFigure(x, y))
		{
			return i;
		}
	}
	return 0;
}
char Line::figureName()
{
	return 'L';
}
int Line::getX(int numberOfDot = 0)
{
	return Dots.arr[numberOfDot]->getX();
}
int Line::getY(int numberOfDot = 0)
{
	return Dots.arr[numberOfDot]->getY();
}
int Line::getNumOfAngles()
{
	return this->numOfAngles;
}

// Polygon