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
    while (true) {
        if (peekmessage(&msg, EX_MOUSE | EX_KEY, true)) {
            if (msg.message == WM_LBUTTONDOWN)
                if (currentPage == PAGE_MENU) {
                    if (msg.x >= 200 && msg.x <= 400 && msg.y >= 100 && msg.y <= 160) {
                        cleardevice();
                        P2.drawPage();
                        currentPage=PAGE_GAME;
                        FlushBatchDraw(); // Ë¢ÐÂ»æÍ¼»º³åÇø
                    }
                    else if (msg.x >= 200 && msg.x <= 400 && msg.y >= 200 && msg.y <= 260) {
                        cleardevice();
                        P3.drawPage();
                        currentPage = PAGE_SETTING;
                        FlushBatchDraw(); // Ë¢ÐÂ»æÍ¼»º³åÇø
                    }
                    else if (msg.x >= 200 && msg.x <= 400 && msg.y >= 300 && msg.y <= 360) {
                        cleardevice();
                        P4.drawPage();
                        currentPage = PAGE_SEVA;
                        FlushBatchDraw(); // Ë¢ÐÂ»æÍ¼»º³åÇø
                    }
                }
                else if (currentPage == PAGE_SETTING) {
                    if (msg.x >= 420 && msg.x <= 600 && msg.y >= 0 && msg.y <= 60) {
                        cleardevice();
                        P1.drawPage();
                        currentPage=PAGE_MENU;
                        FlushBatchDraw(); // Ë¢ÐÂ»æÍ¼»º³åÇø
                    }
                }
                else if (currentPage == PAGE_GAME) {
                    if (msg.x >= 420 && msg.x <= 600 && msg.y >= 0 && msg.y <= 60) {
                        cleardevice();
                        P1.drawPage();
                        currentPage=PAGE_MENU;
                        FlushBatchDraw(); // Ë¢ÐÂ»æÍ¼»º³åÇø
                    }
                }
                else if (currentPage == PAGE_SEVA) {
                    if (msg.x >= 420 && msg.x <= 600 && msg.y >= 0 && msg.y <= 60) {
                        cleardevice();
                        P1.drawPage();
                        currentPage = PAGE_MENU;
                        FlushBatchDraw(); // Ë¢ÐÂ»æÍ¼»º³åÇø
                    }
                }
        }
        Sleep(10);
    }
}

#endif