#include<easyx.h>
#include<graphics.h>

#ifndef Button
#define Button

// 按钮类，封装按钮的位置、大小、文本和绘制逻辑
class button {
private:
	int x, y, w, h;          // 按钮左上角坐标(x,y)和宽高(w,h)
	wchar_t text[20];         // 按钮显示文本

public:
	button(int x0, int y0, int w0, int h0, const wchar_t *text);

	// 判断鼠标是否在按钮区域内
	bool isinButton();

	// 获取按钮属性
	int getx();
	int gety();
	int getw();
	int geth();
	wchar_t* gettext();

	// 绘制按钮（圆角矩形 + 居中文字）
	void drawButton();
};

#endif