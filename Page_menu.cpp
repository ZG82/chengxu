#include"Page.h"



void page_menu::drawPage() {
	cleardevice();
	settextcolor(RGB(0, 0, 255));
	settextstyle(30, 0, L"微软雅黑");
	outtextxy(230,540, L"五子棋菜单页");                      //调整窗口大小之后文字需要重新填写坐标
	settextstyle(50, 0, L"微软雅黑");
	outtextxy(240, 0, L"五子棋");

	button btnStart(200, 100, 200, 60, L"开始游戏");
	button btnSetting(200, 200, 200, 60, L"游戏设置");
	button btnSave(200, 300, 200, 60, L"存档");

	btnStart.drawButton();
	btnSetting.drawButton();
	btnSave.drawButton();
}