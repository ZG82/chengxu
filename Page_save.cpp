#include"Page.h"
#include"Button.h"

void page_save::drawPage() {
	cleardevice();
	settextcolor(RGB(0, 0, 255));
	settextstyle(30, 0, L"Î¢ÈíÑÅºÚ");
	outtextxy(270, 540, L"´æµµ");

	button btnBack(450, 0, 150, 60, L"·µ»Ø");

	btnBack.drawButton();
}