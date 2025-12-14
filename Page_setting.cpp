#include"Page.h"
#include"Button.h"

void page_setting::drawPage() {
	cleardevice();
	settextcolor(RGB(0,100, 0));
	settextstyle(30, 0, L"Œ¢»Ì—≈∫⁄");
	outtextxy(80, 200, L"”Œœ∑…Ë÷√“≥");

	button btnBack(400, 0, 200, 60, L"∑µªÿ");

	/*if (btnBack.m.uMsg == WM_LBUTTONDOWN && btnBack.isinButton()) {
		currentPage = PAGE_MENU;
	}*/

	btnBack.drawButton();
}