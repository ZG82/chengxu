#include"Page.h"


void page_save::drawPage() {
	cleardevice();
	settextcolor(RGB(0, 0, 255));
	settextstyle(30, 0, L"微软雅黑");                      //调整窗口大小之后文字需要重新填写坐标
	outtextxy(270, 540, L"帮助");

	settextcolor(RGB(0, 0, 0));
	settextstyle(20, 0, L"微软雅黑");
	outtextxy(10,80,L"1.账户的ID和密码请不要超过15个字，并且暂时不支持云端数据保存，只有本地数据");
	outtextxy(10, 100, L"2.退出游戏请使用ESC键，否则会占用后台不停的运行，或者手动完整退出程序");
	outtextxy(10, 120, L"3.悔棋功能没有弹窗提示，悔棋之后不可恢复，使用前请谨慎");
	outtextxy(10, 145, L"按键说明");
	outtextxy(10, 170, L"4.玩家一WASD控制，F落子，玩家二上下左右控制，0落子");
	outtextxy(10, 190, L"5.backspace悔棋");
	outtextxy(10, 215, L"性能说明");
	outtextxy(10, 240, L"6.存档只会保存上一次游戏，并且任何账户都可以进行游戏");
	outtextxy(10, 260, L"7.由于时间关系本游戏开发并未完全，部分功能和性能有待提高");
	
	
	outtextxy(10, 160, L"5.backspace悔棋");
	
	settextcolor(RGB(0, 255, 0));
	settextstyle(50, 0, L"微软雅黑");
	outtextxy(200, 400, L"感谢游玩！");
	button btnBack(400, 0, 150, 60, L"返回");

	btnBack.drawButton();
}