#include "Page.h"
#include "Button.h"
#include"Mouse.h"
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include "easyx.h"
using namespace std;

int main() {
    initgraph(600, 600, EX_SHOWCONSOLE);
    outtextxy(250, 250, L"ÕýÔÚ³õÊ¼»¯");
    setbkcolor(WHITE);
    cleardevice(); // ÇåÆÁ

    FlushBatchDraw(); // Ë¢ÐÂ»æÍ¼»º³åÇø


   /* page_menu P1;
    page_game P2;
    page_setting P3;*/
    //Pages currentPage = PAGE_MENU;
    //P1.drawPage();
   // FlushBatchDraw();
    run();
    //ExMessage msg;
    //while (true) {
    //    if (peekmessage(&msg, EX_MOUSE | EX_KEY, true)) {
    //        if (msg.message == WM_LBUTTONDOWN)
    //            if (currentPage == PAGE_MENU) {
    //                if (msg.x >= 150 && msg.x <= 350 && msg.y >= 120 && msg.y <= 180) {
    //                    cleardevice();
    //                    P2.drawPage();
    //                    currentPage = PAGE_GAME;
    //                    FlushBatchDraw(); // Ë¢ÐÂ»æÍ¼»º³åÇø
    //                }
    //                else if (msg.x >= 150 && msg.x <= 350 && msg.y >= 220 && msg.y <= 280) {
    //                    cleardevice();
    //                    P3.drawPage();
    //                    currentPage = PAGE_SETTING;
    //                    FlushBatchDraw(); // Ë¢ÐÂ»æÍ¼»º³åÇø
    //                }
    //            }
    //            else if (currentPage == PAGE_SETTING) {
    //                if (msg.x >= 420 && msg.x <= 600 && msg.y >= 0 && msg.y <= 60) {
    //                    cleardevice();
    //                    P1.drawPage();
    //                    currentPage = PAGE_MENU;
    //                    FlushBatchDraw(); // Ë¢ÐÂ»æÍ¼»º³åÇø
    //                }
    //            }
    //            else if (currentPage == PAGE_GAME) {
    //                if (msg.x >= 420 && msg.x <= 600 && msg.y >= 0 && msg.y <= 60) {
    //                    cleardevice();
    //                    P1.drawPage();
    //                    currentPage = PAGE_MENU;
    //                    FlushBatchDraw(); // Ë¢ÐÂ»æÍ¼»º³åÇø
    //                }
    //            }
    //    }
    //}

    Sleep(10);
}