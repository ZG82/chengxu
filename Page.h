#include<easyx.h>
#include<graphics.h>
#include<stdio.h>
#include"Button.h"
#include"Currentpage.h"
#include"Player.h"

#ifndef Page
#define Page



class page {
public:
	virtual void drawPage()=0;
	virtual ~page(){}
	MOUSEMSG m; 
};

class page_menu :virtual public page{
private:
public:
	void drawPage()override ;
};

class page_game :virtual public page {
public:
	void sign_in();
	void drawPage()override ;
	void initGame();
	void drawBoard();
	void drawStone(int x, int y, int color);
	void drawCursor(int x, int y, int color);
	void drawHighlight(int x, int y); 
	bool placeStone(player& player0);
	bool checkWin(int playerColor);
	void drawGameStatus();
	bool istie();
	void Run();
	void cleararr();
	bool sign_in1=false;
	bool sign_in2=false;
};

class page_setting :virtual public page {
public:
	void drawPage()override ;
	
};

class page_save :virtual public page {
public:
	void drawPage()override ;
};



#endif