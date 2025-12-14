#include"Page.h"
#include"Button.h"

void page_menu::drawPage() {
	cleardevice();
	settextcolor(RGB(0, 0, 255));
	settextstyle(40, 0, L"微软雅黑");
	outtextxy(100, 50, L"五子棋菜单页");


	button btnStart(150, 120, 200, 60, L"开始游戏");
	button btnSetting(150, 220, 200, 60, L"游戏设置");

	/*if (btnStart.m.uMsg == WM_LBUTTONDOWN && btnStart.isinButton()) {
		currentPage = PAGE_GAME;
	}
	else if(btnSetting.m.uMsg == WM_LBUTTONDOWN && btnSetting.isinButton()){
		currentPage = PAGE_SETTING;
	}*/


	btnStart.drawButton();
	btnSetting.drawButton();
}

