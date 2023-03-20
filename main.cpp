#include <Windows.h>
#include "figure.h"
#include <iostream>
int main(void)
{
	/*HWND Buffer_window, Active_window;
	HDC source, active, compatible;
	HBITMAP hbmactive;
	void* bitmap = nullptr;
	int active_number = initwindow(600, 600, "Lines"); // поменять местами
	Active_window = FindWindowA(0, "Lines");
	active = GetDC(Active_window);
	int buffer_number = initwindow(600, 600, "Buffer");
	Buffer_window = FindWindowA(0, "Buffer");
	source = GetDC(Buffer_window);
	*/
	//ShowWindow(Buffer_window, SW_HIDE);
	//compatible = CreateCompatibleDC(active);
	//hbmactive = CreateCompatibleBitmap(compatible, 600, 600);
	//HGDIOBJ hype = SelectObject(compatible, hbmactive);
	//cleardevice();
	//PrintWindow(Buffer_window, compatible, PW_CLIENTONLY);
	//SelectObject(compatible, hype);

	//SetWindowLong(Buffer_window, GWL_EXSTYLE, GetWindowLong(Buffer_window, GWL_EXSTYLE) | WS_EX_LAYERED);
	//SetLayeredWindowAttributes(Buffer_window, 0, 1, LWA_ALPHA);

	void* bitmap = nullptr;
	/*int gdriver = VGA, gmode = VGAMED;
	char graphname[1] = "";
	initgraph(&gdriver, &gmode, graphname);*/
	initwindow(600, 600, "Lines");
	bitmap = (void*)malloc(imagesize(0, 0, 600, 600));
	setvisualpage(0);
	while (1)
	{
		Sleep(37);
		setactivepage(1);
		std::cout << "Page 1" << std::endl;
		line(100, 100, 400, 400);
		line(100, 200, 200, 100);
		line(400, 100, 100, 400);
		getimage(0, 0, 600, 600, bitmap);
		clearviewport();
		setactivepage(0);
		std::cout << "Page 0" << std::endl;
		putimage(0, 0, bitmap, COPY_PUT);
		//ShowWindow(Buffer_window, SW_SHOW);
		//BitBlt(active, 0, 0, 600, 600, source, 0, 0, SRCCOPY);
		//ShowWindow(Buffer_window, SW_HIDE);
		/*bitmap = (void*)malloc(imagesize(0, 0, 600, 600));
		getimage(0, 0, 600, 600, bitmap);
		setactivepage(active_number);
		putimage(0, 0, bitmap, COPY_PUT);
		setactivepage(buffer_number);
		free(bitmap);
		*/

	}
}


/* setvisualpage example 


#include "graphics.h"
#pragma comment(lib,"graphics.lib")

#include <stdlib.h>

#include <stdio.h>

#include <conio.h>



int main(void)

{

	/* select driver and mode that supports multiple pages 

	int gdriver = EGA, gmode = EGAHI, errorcode;

	int x, y, ht;



	/* initialize graphics and local variables 
	char hello[1] = "";

	initgraph(&gdriver, &gmode, hello);



	/* read result of initialization 

	errorcode = graphresult();

	if (errorcode != grOk)    /* an error occurred 

	{

		printf("Graphics error: %s\n", grapherrormsg(errorcode));



		printf("Press any key to halt:");

		getch();

		exit(1);               /* terminate with an error code 

	}



	x = getmaxx() / 2;

	y = getmaxy() / 2;

	//ht = textheight("W");



	/*  select the off screen page for drawing 

	setactivepage(1);



	/* draw a line on page #1 

	line(0, 0, getmaxx(), getmaxy());



	/* output a message on page #1 

	settextjustify(CENTER_TEXT, CENTER_TEXT);

	outtextxy(x, y, "This is page #1:");

	outtextxy(x, y + ht, "Press any key to halt:"); 





	/* select drawing to page #0 

	setactivepage(0);



	/* output a message  on page #0 

	outtextxy(x, y, "This is page #0.");

	outtextxy(x, y + ht, "Press any key to view page #1:"); 

	getch();



	/* select page #1 as the visible page 

	setvisualpage(1);



	/* clean up 

	getch();

	closegraph();

	return 0;

}*/