#include"Button.h"
#include<string.h>
#include<cwchar>
#include<windows.h>

// 获取按钮位置和尺寸
int button::getx() { return x; }
int button::gety() { return y; }
int button::getw() { return w; }
int button::geth() { return h; }
wchar_t* button::gettext() { return text; }

// 判断鼠标光标是否在按钮区域内
bool button::isinButton() {
	POINT pt;
	if (!GetCursorPos(&pt)) return false;
	HWND h = GetHWnd();
	ScreenToClient(h, &pt);  // 屏幕坐标转换为窗口客户区坐标
	return pt.x >= this->getx() && pt.x <= this->getx() + this->getw()
		&& pt.y >= this->gety() && pt.y <= this->gety() + this->geth();
}

// 构造函数：初始化按钮位置、大小和文本
button::button(int x0, int y0, int w0, int h0, const wchar_t *text0) {
	x = x0; y = y0; w = w0; h = h0; wcscpy_s(text, text0);
}

// 绘制按钮：蓝色边框圆角矩形 + 居中显示文本
void button::drawButton() {
	setlinecolor(RGB(0, 0, 255));       // 蓝色边框
	setlinestyle(PS_SOLID, 1);
	setfillcolor(RGB(180, 220, 255));   // 浅蓝色填充
	fillroundrect(x, y, x + w, y + h, 10, 10);
	settextcolor(BLACK);
	settextstyle(24, 0, L"微软雅黑");
	setbkmode(TRANSPARENT);             // 透明背景
	// 计算文本居中位置
	int tw = textwidth(text);
	int th = textheight(text);
	outtextxy(x + (w - tw) / 2, y + (h - th) / 2, text);
}