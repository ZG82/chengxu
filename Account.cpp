#include "Account.h"
#include <easyx.h>
#include <tchar.h>
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <cstring>
#include <string>
#include <sstream>

// 全局变量初始化
std::vector<account*> g_accounts;
account* g_player1Account = nullptr;
account* g_player2Account = nullptr;
account* g_rankHead = nullptr;

// 获取用户名和密码
const wchar_t* account::getUsername() const {
	return username;
}
const wchar_t* account::getPassword() const {
	return password;
}

// 累计总分+1
void account::add() {
	playersocer++;
}
int account::getScore() const {
	return playersocer;
}

// 当前会话得分+1
void account::addnow() {
	playersocernow++;
}
int account::getScorenow() const {
	return playersocernow;
}

// 将会话得分提交到累计总分，并重置会话得分
void account::commitNow() {
	playersocer += playersocernow;
	playersocernow = 0;
}

// 重置会话得分（开始新游戏时调用）
void account::resetNow() {
	playersocernow = 0;
}

// 计算账户的预测总分（累计 + 会话），用于排行榜排序
static int projectedTotal(const account* a) {
	if (!a) return 0;
	return a->getScore() + a->getScorenow();
}

// 重建排行榜链表：将所有账户按预测总分降序插入链表
account* rebuildRankList() {
	account* head = nullptr;
	for (auto a : g_accounts) {
		a->next = nullptr;
		if (!head) {
			head = a;
			continue;
		}
		// 插入到链表头部
		if (projectedTotal(a) > projectedTotal(head)) {
			a->next = head;
			head = a;
			continue;
		}
		// 寻找合适的插入位置
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

// 某账户获胜后：加分 + 持久化 + 重建排行榜
void updateRankingAfterWin(account* winner) {
	if (!winner) return;
	winner->add();
	saveAccounts();
	g_rankHead = rebuildRankList();
}

// 按用户名查找账户
account* findAccountByName(const wchar_t* name) {
	for (auto a : g_accounts) {
		if (wcscmp(a->getUsername(), name) == 0) return a;
	}
	return nullptr;
}

// 登录：验证用户名和密码
account* loginAccount(const wchar_t* name, const wchar_t* pass) {
	account* a = findAccountByName(name);
	if (!a) return nullptr;
	if (wcscmp(a->getPassword(), pass) == 0) return a;
	return nullptr;
}

// 注册：创建新账户并加入全局列表
account* registerAccount(const wchar_t* name, const wchar_t* pass) {
	if (findAccountByName(name)) return nullptr;  // 用户名已存在
	account* a = new account(name, pass, 0);
	g_accounts.push_back(a);
	return a;
}

// 从 Account.txt 加载账户数据（UTF-8编码）
void loadAccounts() {
	g_accounts.clear();
	std::ifstream ifs("Account.txt", std::ios::binary);
	if (!ifs) {
		std::cout << "数据读取异常" << std::endl;
		return;
	}
	std::string line;
	while (std::getline(ifs, line)) {
		std::istringstream iss(line);
		std::string user_utf8, pass_utf8;
		int score = 0;
		if (!(iss >> user_utf8 >> pass_utf8 >> score)) continue;

		// UTF-8 转 宽字符
		wchar_t user[50] = {0};
		wchar_t pass[50] = {0};
		MultiByteToWideChar(CP_UTF8, 0, user_utf8.c_str(), -1, user, 50);
		MultiByteToWideChar(CP_UTF8, 0, pass_utf8.c_str(), -1, pass, 50);

		account* a = new account(user, pass, score);
		g_accounts.push_back(a);
	}
	// 加载后同时重建排行榜
	g_rankHead = rebuildRankList();
}

// 保存账户数据到 Account.txt（UTF-8编码）
void saveAccounts() {
	std::ofstream ofs("Account.txt", std::ios::binary);
	for (auto a : g_accounts) {
		// 宽字符 转 UTF-8
		char user_utf8[128] = {0};
		char pass_utf8[128] = {0};
		WideCharToMultiByte(CP_UTF8, 0, a->getUsername(), -1, user_utf8, 128, nullptr, nullptr);
		WideCharToMultiByte(CP_UTF8, 0, a->getPassword(), -1, pass_utf8, 128, nullptr, nullptr);
		ofs << user_utf8 << " " << pass_utf8 << " " << a->getScore() << "\n";
	}
}

// 确保两个玩家都已登录，否则弹出登录/注册对话框
bool ensurePlayersLoggedIn() {
	if (g_player1Account && g_player2Account) return true;

	using namespace std;
	loadAccounts();

	// 玩家1登录
	if (!g_player1Account) {
		int res = MessageBox(GetHWnd(), _T("玩家1未登录，是否登录/注册？"), _T("登录确认"), MB_YESNO | MB_ICONQUESTION);
		if (res == IDYES) {
			wchar_t uname[50];
			wchar_t upass[50];
			if (!InputBox(uname, 50, _T("请输入用户名："), _T("登录"))) return false;
			if (!InputBox(upass, 50, _T("请输入密码："), _T("登录"))) return false;
			account* a = loginAccount(uname, upass);
			if (a) g_player1Account = a;
			else {
				// 登录失败，提示注册
				int r2 = MessageBox(GetHWnd(), _T("账户不存在或密码错误，是否注册新账号？"), _T("注册"), MB_YESNO | MB_ICONQUESTION);
				if (r2 == IDYES) {
					account* na = registerAccount(uname, upass);
					if (na) { g_player1Account = na; saveAccounts(); }
					else MessageBox(GetHWnd(), _T("用户名已存在！"), _T("错误"), MB_OK | MB_ICONERROR);
				} else return false;
			}
		}
	}

	// 玩家2登录（逻辑同上）
	if (!g_player2Account) {
		int res = MessageBox(GetHWnd(), _T("玩家2未登录，是否登录/注册？"), _T("登录确认"), MB_YESNO | MB_ICONQUESTION);
		if (res == IDYES) {
			wchar_t uname[50];
			wchar_t upass[50];
			if (!InputBox(uname, 50, _T("请输入用户名："), _T("登录"))) return false;
			if (!InputBox(upass, 50, _T("请输入密码："), _T("登录"))) return false;
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