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
	int getScore();
	int getScorenow();
	wchar_t* getUsername();
	wchar_t* getPassword();
	void commitNow();
	void resetNow();
	account * next=NULL;
};

extern std::vector<account*> g_accounts;
extern account* g_player1Account;
extern account* g_player2Account;

//数据的处理
void loadAccounts();
void saveAccounts();

//账户的登录与注册
account* findAccountByName(const wchar_t* name);
account* loginAccount(const wchar_t* name, const wchar_t* pass);
account* registerAccount(const wchar_t* name, const wchar_t* pass);

//登录状态的判定
bool ensurePlayersLoggedIn();

#endif