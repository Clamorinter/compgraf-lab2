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
int Dot::isOnBoarder(int x, int y)
{
	return '\0';
}
char Dot::figureName()
{
	return 'D';
}

 // Line
