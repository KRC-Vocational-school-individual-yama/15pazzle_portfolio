#pragma once
#include<DxLib.h>
#include<math.h>
#include<cassert>
#include<string>
#include<vector>
#include<algorithm>

namespace {
	static const int SCREEN_WIDTH = 800;//画面横幅
	static const int SCREEN_HEIGHT = 600;//画面立幅
	static const char* WINDOW_NAME = "15pazzle";//ウィンドウ名

}

#define not !



//left top : x,y  right bottom : xSize,ySize true：当たっている
inline bool SquareCollision(RECT a, RECT b) {
	if (a.top >= b.top + b.bottom)return false;
	if (a.top + a.bottom <= b.top)return false;
	if (a.left >= b.left + b.right)return false;
	if (a.left + a.right <= b.left)return false;

	//どこにも触れていなければfalseの逆説
	return true;

}
