#include<easyx.h>
#include<graphics.h>
#include<stdio.h>
#include<windows.h>
#include<iostream>
#include"Page.h"
#include"Button.h"
#include "Initialization.h"
#include"Currentpage.h"
#include "Account.h"

#ifndef Mouse
#define Mouse

// 当前页面状态的全局定义（Currentpage.h中extern声明）
Pages currentPage = PAGE_MENU;

// 主消息循环：处理页面切换和用户输入
void run() {
    ExMessage msg;
    page_menu P1;       // 主菜单页
    page_game P2;       // 游戏页
    page_setting P3;    // 设置页
    page_save P4;       // 存档/帮助页
    page_rank P5;       // 排行榜页

    // 初始绘制主菜单
    P1.drawPage();
    FlushBatchDraw();
    currentPage = PAGE_MENU;

    while (true) {
        // 菜单页需要持续重绘（防止残留画面）
        if (currentPage == PAGE_MENU) {
            BeginBatchDraw();
            cleardevice();
            P1.drawPage();
            EndBatchDraw();
        }

        // 非阻塞获取消息（EX_MOUSE | EX_KEY），并从队列中移除
        if (peekmessage(&msg, EX_MOUSE | EX_KEY, true)) {
            // ===== 主菜单页的消息处理 =====
            if (currentPage == PAGE_MENU) {
                // "开始游戏"按钮区域
                if (msg.x >= 200 && msg.x <= 400 && msg.y >= 100 && msg.y <= 160) {
                    if (msg.message == WM_LBUTTONDOWN) {
                        // 确保两个玩家都已登录
                        if (!ensurePlayersLoggedIn()) {
                            MessageBox(GetHWnd(), _T("需要登录两个账户才能开始游戏！"), _T("登录取消"), MB_OK | MB_ICONWARNING);
                            continue;
                        }
                        // 重置会话得分
                        if (g_player1Account) g_player1Account->resetNow();
                        if (g_player2Account) g_player2Account->resetNow();

                        currentPage = PAGE_GAME;
                        // 清屏并进入游戏主循环
                        BeginBatchDraw();
                        cleardevice();
                        EndBatchDraw();
                        flushmessage(EX_MOUSE);
                        flushmessage(EX_KEY);
                        Sleep(50);  // 等待画面稳定
                        P2.Run();   // 进入游戏循环（阻塞直到退出游戏）
                        // 游戏结束后：提交会话得分并保存
                        flushmessage(EX_MOUSE);
                        flushmessage(EX_KEY);
                        if (g_player1Account) { g_player1Account->commitNow(); }
                        if (g_player2Account) { g_player2Account->commitNow(); }
                        saveAccounts();
                        P2.cleararr();  // 清空棋盘状态
                        currentPage = PAGE_MENU;
                        // 重绘菜单
                        BeginBatchDraw();
                        cleardevice();
                        P1.drawPage();
                        EndBatchDraw();
                        continue;
                    }
                }
                // "游戏设置"按钮区域
                else if (msg.x >= 200 && msg.x <= 400 && msg.y >= 200 && msg.y <= 260) {
                    if (msg.message == WM_LBUTTONDOWN) {
                        P3.drawPage();
                        currentPage = PAGE_SETTING;
                        FlushBatchDraw();
                    }
                }
                // "存档"按钮区域
                else if (msg.x >= 200 && msg.x <= 400 && msg.y >= 300 && msg.y <= 360) {
                    if (msg.message == WM_LBUTTONDOWN) {
                        P4.drawPage();
                        currentPage = PAGE_SAVE;
                        FlushBatchDraw();
                    }
                }
                // "排行榜"按钮区域
                else if (msg.x >= 200 && msg.x <= 400 && msg.y >= 400 && msg.y <= 460) {
                    if (msg.message == WM_LBUTTONDOWN) {
                        P5.drawPage();
                        currentPage = PAGE_RANK;
                        FlushBatchDraw();
                    }
                }
            }
            // ===== 设置页：返回按钮 =====
            else if (currentPage == PAGE_SETTING) {
                if (msg.x >= 420 && msg.x <= 600 && msg.y >= 0 && msg.y <= 60 && msg.message == WM_LBUTTONDOWN) {
                    P1.drawPage();
                    currentPage = PAGE_MENU;
                    FlushBatchDraw();
                    continue;
                }
            }
            // ===== 存档页：返回按钮 =====
            else if (currentPage == PAGE_SAVE) {
                if (msg.x >= 420 && msg.x <= 600 && msg.y >= 0 && msg.y <= 60 && msg.message == WM_LBUTTONDOWN) {
                    P1.drawPage();
                    currentPage = PAGE_MENU;
                    FlushBatchDraw();
                    continue;
                }
            }
            // ===== 排行榜页：返回按钮 =====
            else if (currentPage == PAGE_RANK) {
                if (msg.x >= 420 && msg.x <= 600 && msg.y >= 0 && msg.y <= 60 && msg.message == WM_LBUTTONDOWN) {
                    P1.drawPage();
                    currentPage = PAGE_MENU;
                    FlushBatchDraw();
                    continue;
                }
            }

            // ESC键退出游戏（全局生效）
            if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
                int result = MessageBox(
                    GetHWnd(),
                    _T("确认要退出游戏？"),
                    _T("退出确认"),
                    MB_ICONQUESTION | MB_YESNO
                );
                if (result == IDYES) {
                    // 退出前提交会话得分
                    if (g_player1Account) { g_player1Account->commitNow(); }
                    if (g_player2Account) { g_player2Account->commitNow(); }
                    saveAccounts();
                    closegraph();
                    std::cout << std::endl << std::endl << "游戏已退出!!!" << std::endl << std::endl;
                    exit(0);
                }
            }
        }

        Sleep(10);  // 降低CPU占用
    }
}

#endif