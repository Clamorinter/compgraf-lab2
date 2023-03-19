#pragma once
#define BASE_COLOR 0
#include "dynarr.h"

class Figure
{
public:
	Figure() : color(BASE_COLOR) {};
	virtual void draw();

	virtual void rotate(float angle);

	virtual void zoom(float multiplier);

	virtual void move(int dx, int dy);

	virtual void setColor(int color);

	virtual int isOnFigure(int x, int y);

	virtual char figureName();

protected:
	int color;

};

class Dot : public Figure {
public:
	Dot() : Figure(), x(0), y(0) {};
	Dot(int x, int y) : Figure(), x(x), y(y) {};

	void set(int x, int y);
	int getX();
	int getY();
private:
	int x;
	int y;
};

class Line : public Figure {
public:
	Line() : Figure() {
		for (int i = 0; i < 2; i++)
		{
			Dots.append(new Dot);
		}
	};
	~Line() {
		for (int i = 1; i >= 0; i--)
		{
			delete Dots.arr[i];
		}
	}
	void dragDot(int dx, int dy, int numberOfDot);
	int isOnDot(int x, int y);

private:
	dynarr<Figure*> Dots;
};

class Polygon : public Figure {
public:
	Polygon(int numOfAngles) : Figure(), numOfAngles(numOfAngles) {
		for (int i = 0; i < numOfAngles; i++)
		{
			Angles.append(new Dot);
			Lines.append(new Line);
		}
	}
	~Polygon()
	{
		for (int i = numOfAngles-1; i >= 0; i--)
		{
			delete Angles.arr[i];
			delete Lines.arr[i];
		}
	}
	void dragLine(int dx, int dy, int numberOfLine);
	int isOnLine(int dx, int dy);
private:
	dynarr<Figure*> Lines;
	dynarr<Figure*> Angles;
	int numOfAngles;
};