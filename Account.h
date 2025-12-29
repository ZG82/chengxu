#include <corecrt_wstring.h>
#include <vector>

#ifndef Account
#define Account

class account {
private:
	wchar_t username[50];
	wchar_t password[50];
	int playersocer;
	int playersocernow;
public:
	account(const wchar_t* user, const wchar_t* pass, int score = 0) : playersocer(score), playersocernow(0) {
		wcscpy_s(username, user);
		wcscpy_s(password, pass);
	}
	void add();
	void addnow();
	int getScore() const;
	int getScorenow() const;
	const wchar_t* getUsername() const;
	const wchar_t* getPassword() const;
	void commitNow();
	void resetNow();
	account * next=NULL;
};

extern std::vector<account*> g_accounts;
extern account* g_player1Account;
extern account* g_player2Account;

// 链表形式的排行榜头指针
extern account* g_rankHead;

// 数据的处理
void loadAccounts();
void saveAccounts();

// 通过链表重建排行榜（按 playersocer 降序），返回头指针
account* rebuildRankList();

// 当某账户获胜后更新分数并重建排行榜
void updateRankingAfterWin(account* winner);

// 账户的登录与注册
account* findAccountByName(const wchar_t* name);
account* loginAccount(const wchar_t* name, const wchar_t* pass);
account* registerAccount(const wchar_t* name, const wchar_t* pass);

// 登录状态的判定
bool ensurePlayersLoggedIn();

#endif