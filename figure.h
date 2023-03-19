#pragma once
#define BASE_COLOR 0

class Figure
{
public:
	Figure() : color(BASE_COLOR) {};
	virtual void draw();

	virtual void rotate(float angle);

	virtual void zoom(float multiplier);

	virtual void move(int dx, int dy);

	virtual void setColor(int color);

	virtual bool isOnFigure(int x, int y);

	virtual char figureName();

protected:
	int color;

};

class Dot : public Figure {
protected:
	int x;
	int y;
};

class Line : public Dot {
public:
	void dragDot(int dx, int dy, int numberOfDot);
	bool isOnDot(int x, int y, int numberOfDot);

protected:
	Figure** Dots;
};

class Polygon : public Line {
public:
	void dragLine(int dx, int dy, int numberOfLine);
	bool isOnLine(int dx, int dy, int numberOfLine);
protected:
	Figure** Lines;
};