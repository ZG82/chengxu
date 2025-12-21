#include <corecrt_wstring.h>

#ifndef Account
#define Account

class account {
private:
	wchar_t username[50];
	wchar_t password[50];
	int playersocer;
public:
	account(const wchar_t* user, const wchar_t* pass) {
		wcscpy_s(username, user);
		wcscpy_s(password, pass);
	}

	void add();
	wchar_t* getUsername();
	wchar_t* getPassword();
};

#endif