#include"easyx.h"
#include"graphics.h"

#ifndef Page
#define Page

enum Pages {
	PAGE_MENU,
	PAGE_GAME,
	PAGE_SETTING,
};



class page {
public:
	virtual void drawPage()=0;
	
	virtual ~page(){}
	MOUSEMSG m = GetMouseMsg();
	
};

class page_menu :virtual public page{
public:
	void drawPage()override ;
	
};

class page_game :virtual public page {
public:
	void drawPage()override ;
	
	
};

class page_setting :virtual public page {
public:
	void drawPage()override ;
	
};



#endif