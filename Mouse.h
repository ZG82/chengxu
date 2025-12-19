#include<easyx.h>
#include<graphics.h>
#include<stdio.h>
#include<windows.h>
#include<iostream>
#include"Page.h"
#include"Button.h"
#include "Initialization.h"
#include"Currentpage.h"

#ifndef Mouse
#define Mouse
       
void run() {
        ExMessage msg;
        page_menu P1;
        page_game P2;
        page_setting P3;
        page_save P4;
        // 初始绘制主菜单
        P1.drawPage();
        FlushBatchDraw();
        currentPage = PAGE_MENU;

  //主循环，游戏进行关键！！！
    while (true) {
        // 在循环开始统一重绘主菜单，确保返回后界面干净且按钮可用
        if (currentPage == PAGE_MENU) {
            BeginBatchDraw();
            cleardevice();
            P1.drawPage();
            EndBatchDraw();
        }

        if (peekmessage(&msg, EX_MOUSE | EX_KEY, true)) {   //消息获取并移除
///////////////////////////////////////////////////////////////////////////////////////////////////////
                 if (currentPage == PAGE_MENU) {
                     //鼠标消息获取的判定，页面情况的分类
                            if (msg.x >= 200 && msg.x <= 400 && msg.y >= 100 && msg.y <= 160) {
                                if (msg.message == WM_LBUTTONDOWN) {
                                    // 直接进入游戏运行，让 page_game::Run 负责所有绘制
                                    currentPage = PAGE_GAME;
                                    // 清空屏幕并绘制游戏页面一次，确保菜单已被清除且返回按钮可见
                                    BeginBatchDraw();
                                    cleardevice();
                                    EndBatchDraw();
                                    // 进入游戏主循环
                                    P2.Run();
                                    // 确保游戏内的批绘已结束并清理消息
                                    flushmessage(EX_MOUSE);
                                    flushmessage(EX_KEY);
                                    // 清理游戏状态，避免棋盘残留
                                    P2.cleararr();
                                    // 返回主菜单，下一次循环会重绘菜单
                                    currentPage = PAGE_MENU;
                                    // 先清空画面并稍作等待，确保绘图缓冲区稳定
                                    BeginBatchDraw();
                                    cleardevice();
                                    P1.drawPage();
                                    EndBatchDraw();
                                    continue; // avoid processing the same msg further
                                }
                            }
                            else if (msg.x >= 200 && msg.x <= 400 && msg.y >= 200 && msg.y <= 260) {
                                if (msg.message == WM_LBUTTONDOWN) {
                                    P3.drawPage();
                                    currentPage = PAGE_SETTING;
                                    FlushBatchDraw();
                                }
                            }
                            else if (msg.x >= 200 && msg.x <= 400 && msg.y >= 300 && msg.y <= 360) {
                                if (msg.message == WM_LBUTTONDOWN) {
                                    P4.drawPage();
                                    currentPage = PAGE_SAVE;
                                    FlushBatchDraw();
                                }
                            }
                 }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                 else if (currentPage == PAGE_SETTING) {
                           if (msg.x >= 420 && msg.x <= 600 && msg.y >= 0 && msg.y <= 60&&msg.message==WM_LBUTTONDOWN) {
                               P1.drawPage();
                               currentPage = PAGE_MENU;
                               FlushBatchDraw();
                               continue;
                           }

                 }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                 else if (currentPage == PAGE_SAVE) {
                              if (msg.x >= 420 && msg.x <= 600 && msg.y >= 0 && msg.y <= 60 && msg.message == WM_LBUTTONDOWN) {
                                  P1.drawPage();
                                  currentPage = PAGE_MENU;
                                  FlushBatchDraw();
                                  continue;
                              }
                 }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //单独判断是否退出
                if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
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