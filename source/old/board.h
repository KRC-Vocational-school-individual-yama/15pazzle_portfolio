#pragma once
#include"includer.h"

namespace {
	static const int Board_Width = 4;//�Ֆʂ̉�
	const int Board_Height = 4;//�Ֆʂ̏c
	const int Board_Panel_Max= Board_Width * Board_Height;//�Ֆʂ̑���
	const int Board_Panel_SizeX = 64*2;//�}�X�ЂƂ̉���
	const int Board_Panel_SizeY = 64;//�}�X�ЂƂ̏c��

	const int Board_Fast_PosX = 150;//�Ֆʂ̍���ʒu
	const int Board_Fast_PosY = 150;//�Ֆʂ̍���ʒu

}

//15�p�Y���̑啔��
class Board  {
public:
	Board();
	~Board()		;
	void Init()		;
	void Update()	;
	void Draw()		;

	//DragLoadGraph �� �t���i
	void PosCalc(int& getX,int& getY,int x, int y,int index);
	//�Q�����z���index���P�����z��ɂ���
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

	//�N���A���ǂ��� true: �N���A,false:���N���A
	bool PazzleClear();
	//���g�̏ꏊ�ɂ��邩 true:����,false:���Ȃ�
	bool MyPosition(int index);

	//�}�E�X���N���b�N������@���[(16)�Ɠ���ւ�
	void MouseClickToReplace(int mouseX,int mouseY,bool mouseDown);
	//�V���b�t��
	void PazzleShuffle(int shuffleNum=100);

	//�ԍ��̓���ւ�
	void Replace(int& aNum,int& bNum);
};