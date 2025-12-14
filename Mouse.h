#include"easyx.h"
#include"graphics.h"
#include<stdio.h>
#include<windows.h>
#include<iostream>
#include"Page.h"
#include"Button.h"


void run() {
        Pages currentPage = PAGE_MENU;
        page_menu P1;
        page_game P2;
        page_setting P3;
        ExMessage msg;
        P1.drawPage();
        FlushBatchDraw();
    while (true) {
        if (peekmessage(&msg, EX_MOUSE | EX_KEY, true)) {
            if (msg.message == WM_LBUTTONDOWN)
                if (currentPage == PAGE_MENU) {
                    if (msg.x >= 150 && msg.x <= 350 && msg.y >= 120 && msg.y <= 180) {
                        cleardevice();
                        P2.drawPage();
                        currentPage = PAGE_GAME;
                        FlushBatchDraw(); // Ë¢ÐÂ»æÍ¼»º³åÇø
                    }
                    else if (msg.x >= 150 && msg.x <= 350 && msg.y >= 220 && msg.y <= 280) {
                        cleardevice();
                        P3.drawPage();
                        currentPage = PAGE_SETTING;
                        FlushBatchDraw(); // Ë¢ÐÂ»æÍ¼»º³åÇø
                    }
                }
                else if (currentPage == PAGE_SETTING) {
                    if (msg.x >= 420 && msg.x <= 600 && msg.y >= 0 && msg.y <= 60) {
                        cleardevice();
                        P1.drawPage();
                        currentPage = PAGE_MENU;
                        FlushBatchDraw(); // Ë¢ÐÂ»æÍ¼»º³åÇø
                    }
                }
                else if (currentPage == PAGE_GAME) {
                    if (msg.x >= 420 && msg.x <= 600 && msg.y >= 0 && msg.y <= 60) {
                        cleardevice();
                        P1.drawPage();
                        currentPage = PAGE_MENU;
                        FlushBatchDraw(); // Ë¢ÐÂ»æÍ¼»º³åÇø
                    }
                }
        }
    }
}
