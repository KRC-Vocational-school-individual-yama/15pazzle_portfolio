#include "user.h"

const int User::CURSOR_SIZE=5;

User::User()
	:keystop(false)
{
}

User::~User()
{}

void User::Update() {
	keystop = CheckHitKeyAll();
}

bool User::IsClick(const int& mouseButton ) {
	return (GetMouseInput() & mouseButton);
}

bool User::IsKey(const int& keyButton ) {
	return CheckHitKey(keyButton);
}

bool User::AllKey() {
	return CheckHitKeyAll() && not keystop;
}

void User::MousePoint(int& x,int& y) {
	GetMousePoint(&x, &y);
}

RECT User::CursorRect() {
	int x=0, y=0;
	this->MousePoint(x,y);
	
	return {x,y,CURSOR_SIZE,CURSOR_SIZE };
}