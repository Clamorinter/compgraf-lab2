#include "figure.h"

// Dot
void Dot::draw()
{
	putpixel(x, y, color);
}
void Dot::rotate(float angle, int centerx, int centery) {}
void Dot::zoom(float multiplier, int centerx, int centery) {}
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
	return false;
}
int Dot::isOnFragment(int x, int y)
{
	return '\0';
}
char Dot::figureName()
{
	return 'D';
}
int Dot::findCenter(char coord)
{
	if (coord == 'x')
	{
		return x;
	}
	if (coord == 'y')
	{
		return y;
	}
	return -1;
}
int Dot::getX(int numberOfDot)
{
	if (numberOfDot == 0)
	{
		return x;
	}
	return 0;
}
int Dot::getY(int numberOfDot)
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
void Line::rotate(float angle, int centerx, int centery)
{
	int x1 = Dots.arr[0]->getX();
	int y1 = Dots.arr[0]->getY();
	int x2 = Dots.arr[1]->getX();
	int y2 = Dots.arr[1]->getY();
	move(-centerx, -centery);
	int new_x1 = (int)round((float)x1 * cos(angle)) + (int)round((float)y1 * sin(angle));
	int new_y1 = -(int)round((float)x1 * sin(angle)) + (int)round((float)y1 * cos(angle));
	int new_x2 = (int)round((float)x2 * cos(angle)) + (int)round((float)y2 * sin(angle));
	int new_y2 = -(int)round((float)x2* sin(angle)) + (int)round((float)y2 * cos(angle));
	moveFragment(new_x1 - x1, new_y1 - y1, 0);
	moveFragment(new_x2 - x2, new_y2 - y2, 1);
	move(centerx, centery);
}
void Line::zoom(float multiplier, int centerx, int centery)
{
	int x1 = Dots.arr[0]->getX();
	int y1 = Dots.arr[0]->getY();
	int x2 = Dots.arr[1]->getX();
	int y2 = Dots.arr[1]->getY();
	move(-centerx, -centery);
	int new_x1 = (int)round((float)x1 * multiplier);
	int new_y1 = (int)round((float)y1 * multiplier);
	int new_x2 = (int)round((float)x2 * multiplier);
	int new_y2 = (int)round((float)y2 * multiplier);
	if (multiplier < 1.0)
	{
		float rad = atan((float)abs(y2-y1) / (float)abs(x2-x1));
		rotate((float)0.78539 - rad, centerx, centery);
		if (abs(new_x1 - x1) <= 1 || abs(new_y1 - y1) <= 1 || abs(new_x2 - x2) <= 1 || abs(new_y2 - y2) <= 1)
		{
			new_x1 = x1;
			new_y1 = y1;
			new_x2 = x2;
			new_y2 = y2;
			
		}
		rotate(rad - (float)0.78539, centerx, centery);
	}
	moveFragment(new_x1 - x1, new_y1 - y1, 0);
	moveFragment(new_x2 - x2, new_y2 - y2, 1);
	move(centerx, centery);
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
int Line::findCenter(char coord)
{
	int cordin = 0;
	if (coord == 'x')
	{
		for (int i = 0; i < numOfAngles; i++)
		{
			cordin += Dots.arr[i]->getX();
		}
	}
	if (coord == 'y')
	{
		for (int i = 0; i < numOfAngles; i++)
		{
			cordin += Dots.arr[i]->getY();
		}
	}
	cordin = (int)round((float)cordin / 2.0);
	return cordin;
}
int Line::getX(int numberOfDot)
{
	return Dots.arr[numberOfDot]->getX();
}
int Line::getY(int numberOfDot)
{
	return Dots.arr[numberOfDot]->getY();
}
int Line::getNumOfAngles()
{
	return this->numOfAngles;
}

// Polygon
void Polygon::draw()
{
	setcolor(color);
	for (int i = 0; i < numOfAngles; i++)
	{
		Lines.arr[i]->draw();
	}
}
void Polygon::rotate(float angle, int centerx, int centery)
{
	dynarr<Figure*> centerLines;
	Figure* line;
	int new_x, new_y, x, y;
	for (int i = 0; i < numOfAngles; i++)
	{
		line = new Line;
		line->moveFragment(Lines.arr[i]->getX(), Lines.arr[i]->getY(), 0);
		line->moveFragment(centerx, centery, 1);
		centerLines.append(line);
		delete line;
	}
	for (int i = 0; i < numOfAngles; i++)
	{
		centerLines.arr[i]->rotate(angle, centerx, centery);
		new_x = centerLines.arr[i]->getX(0);
		new_y = centerLines.arr[i]->getY(0);
		x = Lines.arr[i]->getX();
		y = Lines.arr[i]->getY();
		moveFragment(new_x - x, new_y - y, i);
	}
}
void Polygon::zoom(float multiplier, int centerx, int centery)
{
	dynarr<Figure*> centerLines;
	Figure* line;
	int new_x, new_y, x, y;
	for (int i = 0; i < numOfAngles; i++)
	{
		line = new Line;
		line->moveFragment(Lines.arr[i]->getX(), Lines.arr[i]->getY(), 0);
		line->moveFragment(centerx, centery, 1);
		centerLines.append(line);
		delete line;
	}
	for (int i = 0; i < numOfAngles; i++)
	{
		centerLines.arr[i]->zoom(multiplier, centerx, centery);
		new_x = centerLines.arr[i]->getX(0);
		new_y = centerLines.arr[i]->getY(0);
		x = Lines.arr[i]->getX();
		y = Lines.arr[i]->getY();
		moveFragment(new_x - x, new_y - y, i);
	}
}
void Polygon::move(int dx, int dy)
{
	for (int i = 0; i < numOfAngles; i++)
	{
		Lines.arr[i]->move(dx, dy);
	}
}
void Polygon::moveFragment(int dx, int dy, int numberOfFragment)
{
	if (numberOfFragment < numOfAngles) // Dots
	{
		int friendLine = numberOfFragment - 1;
		Lines.arr[numberOfFragment]->moveFragment(dx, dy, 0);
		if (numberOfFragment == 0)
		{
			friendLine = numOfAngles - 1;
		}
		Lines.arr[friendLine]->moveFragment(dx, dy, 1);
	}
	else // Lines
	{
		numberOfFragment = numberOfFragment - numOfAngles;
		int prev_line = numberOfFragment - 1;
		int next_line = numberOfFragment + 1;
		if (prev_line == -1)
		{
			prev_line = numOfAngles - 1;
		}
		if (next_line == numOfAngles)
		{
			next_line = 0;
		}
		Lines.arr[numberOfFragment]->move(dx, dy);
		Lines.arr[prev_line]->moveFragment(dx, dy, 1);
		Lines.arr[next_line]->moveFragment(dx, dy, 0);
	}
}
void Polygon::setColor(int color)
{
	this->color = color;
}
bool Polygon::isOnFigure(int x, int y)
{
	return true;
}