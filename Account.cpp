#include "Account.h"
#include <easyx.h>
#include <tchar.h>
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <cstring>
#include <string>
#include <sstream>

//使用指针来提升账户的管理性能
std::vector<account*> g_accounts;
account* g_player1Account = nullptr;
account* g_player2Account = nullptr;

// 链表形式的排行榜头指针
account* g_rankHead = nullptr;

//获取用户名和密码的指针类型
const wchar_t* account::getUsername() const {
	return username;
}
const wchar_t* account::getPassword() const {
	return password;
}
//得分部分功能
void account::add() {
	playersocer++;
}
int account::getScore() const {
	return playersocer;
}
void account::addnow() {
	playersocernow++;
}
int account::getScorenow() const {
	return playersocernow;
}
void account::commitNow() {
	playersocer += playersocernow;
	playersocernow = 0;
}
void account::resetNow() {
	playersocernow = 0;
}

// Helper to get projected total used for ranking
static int projectedTotal(const account* a) {
	if (!a) return 0;
	return a->getScore() + a->getScorenow();
}

// 根据 g_accounts 重建按 playersocer (+ playersocernow) 降序的链表，返回头指针
account* rebuildRankList() {
	account* head = nullptr;
	for (auto a : g_accounts) {
		// 将 a 插入到链表的合适位置（降序），比较 projected total
		a->next = nullptr;
		if (!head) {
			head = a;
			continue;
		}
		// 插入排序
		if (projectedTotal(a) > projectedTotal(head)) {
			a->next = head;
			head = a;
			continue;
		}
		account* prev = head;
		account* cur = head->next;
		while (cur && projectedTotal(cur) >= projectedTotal(a)) {
			prev = cur;
			cur = cur->next;
		}
		prev->next = a;
		a->next = cur;
	}
	return head;
}

// 当某账户获胜后更新分数并重建排行榜
void updateRankingAfterWin(account* winner) {
	if (!winner) return;
	// 增加胜利者总分
	winner->add();
	// 持久化并重建链表
	saveAccounts();
	g_rankHead = rebuildRankList();
}

//根据用户名查找账户
account* findAccountByName(const wchar_t* name) {
	for (auto a : g_accounts) {
		if (wcscmp(a->getUsername(), name) == 0) return a;
	}
	return nullptr;
}
//登录账户
account* loginAccount(const wchar_t* name, const wchar_t* pass) {
	account* a = findAccountByName(name);
	if (!a) return nullptr;
	if (wcscmp(a->getPassword(), pass) == 0) return a;
	return nullptr;
}
//注册账户
account* registerAccount(const wchar_t* name, const wchar_t* pass) {
	if (findAccountByName(name)) return nullptr;
	account* a = new account(name, pass, 0);
	g_accounts.push_back(a);
	return a;
}
//数据读取
void loadAccounts() {
	g_accounts.clear();
	std::ifstream ifs("Account.txt", std::ios::binary);
	if (!ifs) {
		std::cout << "数据异常！！！";
		return;
	}
	std::string line;
	while (std::getline(ifs, line)) {
		std::istringstream iss(line);
		std::string user_utf8, pass_utf8;
		int score = 0;
		if (!(iss >> user_utf8 >> pass_utf8 >> score)) continue;

		wchar_t user[50] = {0};
		wchar_t pass[50] = {0};
		MultiByteToWideChar(CP_UTF8, 0, user_utf8.c_str(), -1, user, 50);
		MultiByteToWideChar(CP_UTF8, 0, pass_utf8.c_str(), -1, pass, 50);

		account* a = new account(user, pass, score);
		g_accounts.push_back(a);
	}
	// 在加载后同时重建排行榜链表
	g_rankHead = rebuildRankList();
}
//数据的存入
void saveAccounts() {
	std::ofstream ofs("Account.txt", std::ios::binary);
	for (auto a : g_accounts) {
		char user_utf8[128] = {0};
		char pass_utf8[128] = {0};
		WideCharToMultiByte(CP_UTF8, 0, a->getUsername(), -1, user_utf8, 128, nullptr, nullptr);
		WideCharToMultiByte(CP_UTF8, 0, a->getPassword(), -1, pass_utf8, 128, nullptr, nullptr);
		ofs << user_utf8 << " " << pass_utf8 << " " << a->getScore() << "\n";
	}
}

//确保玩家已登录
bool ensurePlayersLoggedIn() {

	if (g_player1Account && g_player2Account) return true;

	using namespace std;

	loadAccounts();

	if (!g_player1Account) {
		int res = MessageBox(GetHWnd(), _T("玩家1未登录，是否登录/注册？"), _T("登录确认"), MB_YESNO | MB_ICONQUESTION);
		if (res == IDYES) {
			wchar_t uname[50];
			wchar_t upass[50];
			if (!InputBox(uname, 50, _T("请输入用户名:"), _T("登录"))) return false;
			if (!InputBox(upass, 50, _T("请输入密码:"), _T("登录"))) return false;
			account* a = loginAccount(uname, upass);
			if (a) g_player1Account = a;
			else {
				int r2 = MessageBox(GetHWnd(), _T("账户不存在或密码错误，是否注册新账号？"), _T("注册"), MB_YESNO | MB_ICONQUESTION);
				if (r2 == IDYES) {
					account* na = registerAccount(uname, upass);
					if (na) { g_player1Account = na; saveAccounts(); }
					else MessageBox(GetHWnd(), _T("用户名已存在！"), _T("错误"), MB_OK | MB_ICONERROR);
				} else return false;
			}
		}
	}

	if (!g_player2Account) {
		int res = MessageBox(GetHWnd(), _T("玩家2未登录，是否登录/注册？"), _T("登录确认"), MB_YESNO | MB_ICONQUESTION);
		if (res == IDYES) {
			wchar_t uname[50];
			wchar_t upass[50];
			if (!InputBox(uname, 50, _T("请输入用户名:"), _T("登录"))) return false;
			if (!InputBox(upass, 50, _T("请输入密码:"), _T("登录"))) return false;
			account* a = loginAccount(uname, upass);
			if (a) g_player2Account = a;
			else {
				int r2 = MessageBox(GetHWnd(), _T("账户不存在或密码错误，是否注册新账号？"), _T("注册"), MB_YESNO | MB_ICONQUESTION);
				if (r2 == IDYES) {
					account* na = registerAccount(uname, upass);
					if (na) { g_player2Account = na; saveAccounts(); }
					else MessageBox(GetHWnd(), _T("用户名已存在！"), _T("错误"), MB_OK | MB_ICONERROR);
				} else return false;
			}
		}
	}

	return (g_player1Account != nullptr && g_player2Account != nullptr);
}