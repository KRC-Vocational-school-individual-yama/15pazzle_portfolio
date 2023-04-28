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
	hFont = CreateFontToHandle(NULL, Board_Panel_SizeY * 0.9, -1);//size 64 �� 90%
	assert(hFont > 0);

	gameBord.resize(Board_Panel_Max);

	for (int i = 0; i < Board_Panel_Max; i++)
		gameBord.at(i).number = i + 1;// ����������@+1�@1�`16

	//���s�� 100
	PazzleShuffle(10000);

	//�摜
	{
		int graphX = 0;
		int graphY = 0;
		{
			int hImage = LoadGraph(fastPass);
			assert(hImage > 0);

			DxLib::GetGraphSize(hImage, &graphX, &graphY);
			DeleteGraph(hImage);
		}

		int loadImages[Board_Panel_Max] = {};//LoadDiv�p
		LoadDivGraph(fastPass, Board_Panel_Max, Board_Width, Board_Height, graphX / Board_Width, graphY / Board_Height, loadImages);
		for (int i = 0; i < Board_Panel_Max; i++)
			assert(loadImages[i] > 0);
		//�����o�֑��
		std::vector<int> temp(loadImages, loadImages + Board_Panel_Max);
		hImages = temp;
	}
}

void Board::Update() {
	
	bool mouseClick = GetMouseInput() & MOUSE_INPUT_LEFT;
	
	//�����p�Y�h���̃p�Y
	if (GetMouseInput() & MOUSE_INPUT_RIGHT)
		keystop		= false;
	
	//�}�E�X�ʒu�擾
	int mouseX		= 0;
	int mouseY		= 0;
	GetMousePoint(&mouseX, &mouseY);

	//�{�[�h�̎l�p�̒��ɂ��鎞�����@�N���b�N����������
	{
		RECT mouseCollider = { mouseX,mouseY,5,5 };
		RECT bordCollider = {};

		bordCollider.left = Board_Fast_PosX;
		bordCollider.top = Board_Fast_PosY;
		bordCollider.right = Board_Width * Board_Panel_SizeX;
		bordCollider.bottom = Board_Height * Board_Panel_SizeY;

		//�}�E�X�����蔻��
		if (SquareCollision(mouseCollider, bordCollider))
			MouseClickToReplace(mouseX, mouseY, (mouseClick && not keystop));
	}

	for (int i = 0; i < gameBord.size(); i++) {

		if (CheckHitKey(KEY_INPUT_I)) {
			gameBord.at(i).number = i + 1;//�N���A�ʒu�ɕ��ׂ�
		}


		//index�Ɣԍ������킹�� -1
		int num = gameBord.at(i).number;
		--num;

		//�ړ���
		{
			float moveSpeed = 0.9f;// 0.3f;//0�`1�@0���� 1�����Ȃ�
			gameBord.at(i).moveX *= moveSpeed;
			gameBord.at(i).moveY *= moveSpeed;

			//��Βl�����̐����ȉ��Ȃ�0
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

	int color = 0xffffff;//��


	for (int x = 0; x < Board_Width; x++)
		for (int y = 0; y < Board_Height; y++) {

			int index = GetIndex(x, y);
			int posX = x * Board_Panel_SizeX + Board_Fast_PosX + gameBord.at(index).moveX;
			int posY = y * Board_Panel_SizeY + Board_Fast_PosY + gameBord.at(index).moveY;

			//�����Ă��物�F
			if (MyPosition(index))
				color = 0xeeee00;//��
			else {
				color = 0x0;//��
			}

			//���������16�͕`�悵�Ȃ�
			if (not PazzleClear())//��������\��
				if (gameBord.at(index).number == Board_Panel_Max)
					continue;

			//�摜�`��
			{
				int getX = 0, getY = 0;
				PosCalc(getX, getY, x, y, index);
				DrawExtendGraph(getX, getY, getX + Board_Panel_SizeX, Board_Panel_SizeY + getY, hImages[index], false);

			}

			//�g���`��
			DrawBox(posX, posY, posX + Board_Panel_SizeX, Board_Panel_SizeY + posY, 0xdddddd, false);//�D�F

			//�����`��
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
	// �N���b�N���ĂȂ��Ȃ�I��
	if (not mouseDown)
		return;

	//�}�E�X�̍��W����{�[�h�̈ʒu�𓾂�
	int panelIndexX = (mouseX - Board_Fast_PosX) / Board_Panel_SizeX;
	int panelIndexY = (mouseY - Board_Fast_PosY) / Board_Panel_SizeY;

	int mouseIndex  = GetIndex(panelIndexX, panelIndexY);

	for (int x = 0; x < Board_Width; x++) {
		for (int y = 0; y < Board_Height; y++) {
			int index = GetIndex(x, y);

			//16�̔ԍ���������
			if (gameBord.at(index).number != Board_Panel_Max)
				continue;

			//16���ד��m���ǂ���
			int neighborsX = max(x, panelIndexX) - min(x, panelIndexX);
			int neighborsY = max(y, panelIndexY) - min(y, panelIndexY);

			//�ړ��K��
			{
				//�΂߈ړ��֎~
				if (neighborsX == 1 && neighborsY == 1)
					return;

				if (x != panelIndexX) {//�����s
					//2�}�X�ȏ�
					if (neighborsX != 1)
						return;
				}
				if (y != panelIndexY) {//������
					//2�}�X�ȏ�
					if (neighborsY != 1)
						return;
				}
			}

			//����ւ�
			Replace(gameBord.at(mouseIndex).number, gameBord.at(index).number);

			//�����܂�
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

	for (int i = 0; i < shuffleNum; i++) {//���s��


		bool breakFlag = false;
		for (int x = 0; x < Board_Width; x++) {
			if (breakFlag)
				break;

			for (int y = 0; y < Board_Height; y++) {

				int index = GetIndex(x, y);
				if (gameBord.at(index).number != Board_Panel_Max)
					continue;

				int rand = GetRand(Dir::max);//�����擾
				int dirX = x;
				int dirY = y;

				//�����ɂ������p�l�����W���擾
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

				//�}�C�i�X�ɂȂ�Ȃ��悤��
				{
					if (dirX < 0)dirX *= -1;
					if (dirY < 0)dirY *= -1;
				}

				//����ւ�
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
