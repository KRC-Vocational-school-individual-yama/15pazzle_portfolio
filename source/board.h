#pragma once
#include"library/includer.h"
class Panel;
class User;


class Board {
public:
	Board();
	~Board();
	void Update(User* user);
	void Disp();

private:
	static const int MAX_PANEL;
	static const int POSITION_X;
	static const int POSITION_Y;
	static const int PANEL_SIZE;
	static const int MIX_VALUE;

	enum class State {
		Wait=0//�ҋ@
		,Replace//����ւ�
		,Align//������
		,Clear//�Q�[���N���A
		,Mix//�V���b�t��

	};

	State state;
	Panel* panel;

	void WaitState(User* user);
	void BranchAlign(User* user);//WaitState�̒��g
	void WaitClicked(User* user);//WaitState�̒��g
	void BranchReplace(User* user);//WaitClicked�̒��g
	bool OnBoard(User* user);//BranchReplace�̒��g

	void ReplaceState(User* user);
	void PanelCalc(User* user);//ReplaceState�̒��g
	void PanelNumber(int& x, int& y);//PanelCalc�̒��g
	void BranchClear();//ReplaceState�̒��g

	void AlignState();
	void ClearState(User* user);
	void MixState(User* user);

	void ClearDisp();//Disp�̒��g

};