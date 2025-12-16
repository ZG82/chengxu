#include"initialization.h"
#include<easyx.h>


start::start() {
	initgraph(600, 600);
	outtextxy(250, 250, L"正在初始化...");
	setbkcolor(WHITE);
	FlushBatchDraw(); // 刷新绘图缓冲区
	
}

start::~start() {
	closegraph();
}