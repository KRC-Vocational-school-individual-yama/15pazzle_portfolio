#include "game.h"
#include"user.h"
#include"board.h"

Game::Game()
	:user(nullptr)
	,board(nullptr)
{
	user = new User;
	board = new Board;
}

Game::~Game(){
	delete user;
	delete board;
}

void Game::Update(){
	board->Update(user);
	user->Update();
}

void Game::Draw(){
	board->Disp();

	printfDx("Akeyで揃える\n");
	printfDx("クリア後何かキーを押すとリスタート\n");
}
