#ifndef Player
#define Player

struct player {
    int cursorX, cursorY;  // 光标位置
    int color;             // 棋子颜色
    bool active;           // 是否轮到此玩家
};

#endif
