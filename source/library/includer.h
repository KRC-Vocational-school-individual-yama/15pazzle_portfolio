#pragma once
#include<DxLib.h>
#include<math.h>
#include<cassert>
#include<string>
#include<vector>
#include<algorithm>

namespace {
	static const int SCREEN_WIDTH = 800;//��ʉ���
	static const int SCREEN_HEIGHT = 600;//��ʗ���
	static const char* WINDOW_NAME = "15pazzle";//�E�B���h�E��

}

#define not !



//left top : x,y  right bottom : xSize,ySize true�F�������Ă���
inline bool SquareCollision(RECT a, RECT b) {
	if (a.top >= b.top + b.bottom)return false;
	if (a.top + a.bottom <= b.top)return false;
	if (a.left >= b.left + b.right)return false;
	if (a.left + a.right <= b.left)return false;

	//�ǂ��ɂ��G��Ă��Ȃ����false�̋t��
	return true;

}
