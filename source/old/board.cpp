#include "board.h"

namespace {
	char* fastPass = "data/texture/wood-texture_00127.jpg";
}

Board::Board()
	:gameBord()
	,hFont{-1}
	,hImages{}
	,keystop{false}
{
	gameBord.clear();
	hImages.clear();
}

Board::~Board() {

	if (hFont > 0)
		DeleteFontToHandle(hFont);
	hFont = -1;
	for (int i = 0; i < Board_Panel_Max; i++) {
		if(hImages.at(i)>0)
			DeleteGraph(hImages.at(i));
	}
	hImages.clear();
}

void Board::Init() {
	hFont = CreateFontToHandle(NULL, Board_Panel_SizeY * 0.9, -1);//size 64 の 90%
	assert(hFont > 0);

	gameBord.resize(Board_Panel_Max);

	for (int i = 0; i < Board_Panel_Max; i++)
		gameBord.at(i).number = i + 1;// 数字を入れる　+1　1～16

	//試行回数 100
	PazzleShuffle(10000);

	//画像
	{
		int graphX = 0;
		int graphY = 0;
		{
			int hImage = LoadGraph(fastPass);
			assert(hImage > 0);

			DxLib::GetGraphSize(hImage, &graphX, &graphY);
			DeleteGraph(hImage);
		}

		int loadImages[Board_Panel_Max] = {};//LoadDiv用
		LoadDivGraph(fastPass, Board_Panel_Max, Board_Width, Board_Height, graphX / Board_Width, graphY / Board_Height, loadImages);
		for (int i = 0; i < Board_Panel_Max; i++)
			assert(loadImages[i] > 0);
		//メンバへ代入
		std::vector<int> temp(loadImages, loadImages + Board_Panel_Max);
		hImages = temp;
	}
}

void Board::Update() {
	
	bool mouseClick = GetMouseInput() & MOUSE_INPUT_LEFT;
	
	//実質パズドラのパズ
	if (GetMouseInput() & MOUSE_INPUT_RIGHT)
		keystop		= false;
	
	//マウス位置取得
	int mouseX		= 0;
	int mouseY		= 0;
	GetMousePoint(&mouseX, &mouseY);

	//ボードの四角の中にある時だけ　クリックが反応する
	{
		RECT mouseCollider = { mouseX,mouseY,5,5 };
		RECT bordCollider = {};

		bordCollider.left = Board_Fast_PosX;
		bordCollider.top = Board_Fast_PosY;
		bordCollider.right = Board_Width * Board_Panel_SizeX;
		bordCollider.bottom = Board_Height * Board_Panel_SizeY;

		//マウス当たり判定
		if (SquareCollision(mouseCollider, bordCollider))
			MouseClickToReplace(mouseX, mouseY, (mouseClick && not keystop));
	}

	for (int i = 0; i < gameBord.size(); i++) {

		if (CheckHitKey(KEY_INPUT_I)) {
			gameBord.at(i).number = i + 1;//クリア位置に並べる
		}


		//indexと番号を合わせる -1
		int num = gameBord.at(i).number;
		--num;

		//移動中
		{
			float moveSpeed = 0.9f;// 0.3f;//0～1　0速い 1動かない
			gameBord.at(i).moveX *= moveSpeed;
			gameBord.at(i).moveY *= moveSpeed;

			//絶対値がこの数字以下なら0
			double coercionNum		 = 1.5;
			if ((gameBord.at(i).moveX < coercionNum)&&(gameBord.at(i).moveX > coercionNum))
				 gameBord.at(i).moveX = 0;
			if ((gameBord.at(i).moveY < coercionNum)&&(gameBord.at(i).moveY > coercionNum))
				 gameBord.at(i).moveY = 0;
		}
	}

	keystop = mouseClick;
}

void Board::Draw() {

	int color = 0xffffff;//白


	for (int x = 0; x < Board_Width; x++)
		for (int y = 0; y < Board_Height; y++) {

			int index = GetIndex(x, y);
			int posX = x * Board_Panel_SizeX + Board_Fast_PosX + gameBord.at(index).moveX;
			int posY = y * Board_Panel_SizeY + Board_Fast_PosY + gameBord.at(index).moveY;

			//あってたら黄色
			if (MyPosition(index))
				color = 0xeeee00;//黄
			else {
				color = 0x0;//黒
			}

			//ここから先16は描画しない
			if (not PazzleClear())//揃ったら表示
				if (gameBord.at(index).number == Board_Panel_Max)
					continue;

			//画像描画
			{
				int getX = 0, getY = 0;
				PosCalc(getX, getY, x, y, index);
				DrawExtendGraph(getX, getY, getX + Board_Panel_SizeX, Board_Panel_SizeY + getY, hImages[index], false);

			}

			//枠線描画
			DrawBox(posX, posY, posX + Board_Panel_SizeX, Board_Panel_SizeY + posY, 0xdddddd, false);//灰色

			//数字描画
			DrawFormatStringToHandle(posX, posY, color, hFont, "%2d", gameBord.at(index).number);
		}
}

void Board::PosCalc(int& getX, int& getY, int x, int y, int index){
	int posX = x * Board_Panel_SizeX + Board_Fast_PosX + gameBord.at(index).moveX;
	int posY = y * Board_Panel_SizeY + Board_Fast_PosY + gameBord.at(index).moveY;

	getX = posX;
	getY = posY;
}

bool Board::PazzleClear(){

	bool clearFlag = true;

	for (int i = 0; i < gameBord.size(); i++) {
		__Panel_____ panel = gameBord.at(i);
		int number = i + 1;
		clearFlag = (true && (panel.number == number));
	}
	
	return clearFlag;
}

bool Board::MyPosition(int index){
	__Panel_____ panel= gameBord.at(index);
	int number = index + 1;
	return (panel.number == number);
}

void Board::MouseClickToReplace(int mouseX, int mouseY,bool mouseDown) {
	// クリックしてないなら終了
	if (not mouseDown)
		return;

	//マウスの座標からボードの位置を得る
	int panelIndexX = (mouseX - Board_Fast_PosX) / Board_Panel_SizeX;
	int panelIndexY = (mouseY - Board_Fast_PosY) / Board_Panel_SizeY;

	int mouseIndex  = GetIndex(panelIndexX, panelIndexY);

	for (int x = 0; x < Board_Width; x++) {
		for (int y = 0; y < Board_Height; y++) {
			int index = GetIndex(x, y);

			//16の番号をさがす
			if (gameBord.at(index).number != Board_Panel_Max)
				continue;

			//16が隣同士かどうか
			int neighborsX = max(x, panelIndexX) - min(x, panelIndexX);
			int neighborsY = max(y, panelIndexY) - min(y, panelIndexY);

			//移動規制
			{
				//斜め移動禁止
				if (neighborsX == 1 && neighborsY == 1)
					return;

				if (x != panelIndexX) {//同じ行
					//2マス以上
					if (neighborsX != 1)
						return;
				}
				if (y != panelIndexY) {//同じ列
					//2マス以上
					if (neighborsY != 1)
						return;
				}
			}

			//入れ替え
			Replace(gameBord.at(mouseIndex).number, gameBord.at(index).number);

			//動きます
			gameBord.at(index).moveX = (panelIndexX - x)*Board_Panel_SizeX;
			gameBord.at(index).moveY = (panelIndexY - y)*Board_Panel_SizeY;

			return ;
		}
	}
}

void Board::PazzleShuffle(int shuffleNum ){
	enum Dir {
		up
		,down
		,left
		,right
		,max
	};

	for (int i = 0; i < shuffleNum; i++) {//試行回数


		bool breakFlag = false;
		for (int x = 0; x < Board_Width; x++) {
			if (breakFlag)
				break;

			for (int y = 0; y < Board_Height; y++) {

				int index = GetIndex(x, y);
				if (gameBord.at(index).number != Board_Panel_Max)
					continue;

				int rand = GetRand(Dir::max);//方向取得
				int dirX = x;
				int dirY = y;

				//方向にあったパネル座標を取得
				switch (rand) {
				case Dir::up:
					dirY = (y - 1) % Board_Height;
					break;
				case Dir::down:
					dirY = (y + 1) % Board_Height;
					break;
				case Dir::left:
					dirX = (x - 1) % Board_Width;

					break;
				case Dir::right:
					dirX = (x + 1) % Board_Width;

					break;
				default:
					//non
					break;
				}

				//マイナスにならないように
				{
					if (dirX < 0)dirX *= -1;
					if (dirY < 0)dirY *= -1;
				}

				//入れ替え
				Replace(gameBord.at(GetIndex(dirX, dirY)).number, gameBord.at(index).number);
				breakFlag = true;
			}
		}
	}
}

void Board::Replace(int& aNum, int& bNum){
	//sort
	int temp = aNum;
	aNum	 = bNum;
	bNum	 = temp;
}

int Board::GetIndex(int x, int y){
	return x + y * Board_Width;
}
