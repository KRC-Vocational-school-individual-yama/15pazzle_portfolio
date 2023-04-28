#pragma once
#include"includer.h"

namespace {
	static const int Board_Width = 4;//盤面の横
	const int Board_Height = 4;//盤面の縦
	const int Board_Panel_Max= Board_Width * Board_Height;//盤面の総数
	const int Board_Panel_SizeX = 64*2;//マスひとつの横幅
	const int Board_Panel_SizeY = 64;//マスひとつの縦幅

	const int Board_Fast_PosX = 150;//盤面の左上位置
	const int Board_Fast_PosY = 150;//盤面の左上位置

}

//15パズルの大部分
class Board  {
public:
	Board();
	~Board()		;
	void Init()		;
	void Update()	;
	void Draw()		;

	//DragLoadGraph の 付属品
	void PosCalc(int& getX,int& getY,int x, int y,int index);
	//２次元配列のindexを１次元配列にする
	inline int GetIndex(int x,int y);
private:
	struct __Panel_____ {
		int number	= 0;
		float moveX = 0;
		float moveY = 0;
	};
	std::vector<__Panel_____>gameBord;
	std::vector<int> hImages;
	int hFont;
	bool keystop;

	//クリアかどうか true: クリア,false:未クリア
	bool PazzleClear();
	//自身の場所にいるか true:いる,false:いない
	bool MyPosition(int index);

	//マウスをクリックしたら　末端(16)と入れ替え
	void MouseClickToReplace(int mouseX,int mouseY,bool mouseDown);
	//シャッフル
	void PazzleShuffle(int shuffleNum=100);

	//番号の入れ替え
	void Replace(int& aNum,int& bNum);
};