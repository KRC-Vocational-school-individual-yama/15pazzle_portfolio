#pragma once
#include"library/includer.h"

class User {
public:
	User();
	~User();
	void Update();
	bool IsClick(const int& mouseButton );
	bool IsKey(const int& keyButton );
	bool AllKey();
	void MousePoint(int& x, int& y);
	RECT CursorRect();
private:
	static const int CURSOR_SIZE;
	bool keystop;
};
