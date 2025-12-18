#include"Page.h"
#include"Player.h"
#include <iostream>
#include "Initialization.h"



const int WINDOW_SIZE = 600;         // 窗口尺寸
const int BOARD_SIZE = 19;           // 棋盘格子数
const int BOARD_MARGIN = 20;         // 棋盘边距
const int BOARD_AREA = 400;          // 棋盘区域尺寸
const int GRID_SIZE = BOARD_AREA / (BOARD_SIZE - 1); // 格子尺寸


int board[BOARD_SIZE][BOARD_SIZE] = { 0 }; // 0=空, 1=玩家1, 2=玩家2
player player1, player2;
bool gameOver = false;
int winner = 0;

//变量的声明
////////////////////////////////////////////////////////////////////////////////////////////////////////


void page_game::drawPage() {
    cleardevice();
    settextcolor(RGB(0, 0, 255));                     //调整窗口大小之后文字需要重新填写坐标
    settextstyle(30, 0, L"微软雅黑");
    outtextxy(230, 540, L"五子棋游戏页");

    button btnBack(450, 0, 150, 60, L"返回");

    btnBack.drawButton();
}

/// <summary>
/// ////////////////////////////////////////////////////////////////////////////////////////////////////////
/// </summary>
void page_game::cleararr() {
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            board[y][x] = 0;
        }
    }
}

/// <summary>
/// /////////////////////////////////////////////////////////////////////////////////////////////////
/// </summary>

void page_game::drawBoard() {
    // 绘制棋盘背景 (浅黄色)
    setfillcolor(0xEDE4C0);
    solidrectangle(BOARD_MARGIN, BOARD_MARGIN, BOARD_MARGIN + BOARD_AREA, BOARD_MARGIN + BOARD_AREA);

    // 绘制网格线
    setlinecolor(BLACK);
    setlinestyle(PS_SOLID, 1);

    // 绘制横线
    for (int i = 0; i < BOARD_SIZE; i++) {
        int y = BOARD_MARGIN + i * GRID_SIZE;
        line(BOARD_MARGIN, y, BOARD_MARGIN + BOARD_AREA, y);
    }

    // 绘制竖线
    for (int i = 0; i < BOARD_SIZE; i++) {
        int x = BOARD_MARGIN + i * GRID_SIZE;
        line(x, BOARD_MARGIN, x, BOARD_MARGIN + BOARD_AREA);
    }

    // 绘制棋盘上的五个点
    setfillcolor(BLACK);
    int starPoints[5][2] = {
        {3, 3}, {3, BOARD_SIZE - 4}, {BOARD_SIZE - 4, 3},
        {BOARD_SIZE - 4, BOARD_SIZE - 4}, {BOARD_SIZE / 2, BOARD_SIZE / 2}
    };

    for (int i = 0; i < 5; i++) {
        int x = BOARD_MARGIN + starPoints[i][0] * GRID_SIZE;
        int y = BOARD_MARGIN + starPoints[i][1] * GRID_SIZE;
        solidcircle(x, y, 4);
    }
}
/// <summary>
/// ////////////////////////////////////////////////////////////////////////////////////////////////////////
/// </summary>
void page_game::initGame() {
    // 初始化玩家1
    player1.cursorX = BOARD_SIZE / 2;
    player1.cursorY = BOARD_SIZE / 2;
    player1.color = 1;
    player1.active = true;

    // 初始化玩家2
    player2.cursorX = BOARD_SIZE / 2;
    player2.cursorY = BOARD_SIZE / 2;
    player2.color = 2;
    player2.active = false;
}
/// <summary>
/// ////////////////////////////////////////////////////////////////////////////////////////////////////////
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="color"></param>
void page_game::drawStone(int x, int y, int color) {
    int screenX = BOARD_MARGIN + x * GRID_SIZE;
    int screenY = BOARD_MARGIN + y * GRID_SIZE;

    if (color == 1) { // 黑色棋子
        setfillcolor(BLACK);
        solidcircle(screenX, screenY, GRID_SIZE / 2 - 2);
    }
    else if (color == 2) { // 白色棋子
        setfillcolor(WHITE);
        solidcircle(screenX, screenY, GRID_SIZE / 2 - 2);
        setlinecolor(BLACK);
        circle(screenX, screenY, GRID_SIZE / 2 - 2);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// 绘制光标
void page_game::drawCursor(int x, int y, int color) {
    int screenX = BOARD_MARGIN + x * GRID_SIZE;
    int screenY = BOARD_MARGIN + y * GRID_SIZE;

    setlinecolor(color);
    setlinestyle(PS_SOLID, 2);
    rectangle(screenX - GRID_SIZE / 2 + 2, screenY - GRID_SIZE / 2 + 2,screenX + GRID_SIZE / 2 - 2, screenY + GRID_SIZE / 2 - 2);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// 放置棋子
bool page_game::placeStone(player& player) {
    if (board[player.cursorY][player.cursorX] != 0) {
        return false; // 位置已有棋子
    }
    drawStone(player.cursorX, player.cursorY, player.color);
    board[player.cursorY][player.cursorX] = player.color;
    return true;
}

/// <summary>
/// //////////////////////////////////////////////////////////////////////////////////////////////////////////
/// </summary>
/// <param name="playerColor"></param>
/// <returns></returns>
bool page_game::checkWin(int playerColor) {
    // 检查方向：水平、垂直、两个对角线
    const int directions[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };

    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            if (board[y][x] != playerColor) continue;

            for (int d = 0; d < 4; d++) {
                int count = 1;
                int dx = directions[d][0];
                int dy = directions[d][1];

                // 正方向检查
                for (int i = 1; i < 5; i++) {
                    int nx = x + dx * i;
                    int ny = y + dy * i;
                    if (nx < 0 || nx >= BOARD_SIZE || ny < 0 || ny >= BOARD_SIZE) break;
                    if (board[ny][nx] == playerColor) count++;
                    else break;
                }

                // 反方向检查
                for (int i = 1; i < 5; i++) {
                    int nx = x - dx * i;
                    int ny = y - dy * i;
                    if (nx < 0 || nx >= BOARD_SIZE || ny < 0 || ny >= BOARD_SIZE) break;
                    if (board[ny][nx] == playerColor) count++;
                    else break;
                }

                if (count >= 5) return true;
            }
        }
    }
    return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void page_game::drawGameStatus() {
    settextstyle(20, 0, _T("宋体"));

    // 绘制玩家1状态
    settextcolor(player1.active ? RED : BLACK);
    outtextxy(BOARD_AREA + 40, 70, _T("玩家1 (黑色)"));
    outtextxy(BOARD_AREA + 40, 100, _T("控制: WASD移动"));
    outtextxy(BOARD_AREA + 40, 130, _T("F键落子"));

    // 绘制玩家2状态
    settextcolor(player2.active ? BLUE : BLACK);
    outtextxy(BOARD_AREA + 40, 170, _T("玩家2 (白色)"));
    outtextxy(BOARD_AREA + 40, 200, _T("控制: 方向键移动"));
    outtextxy(BOARD_AREA + 40, 230, _T("0键落子"));

    // 绘制游戏状态
    if (gameOver) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            for (int x = 0; x < BOARD_SIZE; x++) {
                if (board[y][x] != 0) {
                    drawStone(x, y, board[y][x]);
                }
            }
        }
        if (winner==1) {
            // 弹出确认对话框
            int result = MessageBox(
                GetHWnd(),
                _T("玩家1胜利！"),
                _T("再来一把"),
                MB_ICONQUESTION | MB_YESNO
            );
            if (result == IDYES) {
                cleararr();
                gameOver = false;
            }
        }
        else {
            // 弹出确认对话框
            int result = MessageBox(
                GetHWnd(),
                _T("玩家2胜利！"),
                _T("是否再来一把？"),
                MB_ICONQUESTION | MB_YESNO
            );
            if (result == IDYES) {
                cleararr();
                gameOver = false;
            }
        }
    }
    else {
        settextcolor(BLACK);
        outtextxy(BOARD_AREA + 40, 250, _T("游戏进行中..."));
        outtextxy(BOARD_AREA + 40, 280, _T("ESC键退出"));
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void page_game::Run() {
    //initgraph(WINDOW_SIZE, WINDOW_SIZE);

    // 设置窗口背景色
    //setbkcolor(WHITE);
    //cleardevice();

    initGame();

    // 消息处理变量
    ExMessage msg;
    ExMessage msg0;

    BeginBatchDraw();
    while (!gameOver) {
        // 绘制棋盘
        drawBoard();

        // 绘制所有已有棋子
        for (int y = 0; y < BOARD_SIZE; y++) {
            for (int x = 0; x < BOARD_SIZE; x++) {
                if (board[y][x] != 0) {
                    drawStone(x, y, board[y][x]);
                }
            }
        }

        // 绘制光标
        if (player1.active) {
            drawCursor(player1.cursorX, player1.cursorY, RED);
        }
        else {
            drawCursor(player2.cursorX, player2.cursorY, BLUE);
        }

        // 绘制游戏状态
        drawGameStatus();

      //判断返回
      
      //if (peekmessage(&msg0, EX_MOUSE)) {
      //    if (msg0.x >= 420 && msg0.x <= 600 && msg0.y >= 0 && msg0.y <= 60 && msg0.message == WM_LBUTTONDOWN) {
      //        int result = MessageBox(
      //            GetHWnd(),
      //            _T("提示"),
      //            _T("确定退出吗？"),
      //            MB_ICONQUESTION | MB_YESNO
      //        );
      //        if (result == IDYES) {
      //            P11.drawPage();
      //            cleararr();
      //            gameOver = true;
      //        }
      //        currentPage = PAGE_MENU;
      //        FlushBatchDraw(); // 刷新绘图缓冲区 
      //    }
      //}
        // 处理键盘输入
        if (peekmessage(&msg, EX_KEY)) {
            if (msg.message == WM_KEYDOWN) {
////////////////// 玩家1控制 (WASD + F)
                if (player1.active) {
                    switch (msg.vkcode) {
                    case 'W':
                        if (player1.cursorY - 1 >= 0) {
                            player1.cursorY = player1.cursorY - 1;
                        }
                        break;
                    case 'S':
                        if (player1.cursorY + 1 < BOARD_SIZE) {
                            player1.cursorY = player1.cursorY + 1;
                        }
                        break;
                    case 'A':
                        if (player1.cursorX - 1 >= 0) {
                            player1.cursorX = player1.cursorX - 1;
                        }
                        break;
                    case 'D':
                        if (player1.cursorX + 1 < BOARD_SIZE) {
                            player1.cursorX = player1.cursorX + 1;
                        }
                        break;
                    case 'F':
                        if (placeStone(player1)) { 
                            player1.active = false;
                            player2.active = true;
                            if (checkWin(player1.color)) {
                                gameOver = true;
                                winner = 1;
                                player1.active = true;
                                player2.active = false;
                            }
                           
                        }
                        break;
                    }
                }
//////////////////玩家1控制结束

//////////////////玩家2控制 (方向键 + 0)
                if (player2.active) {
                    switch (msg.vkcode) {
                    case VK_UP:
                        if (player2.cursorY - 1 >= 0) {
                            player2.cursorY = player2.cursorY - 1;
                        }
                        break;
                    case VK_DOWN:
                        if (player2.cursorY + 1 < BOARD_SIZE) {
                            player2.cursorY = player2.cursorY + 1;
                        }
                        break;
                    case VK_LEFT:
                        if (player2.cursorX - 1 >= 0) {
                            player2.cursorX = player2.cursorX - 1;
                        }
                        break;
                    case VK_RIGHT:
                        if (player2.cursorX + 1 < BOARD_SIZE) {
                            player2.cursorX = player2.cursorX + 1;
                        }
                        break;
                    case '0':
                        if (placeStone(player2)) {
                            player2.active = false;
                            player1.active = true;
                            if (checkWin(player2.color)) {
                                gameOver = true;
                                winner = 2;
                            }
                           
                        }
                        break;
                    }
                }
/////////////////玩家2控制结束
                // 处理窗口关闭
                if (msg.vkcode == VK_ESCAPE) {
                    gameOver = true;
                }
                drawGameStatus();
                // 清除消息
                flushmessage(EX_KEY);
            }
        }

        FlushBatchDraw();
        Sleep(20); // 减少CPU占用
    }
    //游戏while结束，gameover发生

    EndBatchDraw();

    // 最终绘制一次胜利信息
    drawBoard();
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            if (board[y][x] != 0) {
                drawStone(x, y, board[y][x]);
            }
        }
    }
    FlushBatchDraw();

    // 等待退出
    while (peekmessage(&msg, EX_KEY) && msg.vkcode != VK_ESCAPE) {
        flushmessage(EX_KEY);
    }

    //closegraph();
}