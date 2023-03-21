#pragma once
#include "figure.h"
#include <iostream>

class WinRender
{
public:
	WinRender(int x, int y);
	~WinRender();

	//do functions
	void doAMouse();
	void doAKey();
	void doAChange();

	//mouse functions
	void createmode();
	void movemode();
	void dragmode();
	void choosing();
	bool mouseProcessing();

	//key functions
	void movekey();
	void createkey();
	void choosekey();
	void chooseallkey();
	void rotatekey();
	void zoomkey();
	void deletekey();
	void exitkey();

	//menu function
	void menu();
	//flag functions
	bool isExit();

private:

	dynarr<Figure*> figures;
	int choosed;
	int x, y, xscreen, yscreen;
	int numOfFragment;
	int numOfElements = 0;
	int counter1, counter2;

	char key;
	void* bitmap;

	bool clickflag = false;
	bool exitflag = false;
	bool createflag = false;
	bool moveflag = false;
	bool dragflag = false;
	bool changeflag = false;
	bool chooseflag = false;
};