#include"Page.h"
#include"Button.h"

void page_setting::drawPage() {
	cleardevice();
	settextcolor(RGB(0,0,255));
	settextstyle(30, 0, L"微软雅黑");
	outtextxy(230, 540, L"游戏设置页");                    //调整窗口大小之后文字需要重新填写坐标

	button btnBack(450, 0, 150, 60, L"返回");

	btnBack.drawButton();
}