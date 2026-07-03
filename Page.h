#include<easyx.h>
#include<graphics.h>
#include<stdio.h>
#include"Button.h"
#include"Currentpage.h"
#include"Player.h"

#ifndef Page
#define Page

// 页面基类，定义绘制接口
class page {
public:
	virtual void drawPage()=0;   // 纯虚函数，子类必须实现页面绘制
	virtual ~page(){}
};

// 主菜单页面
class page_menu :virtual public page{
private:
public:
	void drawPage()override;
};

// 游戏页面：五子棋核心逻辑
class page_game :virtual public page {
public:
	void sign_in();
	void drawPage()override;
	void initGame();                              // 初始化游戏状态
	void drawBoard();                             // 绘制棋盘
	void drawStone(int x, int y, int color);      // 绘制棋子
	void drawCursor(int x, int y, int color);     // 绘制光标
	void drawHighlight(int x, int y);             // 绘制胜利高亮圈
	bool placeStone(player& player0);             // 落子
	bool checkWin(int playerColor);               // 检查是否五连
	void drawGameStatus();                        // 绘制游戏状态信息
	bool istie();                                 // 检查是否平局
	void Run();                                   // 游戏主循环
	void cleararr();                              // 清空棋盘数组
	void savegamedate();                          // 保存游戏数据到文件
	void loadoldBoard();                          // 从文件加载棋盘
	bool isFileEmpty();                           // 检查存档文件是否为空
};

// 设置页面（开发中）
class page_setting :virtual public page {
public:
	void drawPage()override;
};

// 存档/帮助页面
class page_save :virtual public page {
public:
	void drawPage()override;
};

// 排行榜页面
class page_rank :virtual public page {
public:
	void drawPage()override;
};

#endif