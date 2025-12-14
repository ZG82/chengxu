#include<easyx.h>
#include<graphics.h>
#include<stdio.h>
#include<windows.h>
#include<iostream>
#include"Page.h"
#include"Button.h"
#include "Initialization.h"

#ifndef Mouse
#define Mouse
void run() {
    enum Pages {
        PAGE_MENU,
        PAGE_GAME,
        PAGE_SETTING,
        PAGE_SEVA,
    };
    Pages currentPage = PAGE_MENU;
        page_menu P1;
        page_game P2;
        page_setting P3;
        page_save P4;
        ExMessage msg;
        P1.drawPage();
        FlushBatchDraw();

  //主循环，游戏进行关键！！！
    while (true) {
        if (peekmessage(&msg, EX_MOUSE | EX_KEY, true)) {   //消息获取
            if (msg.message == WM_LBUTTONDOWN) {
                if (currentPage == PAGE_MENU) {
                    if (msg.x >= 200 && msg.x <= 400 && msg.y >= 100 && msg.y <= 160) {
                        cleardevice();                                   //清屏
                        P2.drawPage();                                   //绘制页面
                        currentPage = PAGE_GAME;                         //页面状态切换
                        FlushBatchDraw();                                // 刷新绘图缓冲区
                    }
                    else if (msg.x >= 200 && msg.x <= 400 && msg.y >= 200 && msg.y <= 260) {      //同上
                        cleardevice();
                        P3.drawPage();
                        currentPage = PAGE_SETTING;
                        FlushBatchDraw(); // 刷新绘图缓冲区
                    }
                    else if (msg.x >= 200 && msg.x <= 400 && msg.y >= 300 && msg.y <= 360) {
                        cleardevice();
                        P4.drawPage();
                        currentPage = PAGE_SEVA;
                        FlushBatchDraw(); // 刷新绘图缓冲区
                    }
                }
                else if (currentPage == PAGE_SETTING) {
                    if (msg.x >= 420 && msg.x <= 600 && msg.y >= 0 && msg.y <= 60) {
                        cleardevice();
                        P1.drawPage();
                        currentPage = PAGE_MENU;
                        FlushBatchDraw(); // 刷新绘图缓冲区
                    }
                }
                else if (currentPage == PAGE_GAME) {
                    if (msg.x >= 420 && msg.x <= 600 && msg.y >= 0 && msg.y <= 60) {
                        cleardevice();
                        P1.drawPage();
                        currentPage = PAGE_MENU;
                        FlushBatchDraw(); // 刷新绘图缓冲区
                    }
                }
                else if (currentPage == PAGE_SEVA) {
                    if (msg.x >= 420 && msg.x <= 600 && msg.y >= 0 && msg.y <= 60) {
                        cleardevice();
                        P1.drawPage();
                        currentPage = PAGE_MENU;
                        FlushBatchDraw(); // 刷新绘图缓冲区
                    }
                }
            }
            else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {            //esc实现，windows窗口的使用
                    // 弹出确认对话框
                    int result = MessageBox(
                        GetHWnd(),
                        _T("确定要退出游戏吗？"),
                        _T("退出确认"),
                        MB_ICONQUESTION | MB_YESNO
                    );
                    if (result == IDYES) {

                        closegraph();
                        std::cout << std::endl << std::endl << "游戏已退出!!!" << std::endl << std::endl;
                        exit(0);
                    }
            }
                
        }
        Sleep(10);
    }
}

#endif