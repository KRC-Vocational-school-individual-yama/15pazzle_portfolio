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
		Wait=0//待機
		,Replace//入れ替え
		,Align//揃える
		,Clear//ゲームクリア
		,Mix//シャッフル

	};

	State state;
	Panel* panel;

	void WaitState(User* user);
	void BranchAlign(User* user);//WaitStateの中身
	void WaitClicked(User* user);//WaitStateの中身
	void BranchReplace(User* user);//WaitClickedの中身
	bool OnBoard(User* user);//BranchReplaceの中身

	void ReplaceState(User* user);
	void PanelCalc(User* user);//ReplaceStateの中身
	void PanelNumber(int& x, int& y);//PanelCalcの中身
	void BranchClear();//ReplaceStateの中身

	void AlignState();
	void ClearState(User* user);
	void MixState(User* user);

	void ClearDisp();//Dispの中身

};