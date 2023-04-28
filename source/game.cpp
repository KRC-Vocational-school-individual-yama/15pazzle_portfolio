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

	printfDx("Akey�ő�����\n");
	printfDx("�N���A�㉽���L�[�������ƃ��X�^�[�g\n");
}
