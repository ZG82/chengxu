#include "Page.h"
#include "Button.h"
#include"Mouse.h"
#include"Initialization.h"
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <easyx.h>

using namespace std;

int main() {
    Sleep(500);
    cout << "正在配置游戏数据..."<<endl;
    Sleep(500);
    cout << "正在连接移动数据..."<<endl;
    Sleep(500);
    cout << "正在启动游戏..."<<endl;
    Sleep(500);
    start GoBang;
    Sleep(500);
    run();
    Sleep(10);
}