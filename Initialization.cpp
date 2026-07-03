#include"initialization.h"
#include<easyx.h>

// 构造函数：创建600x600的图形窗口，设置白色背景
start::start() {
	initgraph(600, 600);
	outtextxy(250, 250, L"正在初始化...");
	setbkcolor(WHITE);
	FlushBatchDraw();  // 刷新批量绘图缓冲区
}

// 析构函数：关闭图形窗口
start::~start() {
	closegraph();
}