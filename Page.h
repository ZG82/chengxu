#include<easyx.h>
#include<graphics.h>
#include<stdio.h>
#include"Button.h"
#include"Currentpage.h"


#ifndef Page
#define Page





class page {
public:
	virtual void drawPage()=0;
	virtual ~page(){}
	MOUSEMSG m = GetMouseMsg();
};

class page_menu :virtual public page{
private:
public:
	void drawPage()override ;
};

class page_game :virtual public page {
public:
	struct Player {
		int cursorX, cursorY;  // 光标位置
		int color;             // 棋子颜色
		bool active;           // 是否轮到此玩家
	};

	void drawPage()override ;
	void initGame();
	void drawBoard();
	void drawStone(int x, int y, int color);
	void drawCursor(int x, int y, int color);
	bool placeStone(Player& player);
	bool checkWin(int playerColor);
	void drawGameStatus();
	void Run();
	
	
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