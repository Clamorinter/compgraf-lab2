#pragma once
#include "figure.h"

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
	void createmode(int x, int y);
	void movemode(int x, int y);
	void dragmode(int x, int y);
	void choosing(int x, int y);
	bool mouseProcessing();

	//key functions
	void movekey(char key);
	void createkey(char key);
	void choosekey(char key);
	void chooseallkey();
	void rotatekey(char key);
	void zoomkey(char key);
	void deletekey();
	void exitkey();

	//menu function
	void menu();
	//flag functions
	bool isExit();

private:

	dynarr<Figure**> figures;
	int choosed;
	int x, y;
	int numOfFragment;
	int numOfElements = 0;
	char c;
	void* bitmap;

	bool clickflag = false;
	bool exitflag = false;
	bool createflag = false;
	bool moveflag = false;
	bool changeflag = false;
	bool chooseflag = false;
};