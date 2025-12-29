#include "Page.h"
#include "Account.h"

void page_rank::drawPage() {
    cleardevice();
    settextcolor(RGB(0, 0, 255));
    settextstyle(30, 0, L"微软雅黑");
    outtextxy(230, 540, L"排名页");

    // 标题
    settextstyle(24, 0, L"宋体");
    outtextxy(50, 20, L"排行榜（按总分降序）");

    // 绘制返回按钮
    button btnBack(450, 0, 150, 60, L"返回");
    btnBack.drawButton();

    // 绘制排行榜，使用链表 g_rankHead
    int y = 80;
    int idx = 1;
    account* cur = g_rankHead;
    while (cur && y < 520) {
        wchar_t buf[256];
        swprintf(buf, 256, L"%d. %ls - %d", idx, cur->getUsername(), cur->getScore());
        outtextxy(50, y, buf);
        y += 30;
        idx++;
        cur = cur->next;
    }
}
