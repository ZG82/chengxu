#include <cwchar>
#include <vector>

#ifndef Account
#define Account

// 账户类，存储用户名、密码和累计得分
class account {
private:
	wchar_t username[50];    // 用户名
	wchar_t password[50];    // 密码
	int playersocer;         // 累计总分（已提交）
	int playersocernow;      // 当前会话得分（未提交）

public:
	account(const wchar_t* user, const wchar_t* pass, int score = 0) : playersocer(score), playersocernow(0) {
		wcscpy_s(username, user);
		wcscpy_s(password, pass);
	}
	void add();              // 累计总分+1
	void addnow();           // 当前会话得分+1
	int getScore() const;    // 获取累计总分
	int getScorenow() const; // 获取当前会话得分
	const wchar_t* getUsername() const;
	const wchar_t* getPassword() const;
	void commitNow();        // 将会话得分提交到累计总分
	void resetNow();         // 重置会话得分
	account * next=NULL;     // 链表指针，用于排行榜排序
};

// 全局账户列表
extern std::vector<account*> g_accounts;
extern account* g_player1Account;   // 玩家1的账户
extern account* g_player2Account;   // 玩家2的账户

// 排行榜链表头指针（按总分降序排列）
extern account* g_rankHead;

// 从文件加载账户数据
void loadAccounts();
// 保存账户数据到文件
void saveAccounts();

// 重建排行榜链表（按总分降序），返回链表头指针
account* rebuildRankList();

// 某账户获胜后更新排行榜
void updateRankingAfterWin(account* winner);

// 按用户名查找账户
account* findAccountByName(const wchar_t* name);
// 登录账户（验证用户名和密码）
account* loginAccount(const wchar_t* name, const wchar_t* pass);
// 注册新账户
account* registerAccount(const wchar_t* name, const wchar_t* pass);

// 确保两个玩家都已登录，未登录则弹出登录/注册对话框
bool ensurePlayersLoggedIn();

#endif