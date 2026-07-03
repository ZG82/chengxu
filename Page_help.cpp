#include"Page.h"

// 绘制存档/帮助页面：显示游戏操作说明和存档说明
void page_save::drawPage() {
	cleardevice();
	settextcolor(RGB(0, 0, 255));
	settextstyle(30, 0, L"微软雅黑");
	outtextxy(270, 540, L"存档");

	// 操作说明
	settextcolor(RGB(0, 0, 0));
	settextstyle(20, 0, L"微软雅黑");
	outtextxy(10, 80, L"1.账户的ID和密码请不要超过15字符，目前仅支持手动数据保存，只有保存才能存");
	outtextxy(10, 100, L"2.退出游戏请使用ESC键，直接关闭可能占用后台进程，需要手动关闭退出");
	outtextxy(10, 120, L"3.存档功能没有弹窗提示，存档之后不可恢复使用当前存档");
	outtextxy(10, 145, L"游戏说明：");
	outtextxy(10, 170, L"4.玩家一WASD移动，F落子；玩家二方向键移动，0落子");
	outtextxy(10, 190, L"5.backspace悔棋");
	outtextxy(10, 215, L"存档说明：");
	outtextxy(10, 240, L"6.存档只会保存上一次游戏，任何账户都可以继续该游戏");
	outtextxy(10, 260, L"7.存档时若上一次的游戏数据未完全写入可能会造成数据错误");

	settextcolor(RGB(0, 255, 0));
	settextstyle(50, 0, L"微软雅黑");
	outtextxy(200, 400, L"感谢游玩！");
	button btnBack(400, 0, 150, 60, L"返回");
	btnBack.drawButton();
}