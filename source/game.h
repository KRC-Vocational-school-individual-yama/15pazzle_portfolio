#pragma once
#include"library/includer.h"
class User;
class Board;

class Game {
public:
	Game();
	~Game();
	void Update();
	void Draw();
private:
	User* user;
	Board* board;
};