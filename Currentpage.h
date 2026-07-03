#ifndef Currentpage
#define Currentpage

// 页面枚举，用于标识当前显示的页面
enum Pages {
    PAGE_MENU,      // 主菜单页
    PAGE_GAME,      // 游戏页
    PAGE_SETTING,   // 设置页
    PAGE_SAVE,      // 存档/帮助页
    PAGE_RANK,      // 排行榜页
};

// 当前页面状态，在 Mouse.h 中定义
extern Pages currentPage;

#endif