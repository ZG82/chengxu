#include"Page.h"
#include"Player.h"
#include"Account.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include "Initialization.h"



const int WINDOW_SIZE = 600;         // 窗口尺寸
const int BOARD_SIZE = 19;           // 棋盘格子数
const int BOARD_MARGIN = 20;         // 棋盘边距
const int BOARD_AREA = 400;          // 棋盘区域尺寸
const int GRID_SIZE = BOARD_AREA / (BOARD_SIZE - 1); // 格子尺寸

bool isreturn = false;


int board[BOARD_SIZE][BOARD_SIZE] = { 0 }; // 0=空, 1=玩家1, 2=玩家2
player player1, player2;
bool gameOver = false;
int winner = 0;

int winCoords[5][2] = { {0,0} };

struct Move { int x; int y; int color; };
static std::vector<Move> moveHistory;

//变量的声明
////////////////////////////////////////////////////////////////////////////////////////////////////////

void page_game::sign_in() {
    
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

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
    for (int i = 0; i < 5; ++i) { winCoords[i][0] = winCoords[i][1] = 0; }
    moveHistory.clear();
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

// 胜利光标绘制
void page_game::drawHighlight(int x, int y) {
    int screenX = BOARD_MARGIN + x * GRID_SIZE;
    int screenY = BOARD_MARGIN + y * GRID_SIZE;
    setlinestyle(PS_SOLID, 2);
    setlinecolor(RGB(255, 215, 0));
    circle(screenX, screenY, GRID_SIZE / 2 + 3);
    circle(screenX, screenY, GRID_SIZE / 2 + 5);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// 绘制光标
void page_game::drawCursor(int x, int y, int color) {
    int screenX = BOARD_MARGIN + x * GRID_SIZE;
    int screenY = BOARD_MARGIN + y * GRID_SIZE;

    setlinecolor(color);
    setlinestyle(PS_SOLID, 2);
    rectangle(screenX - GRID_SIZE / 2 + 2, screenY - GRID_SIZE / 2 + 2, screenX + GRID_SIZE / 2 - 2, screenY + GRID_SIZE / 2 - 2);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// 放置棋子
bool page_game::placeStone(player& player) {
    if (board[player.cursorY][player.cursorX] != 0) {
        return false; // 位置已有棋子
    }
    drawStone(player.cursorX, player.cursorY, player.color);
    board[player.cursorY][player.cursorX] = player.color;
    moveHistory.push_back({ player.cursorX, player.cursorY, player.color });
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
                int dx = directions[d][0];
                int dy = directions[d][1];

                int count_forward = 0;
                for (int i = 1; i < 5; i++) {
                    int nx = x + dx * i;
                    int ny = y + dy * i;
                    if (nx < 0 || nx >= BOARD_SIZE || ny < 0 || ny >= BOARD_SIZE) break;
                    if (board[ny][nx] == playerColor) count_forward++;
                    else break;
                }

                int count_back = 0;
                for (int i = 1; i < 5; i++) {
                    int nx = x - dx * i;
                    int ny = y - dy * i;
                    if (nx < 0 || nx >= BOARD_SIZE || ny < 0 || ny >= BOARD_SIZE) break;
                    if (board[ny][nx] == playerColor) count_back++;
                    else break;
                }

                int total = 1 + count_forward + count_back;
                if (total >= 5) {
                    // compute starting coordinate of the sequence
                    int startX = x - dx * count_back;
                    int startY = y - dy * count_back;
                    // store exactly five positions
                    for (int i = 0; i < 5; i++) {
                        winCoords[i][0] = startX + dx * i;
                        winCoords[i][1] = startY + dy * i;
                    }
                    return true;
                }
            }
        }
    }
    return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool page_game::istie() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) { return false; }
        }
    }
    return true;
}
/// <summary>
/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// </summary>
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
        if (winner == 1 || winner == 2) {
            for (int i = 0; i < 5; ++i) {
                int wx = winCoords[i][0];
                int wy = winCoords[i][1];
                if (wx >= 0 && wx < BOARD_SIZE && wy >= 0 && wy < BOARD_SIZE) {
                    drawHighlight(wx, wy);
                }
            }
        }
        if (gameOver && (winner == 1 || winner == 2 || winner == 3)) {
            FlushBatchDraw();
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
        else if(winner==2){
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
        else if (winner == 3) {
            // 弹出确认对话框
            int result = MessageBox(
                GetHWnd(),
                _T("平局"),
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
    initGame();

    // 消息处理变量
    ExMessage msg;
    ExMessage msg0;
    BeginBatchDraw();
    while (!gameOver) {
        // 绘制页面顶部与返回按钮，先清空屏幕的一部分并显示页眉
        drawPage();
        
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

        // 判断平局
        if (istie()) {
            gameOver = true;
            winner = 3;
        }

        // 处理键盘和鼠标输入
        if (peekmessage(&msg, EX_MOUSE | EX_KEY)) {
            // 处理鼠标返回按钮
            if (msg.message == WM_LBUTTONDOWN) {
                if (msg.x >= 450 && msg.x <= 600 && msg.y >= 0 && msg.y <= 60) {
                    // 弹出确认对话框
                    int result = MessageBox(
                        GetHWnd(),
                        _T("确认要返回主菜单吗？"),
                        _T("返回确认"),
                        MB_ICONQUESTION | MB_YESNO
                    );
                    if (result == IDYES) {
                        // 清除其他挂起的消息，避免回到菜单后被遗留的鼠标事件触发
                        flushmessage(EX_MOUSE);
                        flushmessage(EX_KEY);
                        // 重置游戏状态，清除棋盘，避免返回后棋盘残留
                        cleararr();
                        gameOver = false;
                        winner = 0;
                        initGame();
                        // 返回菜单（不要在这里绘制菜单，由外层主循环负责重绘）
                        currentPage = PAGE_MENU;
                        break; // 退出Run，回到外层消息循环
                    }
                    // 否则继续游戏
                }
            }

            if (msg.message == WM_KEYDOWN) {
                if (msg.vkcode == VK_BACK) {
                    if (!moveHistory.empty()) {
                        Move last = moveHistory.back();
                        moveHistory.pop_back();
                        if (last.y >= 0 && last.y < BOARD_SIZE && last.x >= 0 && last.x < BOARD_SIZE) {
                            board[last.y][last.x] = 0;
                        }
                        if (last.color == 1) {
                            player1.active = true;
                            player2.active = false;
                        } else {
                            player1.active = false;
                            player2.active = true;
                        }
                        player1.cursorX = last.x; player1.cursorY = last.y;
                        player2.cursorX = last.x; player2.cursorY = last.y;
                        gameOver = false;
                        winner = 0;
                        for (int i = 0; i < 5; ++i) { winCoords[i][0] = winCoords[i][1] = 0; }
                        drawBoard();
                        for (int yy = 0; yy < BOARD_SIZE; yy++) {
                            for (int xx = 0; xx < BOARD_SIZE; xx++) {
                                if (board[yy][xx] != 0) drawStone(xx, yy, board[yy][xx]);
                            }
                        }
                        if (player1.active) drawCursor(player1.cursorX, player1.cursorY, RED);
                        else drawCursor(player2.cursorX, player2.cursorY, BLUE);
                        drawGameStatus();
                        FlushBatchDraw();
                    }
                    flushmessage(EX_KEY);
                    continue;
                }

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
                // 处理窗口关闭或返回菜单
                if (msg.vkcode == VK_ESCAPE) {
                    // 弹出确认对话框，确认是否退出程序
                    int result = MessageBox(
                        GetHWnd(),
                        _T("确认要退出程序吗？"),
                        _T("退出确认"),
                        MB_ICONQUESTION | MB_YESNO
                    );
                    if (result == IDYES) {
                        // 直接退出程序
                        // 清理可能的消息
                        flushmessage(EX_MOUSE);
                        flushmessage(EX_KEY);
                        EndBatchDraw();
                        exit(0);
                    }
                    // 否则继续游戏
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

    // 如果用户在游戏中选择返回菜单，清理残留消息并返回，让外层主循环负责重绘主菜单
    if (currentPage == PAGE_MENU) {
        // 清理残留消息
        flushmessage(EX_MOUSE);
        flushmessage(EX_KEY);
        return;
    }

    // 最终绘制一次胜利信息
    drawBoard();
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            if (board[y][x] != 0) {
                drawStone(x, y, board[y][x]);
            }
        }
    }
   //绘制胜利光圈
    if (winner == 1 || winner == 2) {
        for (int i = 0; i < 5; ++i) {
            int wx = winCoords[i][0];
            int wy = winCoords[i][1];
            if (wx >= 0 && wx < BOARD_SIZE && wy >= 0 && wy < BOARD_SIZE) {
                drawHighlight(wx, wy);
            }
        }
    }
    FlushBatchDraw();

    // 等待退出
    while (peekmessage(&msg, EX_KEY) && msg.vkcode != VK_ESCAPE) {
        flushmessage(EX_KEY);
    }
}