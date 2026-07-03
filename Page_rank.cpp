#include "Page.h"
#include "Account.h"

// 绘制排行榜页面：按总分降序显示所有账户
void page_rank::drawPage() {
    cleardevice();
    settextcolor(RGB(0, 0, 255));
    settextstyle(30, 0, L"微软雅黑");
    outtextxy(230, 540, L"排行榜页");

    settextstyle(24, 0, L"黑体");
    outtextxy(50, 20, L"排行榜（按总分降序）");

    button btnBack(450, 0, 150, 60, L"返回");
    btnBack.drawButton();

    // 遍历排行榜链表，显示排名、用户名和得分
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