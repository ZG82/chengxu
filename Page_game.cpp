#include"Page.h"
#include"Button.h"

void page_game::drawPage() {
	cleardevice();
	settextcolor(RGB(255, 0, 0));
	settextstyle(30, 0, L"微软雅黑");
	outtextxy(200, 540, L"五子棋游戏页");

	button btnBack(420, 0, 180, 60, L"返回");

	btnBack.drawButton();

	/*if (btnBack.m.uMsg == WM_LBUTTONDOWN && btnBack.isinButton()) {
		currentPage = PAGE_MENU;
	}*/

	//图片设置
	IMAGE img_board;
	loadimage(&img_board, _T("assets/棋盘.jpg"), 396, 373);//加载图片，在assets里面（ps：老费劲了找这个路径），还有牛逼的_T
	putimage(10, 10, &img_board);//打印图片




	
}