#include<easyx.h>
#include<graphics.h>

#ifndef Button
#define Button

class button {
private:
	int x, y, w, h;
	wchar_t text[20];
	
public:
	button(int x0,int y0,int w0,int h0,const wchar_t *text);
	

	bool isinButton ();

	int getx ();
	int gety ();
	int getw ();
	int geth ();
	wchar_t* gettext ();
	MOUSEMSG m = GetMouseMsg();

	
	void drawButton();//外部接口
	//void drawButton2();
};


#endif 