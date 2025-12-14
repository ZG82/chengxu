#include"Button.h"
#include<string.h>
#include<cwchar>

int button::getx() {return x;}
int button::gety() {return y;}
int button::getw() {return w;}
int button::geth() {return h;}
wchar_t* button::gettext() {return text;}

bool button::isinButton() {
	return m.x >= this->getx() && m.x <= this->getx() + this->getw() && m.y >= this->gety() && m.y <= this->gety() + this->geth();
	FlushBatchDraw();
}

button::button(int x0, int y0, int w0, int h0, const wchar_t *text0 ){
	x = x0; y = y0; w = w0; h = h0; wcscpy_s(text,text0);
}

//绘画按钮，颜色，大小位置，文字自动居中不需要更改
//主要的外部接口
void button::drawButton() {
	setfillcolor(isinButton() ? RGB(100, 200, 255) : RGB(180, 220, 255)); 
	fillroundrect(x, y, x + w, y + h, 10, 10);
	settextcolor(BLACK);
	settextstyle(24, 0, L"微软雅黑");
	setbkmode(TRANSPARENT);
	int tw = textwidth(text);
	int th = textheight(text);
	outtextxy(x + (w - tw) / 2, y + (h - th) / 2, text);
	FlushBatchDraw();
}
