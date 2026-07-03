#include"Mouse.h"

using namespace std;

int main() {
    Sleep(500);
    cout << "正在加载游戏资源..."<<endl;
    Sleep(500);
    cout << "正在初始化移动控制..."<<endl;
    Sleep(500);
    cout << "正在启动游戏..."<<endl;
    Sleep(500);
    start GoBang;   // 创建窗口（调用Initialization构造函数）
    Sleep(500);
    run();           // 进入主消息循环（Mouse.h中定义）
    Sleep(10);
}