#pragma once
#define BASE_COLOR 0
#define ERROR_OF_POINTER 10
#include "dynarr.h"
#include <cmath>

#include "graphics.h"
#pragma comment(lib,"graphics.lib")

class Figure
{
public:
	Figure() : color(BASE_COLOR) {};
	virtual void draw();
	virtual void rotate(float angle);
	virtual void zoom(float multiplier);
	virtual void move(int dx, int dy);
	virtual void moveFragment(int dx, int dy, int numberOfFragment);
	virtual void setColor(int color);
	virtual bool isOnFigure(int x, int y);
	virtual int isOnFragment(int x, int y);
	virtual char figureName();
	virtual int getX(int numberOfDot = 0);
	virtual int getY(int numberOfDor = 0);
	virtual int getNumOfAngles();
protected:
	int color;
	int numOfAngles;
};

class Dot : public Figure {
public:
	Dot() : Figure(), x(0), y(0) {
		this->numOfAngles = 1;
	};
	Dot(int x, int y) : Figure(), x(x), y(y) {
		this->numOfAngles = 1;
	};
	void draw();
	void rotate(float angle);
	void zoom(float multiplier);
	void move(int dx, int dy);
	void moveFragment(int dx, int dy, int numberOfFragment);
	void setColor(int color);
	bool isOnFigure(int x, int y);
	int isOnFragment(int x, int y);
	char figureName();
	int getX(int numberOfDot = 0);
	int getY(int numberOfDot = 0);
	int getNumOfAngles();
private:
	int x;
	int y;
};

class Line : public Figure {
public:
	Line() : Figure() {
		for (int i = 0; i < 2; i++)
		{
			Dots.append(new Dot(0, 0));
		}
		this->numOfAngles = 2;
	};
	~Line() {
		for (int i = 1; i >= 0; i--)
		{
			delete Dots.arr[i];
		}
	}
	void draw();
	void rotate(float angle);
	void zoom(float multiplier);
	void move(int dx, int dy);
	void moveFragment(int dx, int dy, int numberOfFragment);
	void setColor(int color);
	bool isOnFigure(int x, int y);
	int isOnFragment(int x, int y);
	char figureName();
	int getX(int numberOfDot = 0);
	int getY(int numberOfDor = 0);
	int getNumOfAngles();
private:
	dynarr<Figure*> Dots;

};

class Polygon : public Figure {
public:
	Polygon(int numOfAngles) : Figure() {
		for (int i = 0; i < numOfAngles; i++)
		{
			Angles.append(new Dot);
			Lines.append(new Line);
		}
		this->numOfAngles = numOfAngles;
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
};