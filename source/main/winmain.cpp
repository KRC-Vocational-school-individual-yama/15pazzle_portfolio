#include"../library/includer.h"
#include"../game.h"

void LoadInit() {//初期化前設定
	SetOutApplicationLogValidFlag(FALSE)		;//ログの書き出し設定
	ChangeWindowMode(TRUE)					;//ウィンドウモードにする
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32)	;//ウィンドウサイズを設定する
	SetWindowSizeExtendRate(1.0f)			;//ウィンドウ拡大率
	SetWindowStyleMode(7)				;//ウィンドウの最大化ボタンを機能させる。
	SetDrawScreen(DX_SCREEN_BACK)					;//裏画面を描画対象へ
	SetMainWindowText(WINDOW_NAME)						;//ウィンドウの名前
	SetUseDXArchiveFlag(TRUE)						;//DxLibのアーカイブを読み込むかどうか
	SetWaitVSyncFlag(FALSE);//垂直同期信号待ち
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){//プログラムは WinMain から始まります
	LoadInit()				;//初期化前設定
	
	if (DxLib_Init() == -1)	 // ＤＸライブラリ初期化処理
		return -1			;// エラーが起きたら直ちに終了
	
	Game* game = new Game;
	
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE)!=1) {//メイン処理
		clsDx()				;//prinfdxの描画を消去

		game->Update();
		ClearDrawScreen()	;//裏画面の描画を全て消去
		if (CheckHitKey(KEY_INPUT_W) && CheckHitKey(KEY_INPUT_LCONTROL))
			break;

		game->Draw();
		ScreenFlip()		;//裏画面と表画面の入替
	}

	delete game;

	DxLib_End()				;// ＤＸライブラリ使用の終了処理

	return 0				;// ソフトの終了 
}
