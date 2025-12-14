#include"Page.h"
#include"Button.h"

void page_game::drawPage() {
	cleardevice();
	settextcolor(RGB(0, 0, 255));                     //调整窗口大小之后文字需要重新填写坐标
	settextstyle(30, 0, L"微软雅黑");
	outtextxy(230, 540, L"五子棋游戏页");
	

	button btnBack(450, 0, 150, 60, L"返回");

	btnBack.drawButton();

	//图片设置
	IMAGE img_board;
	loadimage(&img_board, _T("assets/棋盘.jpg"), 396, 373);//加载图片，在assets里面（ps：老费劲了找这个路径），还有牛逼的_T
	putimage(10, 10, &img_board);//打印图片
}