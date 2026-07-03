#include"Account.h"

#ifndef Player
#define Player

// 玩家结构体，存储光标位置、棋子颜色、是否活跃以及关联的账户
struct player {
    int cursorX, cursorY;   // 光标在棋盘上的坐标
    int color;              // 棋子颜色：1=黑子，2=白子
    bool active;            // 是否为当前活跃玩家（轮到该玩家落子）

    account * PLAYER=NULL;  // 关联的账户指针
};

#endif