#include"Page.h"


void page_save::drawPage() {
	cleardevice();
	settextcolor(RGB(0, 0, 255));
	settextstyle(30, 0, L"微软雅黑");                      //调整窗口大小之后文字需要重新填写坐标
	outtextxy(270, 540, L"存档");

	

	button btnBack(450, 0, 150, 60, L"返回");

	btnBack.drawButton();
}