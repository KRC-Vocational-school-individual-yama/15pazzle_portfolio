#include "board.h"
#include"panel.h"
#include"user.h"

const int Board::MAX_PANEL	= 16;
const int Board::POSITION_X = 100;
const int Board::POSITION_Y = 100;
const int Board::PANEL_SIZE = 64;
const int Board::MIX_VALUE  = 1000;

Board::Board()
	:panel(nullptr)
	,state(State::Wait)
{
	panel = new Panel(MAX_PANEL);
	panel->Mix(MIX_VALUE);
}

Board::~Board(){
	delete panel;
}

void Board::Update(User* user) {
	assert(user != nullptr);

	switch (state){
	case Board::State::Wait:	WaitState(user);   	break;
	case Board::State::Replace:	ReplaceState(user);	break;
	case Board::State::Align:	AlignState();		break;
	case Board::State::Clear:	ClearState(user);  	break;
	case Board::State::Mix:		MixState(user);		break;
	default:		break;
	}

}

void Board::Disp(){
	assert(panel != nullptr);
	panel->Disp(POSITION_X, POSITION_Y, PANEL_SIZE);
	panel->DispFrame(POSITION_X, POSITION_Y, PANEL_SIZE, 0xffffff);

	ClearDisp();
}
//Dispの中身
void Board::ClearDisp() {
	if (state != State::Clear)
		return;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 / 3);
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0xdddddd, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	DrawString(SCREEN_WIDTH / 2 - 40, SCREEN_HEIGHT / 2 - 40, "Clear", 0);

}

void Board::WaitState(User* user){
	WaitClicked(user);
	BranchAlign(user);
}
//WaitClickedの中身
void Board::BranchReplace(User*user) {
	if (not OnBoard(user))
		return;
	state = State::Replace;
}
//BranchReplaceの中身
bool Board::OnBoard(User* user) {
	
	RECT cursor=user->CursorRect();

	RECT board;
	board.left	 = POSITION_X;
	board.top	 = POSITION_Y;
	board.right  = PANEL_SIZE * sqrt(MAX_PANEL);
	board.bottom = PANEL_SIZE * sqrt(MAX_PANEL);

	return SquareCollision(board, cursor);
}
//WaitStateの中身
void Board::BranchAlign(User* user){
	if (not user->IsKey(KEY_INPUT_A))
		return;
	state = State::Align;
}
//WaitStateの中身
void Board::WaitClicked(User* user) {
	if (not user->IsClick(MOUSE_INPUT_LEFT))
		return;
	BranchReplace(user);
}

void Board::ReplaceState(User* user) {
	PanelCalc(user);

	BranchClear();
}
//ReplaceStateの中身
void Board::PanelCalc(User* user) {
	int x = 0, y = 0;
	user->MousePoint(x, y);

	PanelNumber(x,y);

	int index = panel->ChangeIndex(x, y);
	panel->Replace(index);

}
//PanelCalcの中身
void Board::PanelNumber(int& x, int& y) {
	x -= POSITION_X;
	y -= POSITION_X;

	x /= PANEL_SIZE;
	y /= PANEL_SIZE;
	
	x= std::clamp(x, 0, (int)sqrt(MAX_PANEL) - 1);
	y= std::clamp(y, 0, (int)sqrt(MAX_PANEL) - 1);
}
//ReplaceStateの中身
void Board::BranchClear() {
	if (panel->JastAll()) {
		state = State::Clear;
		return;
	}

	state = State::Wait;
}

void Board::AlignState() {
	panel->Align();
	state = State::Clear;
}

void Board::ClearState(User* user) {
	if (not user->AllKey())
		return;
	state = State::Mix;
}

void Board::MixState(User* user) {
	panel->Mix(MIX_VALUE);

	state = State::Wait;
}