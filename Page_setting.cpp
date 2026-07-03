#include"Page.h"

// 绘制设置页面（目前功能开发中）
void page_setting::drawPage() {
	cleardevice();
	settextcolor(RGB(0,0,255));
	settextstyle(30, 0, L"微软雅黑");
	outtextxy(230, 540, L"游戏设置页");

	settextcolor(RGB(0, 0, 255));
	settextstyle(80, 0, L"微软雅黑");
	outtextxy(150, 250, L"正在开发...");

	button btnBack(450, 0, 150, 60, L"返回");
	btnBack.drawButton();
}