#include"app.h"

#include"../board.h"
#include"../backGroundFrame.h"
#include"../panel.h"

namespace {
	BackGroundFrame	*	backImage=nullptr;
	Board			*	board=nullptr;
	Panel* panel=nullptr;
}
namespace APP {
	void Init() {
		backImage = new BackGroundFrame;
		board = new Board;
		panel = new Panel(16);

		backImage->Init();
		board->Init();
	}
	void Update() {
		board->Update();
		int index = panel->ChangeIndex(2,3);
		auto num= panel->PanelId(index);
		if (CheckHitKey(KEY_INPUT_B))
			assert(!panel->JastPanel(index));
		if (CheckHitKey(KEY_INPUT_N))
			panel->Replace(index);
	}
	void Draw() {
		backImage->Draw();
		board->Draw();
		panel->Disp(100,100,64,-1);
	}
	void Delete() {
		delete backImage;
		delete board;
		delete panel;
	}
}
