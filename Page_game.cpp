#include"Page.h"
#include"Player.h"
#include"Account.h"
#include <iostream>
#include<fstream>
#include <cstdlib>
#include <vector>
#include "Initialization.h"

// ===== 棋盘常量 =====
const int WINDOW_SIZE = 600;                            // 窗口尺寸
const int BOARD_SIZE = 19;                              // 棋盘格数（19x19）
const int BOARD_MARGIN = 20;                            // 棋盘边距
const int BOARD_AREA = 400;                             // 棋盘绘制区域尺寸
const int GRID_SIZE = BOARD_AREA / (BOARD_SIZE - 1);   // 每格像素大小

bool isreturn = false;  // 返回标志（暂未使用）

// ===== 游戏状态 =====
int board[BOARD_SIZE][BOARD_SIZE] = { 0 };  // 棋盘数组：0=空, 1=黑子(玩家1), 2=白子(玩家2)
player player1, player2;                     // 两个玩家
bool gameOver = false;                       // 游戏是否结束
int winner = 0;                              // 胜者：0=无, 1=玩家1, 2=玩家2, 3=平局

int winCoords[5][2] = { {0,0} };  // 胜利五连的坐标

// 落子历史记录，用于悔棋功能
struct Move { int x; int y; int color; };
static std::vector<Move> moveHistory;

// ===== 存档功能 =====

// 保存当前棋盘到 Date.text 文件，保存后清空棋盘
void page_game::savegamedate() {
    std::ofstream outFile("Date.text");
    if (!outFile.is_open()) {
        std::cout << "数据保存失败！";
        return;
    }
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            outFile << board[i][j] << " ";
        }
        outFile << std::endl;
    }
    outFile.close();
    // 保存后清空内存中的棋盘
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = 0;
        }
    }
}

// 检查存档文件是否为空（不存在也视为空）
bool page_game::isFileEmpty() {
    std::ifstream fil("Date.text");
    if (!fil) return true;
    return fil.peek() == std::ifstream::traits_type::eof();
}

// 从 Date.text 加载棋盘数据，加载后清空文件
void page_game::loadoldBoard() {
    std::ifstream fin("Date.text", std::ios::in);
    if (!fin) {
        std::cout << "数据存档异常" << std::endl;
        return;
    }
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            fin >> board[i][j];
        }
    }
    fin.close();
    // 加载后清空存档文件（一次性使用）
    std::ofstream("Date.text", std::ios::trunc).close();
}

// ===== 页面绘制 =====

// 绘制游戏页面框架（返回按钮）
void page_game::drawPage() {
    cleardevice();
    settextcolor(RGB(0, 0, 255));
    settextstyle(30, 0, L"微软雅黑");
    outtextxy(230, 540, L"当前：游戏页");

    button btnBack(450, 0, 150, 60, L"返回");
    btnBack.drawButton();
}

// 清空棋盘数组和胜利坐标，重置历史记录
void page_game::cleararr() {
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            board[y][x] = 0;
        }
    }
    for (int i = 0; i < 5; ++i) { winCoords[i][0] = winCoords[i][1] = 0; }
    moveHistory.clear();
}

// 绘制棋盘：背景 + 网格线 + 星位
void page_game::drawBoard() {
    // 棋盘背景（木色）
    setfillcolor(0xEDE4C0);
    solidrectangle(BOARD_MARGIN, BOARD_MARGIN, BOARD_MARGIN + BOARD_AREA, BOARD_MARGIN + BOARD_AREA);

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

    // 绘制星位（天元和四角星）
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

// 初始化游戏状态：清空棋盘、重置玩家位置和活跃状态
void page_game::initGame() {
    cleararr();
    gameOver = false;
    winner = 0;

    // 玩家1：黑子，初始活跃
    player1.cursorX = BOARD_SIZE / 2;
    player1.cursorY = BOARD_SIZE / 2;
    player1.color = 1;
    player1.active = true;

    // 玩家2：白子，初始非活跃
    player2.cursorX = BOARD_SIZE / 2;
    player2.cursorY = BOARD_SIZE / 2;
    player2.color = 2;
    player2.active = false;
}

// 绘制棋子：黑色实心圆或白色空心圆
void page_game::drawStone(int x, int y, int color) {
    int screenX = BOARD_MARGIN + x * GRID_SIZE;
    int screenY = BOARD_MARGIN + y * GRID_SIZE;

    if (color == 1) {  // 黑子
        setfillcolor(BLACK);
        solidcircle(screenX, screenY, GRID_SIZE / 2 - 2);
    }
    else if (color == 2) {  // 白子（加黑色边框）
        setfillcolor(WHITE);
        solidcircle(screenX, screenY, GRID_SIZE / 2 - 2);
        setlinecolor(BLACK);
        circle(screenX, screenY, GRID_SIZE / 2 - 2);
    }
}

// 绘制胜利高亮：在胜利五连位置画金色双圈
void page_game::drawHighlight(int x, int y) {
    int screenX = BOARD_MARGIN + x * GRID_SIZE;
    int screenY = BOARD_MARGIN + y * GRID_SIZE;
    setlinestyle(PS_SOLID, 2);
    setlinecolor(RGB(255, 215, 0));  // 金色
    circle(screenX, screenY, GRID_SIZE / 2 + 3);
    circle(screenX, screenY, GRID_SIZE / 2 + 5);
}

// 绘制光标：在当前活跃玩家的光标位置画矩形框
void page_game::drawCursor(int x, int y, int color) {
    int screenX = BOARD_MARGIN + x * GRID_SIZE;
    int screenY = BOARD_MARGIN + y * GRID_SIZE;

    setlinecolor(color);
    setlinestyle(PS_SOLID, 2);
    rectangle(screenX - GRID_SIZE / 2 + 2, screenY - GRID_SIZE / 2 + 2,
              screenX + GRID_SIZE / 2 - 2, screenY + GRID_SIZE / 2 - 2);
}

// ===== 游戏逻辑 =====

// 落子：在光标位置放置棋子，记录到历史
bool page_game::placeStone(player& player) {
    if (board[player.cursorY][player.cursorX] != 0) {
        return false;  // 位置已有棋子
    }
    drawStone(player.cursorX, player.cursorY, player.color);
    board[player.cursorY][player.cursorX] = player.color;
    moveHistory.push_back({ player.cursorX, player.cursorY, player.color });
    return true;
}

// 检查是否五连：遍历四个方向（水平、垂直、两条对角线）
bool page_game::checkWin(int playerColor) {
    const int directions[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };

    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            if (board[y][x] != playerColor) continue;

            for (int d = 0; d < 4; d++) {
                int dx = directions[d][0];
                int dy = directions[d][1];

                // 正方向计数
                int count_forward = 0;
                for (int i = 1; i < 5; i++) {
                    int nx = x + dx * i;
                    int ny = y + dy * i;
                    if (nx < 0 || nx >= BOARD_SIZE || ny < 0 || ny >= BOARD_SIZE) break;
                    if (board[ny][nx] == playerColor) count_forward++;
                    else break;
                }

                // 反方向计数
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
                    // 记录胜利五连的起始坐标
                    int startX = x - dx * count_back;
                    int startY = y - dy * count_back;
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

// 检查是否平局（棋盘已满）
bool page_game::istie() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) { return false; }
        }
    }
    return true;
}

// 绘制游戏状态信息：玩家操作提示、胜负结果
void page_game::drawGameStatus() {
    settextstyle(20, 0, _T("黑体"));

    // 玩家1状态（活跃时红色高亮）
    settextcolor(player1.active ? RED : BLACK);
    outtextxy(BOARD_AREA + 40, 70, _T("玩家1 (黑色)"));
    outtextxy(BOARD_AREA + 40, 100, _T("操作: WASD移动"));
    outtextxy(BOARD_AREA + 40, 130, _T("F键落子"));

    // 玩家2状态（活跃时蓝色高亮）
    settextcolor(player2.active ? BLUE : BLACK);
    outtextxy(BOARD_AREA + 40, 170, _T("玩家2 (白色)"));
    outtextxy(BOARD_AREA + 40, 200, _T("操作: 方向键移动"));
    outtextxy(BOARD_AREA + 40, 230, _T("0键落子"));

    if (gameOver) {
        // 重绘所有棋子
        for (int y = 0; y < BOARD_SIZE; y++) {
            for (int x = 0; x < BOARD_SIZE; x++) {
                if (board[y][x] != 0) {
                    drawStone(x, y, board[y][x]);
                }
            }
        }
        // 绘制胜利高亮
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

        // 弹出胜负/平局对话框，选择是否再来一局
        if (winner == 1) {
            int result = MessageBox(GetHWnd(), _T("玩家1胜！"), _T("是否再来一局？"), MB_ICONQUESTION | MB_YESNO);
            if (result == IDYES) { initGame(); }  // 重新初始化游戏
        }
        else if (winner == 2) {
            int result = MessageBox(GetHWnd(), _T("玩家2胜！"), _T("是否再来一局？"), MB_ICONQUESTION | MB_YESNO);
            if (result == IDYES) { initGame(); }
        }
        else if (winner == 3) {
            int result = MessageBox(GetHWnd(), _T("平局！"), _T("是否再来一局？"), MB_ICONQUESTION | MB_YESNO);
            if (result == IDYES) { initGame(); }
        }
    }
    else {
        settextcolor(BLACK);
        outtextxy(BOARD_AREA + 40, 250, _T("游戏进行中..."));
        outtextxy(BOARD_AREA + 40, 280, _T("ESC键退出"));
    }
}

// ===== 游戏主循环 =====
void page_game::Run() {
    initGame();

    // 检查是否有存档，提示是否继续
    if (isFileEmpty()) {
        Sleep(10);
    }
    else {
        int result = MessageBox(GetHWnd(), _T("检测到存档"), _T("是否继续游戏？"), MB_ICONQUESTION | MB_YESNO);
        if (result == IDYES) {
            loadoldBoard();
        }
    }

    ExMessage msg;
    BeginBatchDraw();
    while (!gameOver) {
        // 每帧重绘：页面框架 + 棋盘 + 棋子 + 光标 + 状态
        drawPage();
        drawBoard();

        for (int y = 0; y < BOARD_SIZE; y++) {
            for (int x = 0; x < BOARD_SIZE; x++) {
                if (board[y][x] != 0) {
                    drawStone(x, y, board[y][x]);
                }
            }
        }

        if (player1.active) {
            drawCursor(player1.cursorX, player1.cursorY, RED);
        }
        else {
            drawCursor(player2.cursorX, player2.cursorY, BLUE);
        }

        drawGameStatus();

        // 检查平局
        if (istie()) {
            gameOver = true;
            winner = 3;
        }

        // 处理输入消息
        if (peekmessage(&msg, EX_MOUSE | EX_KEY)) {
            // 鼠标点击返回按钮
            if (msg.message == WM_LBUTTONDOWN) {
                if (msg.x >= 450 && msg.x <= 600 && msg.y >= 0 && msg.y <= 60) {
                    int result = MessageBox(GetHWnd(), _T("确认要返回主菜单？"), _T("返回确认"), MB_ICONQUESTION | MB_YESNO);
                    if (result == IDYES) {
                        savegamedate();     // 保存当前棋盘
                        flushmessage(EX_MOUSE);
                        flushmessage(EX_KEY);
                        cleararr();
                        gameOver = false;
                        winner = 0;
                        initGame();
                        currentPage = PAGE_MENU;
                        break;  // 退出游戏循环，返回主菜单
                    }
                }
            }

            if (msg.message == WM_KEYDOWN) {
                // Backspace 悔棋
                if (msg.vkcode == VK_BACK) {
                    if (!moveHistory.empty()) {
                        Move last = moveHistory.back();
                        moveHistory.pop_back();
                        // 恢复棋盘
                        if (last.y >= 0 && last.y < BOARD_SIZE && last.x >= 0 && last.x < BOARD_SIZE) {
                            board[last.y][last.x] = 0;
                        }
                        // 切换活跃玩家
                        if (last.color == 1) {
                            player1.active = true;
                            player2.active = false;
                        } else {
                            player1.active = false;
                            player2.active = true;
                        }
                        // 光标回到悔棋位置
                        player1.cursorX = last.x; player1.cursorY = last.y;
                        player2.cursorX = last.x; player2.cursorY = last.y;
                        gameOver = false;
                        winner = 0;
                        for (int i = 0; i < 5; ++i) { winCoords[i][0] = winCoords[i][1] = 0; }
                        // 重绘画面
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

                // ===== 玩家1操作：WASD移动 + F落子 =====
                if (player1.active) {
                    switch (msg.vkcode) {
                    case 'W':
                        if (player1.cursorY - 1 >= 0) player1.cursorY--;
                        break;
                    case 'S':
                        if (player1.cursorY + 1 < BOARD_SIZE) player1.cursorY++;
                        break;
                    case 'A':
                        if (player1.cursorX - 1 >= 0) player1.cursorX--;
                        break;
                    case 'D':
                        if (player1.cursorX + 1 < BOARD_SIZE) player1.cursorX++;
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
                                // 更新排行榜
                                if (g_player1Account) updateRankingAfterWin(g_player1Account);
                            }
                        }
                        break;
                    }
                }

                // ===== 玩家2操作：方向键移动 + 0落子 =====
                if (player2.active) {
                    switch (msg.vkcode) {
                    case VK_UP:
                        if (player2.cursorY - 1 >= 0) player2.cursorY--;
                        break;
                    case VK_DOWN:
                        if (player2.cursorY + 1 < BOARD_SIZE) player2.cursorY++;
                        break;
                    case VK_LEFT:
                        if (player2.cursorX - 1 >= 0) player2.cursorX--;
                        break;
                    case VK_RIGHT:
                        if (player2.cursorX + 1 < BOARD_SIZE) player2.cursorX++;
                        break;
                    case '0':
                        if (placeStone(player2)) {
                            player2.active = false;
                            player1.active = true;
                            if (checkWin(player2.color)) {
                                gameOver = true;
                                winner = 2;
                                // 更新排行榜
                                if (g_player2Account) updateRankingAfterWin(g_player2Account);
                            }
                        }
                        break;
                    }
                }

                // ESC键退出游戏
                if (msg.vkcode == VK_ESCAPE) {
                    int result = MessageBox(GetHWnd(), _T("确认要退出游戏？"), _T("退出确认"), MB_ICONQUESTION | MB_YESNO);
                    if (result == IDYES) {
                        flushmessage(EX_MOUSE);
                        flushmessage(EX_KEY);
                        EndBatchDraw();
                        exit(0);
                    }
                }
                drawGameStatus();
                flushmessage(EX_KEY);  // 清空键盘消息队列，防止按键堆积
            }
        }

        FlushBatchDraw();
        Sleep(20);  // 控制帧率，降低CPU占用
    }

    EndBatchDraw();

    // 如果是返回菜单，直接退出
    if (currentPage == PAGE_MENU) {
        flushmessage(EX_MOUSE);
        flushmessage(EX_KEY);
        return;
    }

    // 游戏结束后：重绘最终棋盘 + 胜利高亮
    drawBoard();
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
    FlushBatchDraw();

    // 等待ESC退出
    while (peekmessage(&msg, EX_KEY) && msg.vkcode != VK_ESCAPE) {
        flushmessage(EX_KEY);
    }
}