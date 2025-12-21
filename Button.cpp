#include"Button.h"
#include<string.h>
#include<cwchar>
#include<windows.h>

int button::getx() {return x;}
int button::gety() {return y;}
int button::getw() {return w;}
int button::geth() {return h;}
wchar_t* button::gettext() {return text;}

bool button::isinButton() {
	POINT pt;
	if (!GetCursorPos(&pt)) return false;
	HWND h = GetHWnd();
	ScreenToClient(h, &pt);
	return pt.x >= this->getx() && pt.x <= this->getx() + this->getw() && pt.y >= this->gety() && pt.y <= this->gety() + this->geth();
}

button::button(int x0, int y0, int w0, int h0, const wchar_t *text0 ){
	x = x0; y = y0; w = w0; h = h0; wcscpy_s(text,text0);
}

//绘画按钮，颜色，大小位置，文字自动居中不需要更改
//主要的外部接口
void button::drawButton() {
	setlinecolor(RGB(0, 0, 255)); 
	setlinestyle(PS_SOLID, 1);
	setfillcolor(RGB(180, 220, 255));
	fillroundrect(x, y, x + w, y + h, 10, 10);
	settextcolor(BLACK);
	settextstyle(24, 0, L"微软雅黑");
	setbkmode(TRANSPARENT);
	int tw = textwidth(text);
	int th = textheight(text);
	outtextxy(x + (w - tw) / 2, y + (h - th) / 2, text);

}