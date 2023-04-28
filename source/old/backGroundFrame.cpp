#include "backGroundFrame.h"
#include"board.h"

namespace {
	char* pass = "data/texture/wood-texture_00004.jpg";
}
BackGroundFrame::BackGroundFrame()
	:hImage{-1}
{}
BackGroundFrame::~BackGroundFrame(){
	if (hImage > 0)
		DeleteGraph(hImage);
}
void BackGroundFrame::Init(){
	hImage = LoadGraph(pass);
	assert(hImage > 0);
}
void BackGroundFrame::Draw(){
		  int	left 	= Board_Fast_PosX;
		  int	up	 	= Board_Fast_PosY;
		  int	right	= Board_Fast_PosX + Board_Panel_SizeX * Board_Width;
	const int	bottom	= Board_Fast_PosY + Board_Panel_SizeY * Board_Height;
		  int	size	= 50;

	int r=0, g=0, b=0;
	GetDrawBright(&r,&g,&b );
	SetDrawBright(200,200,200);
	DrawExtendGraph(left-size,up-size,right+size,bottom+size,hImage,true);
	SetDrawBright(r, g, b);

	DrawExtendGraph(left- size,up- size,left,bottom+size,hImage,true);
	DrawExtendGraph(right,up-size,right+size,bottom+size,hImage,true);
	DrawExtendGraph(left, up - size, right, up, hImage, true);
	DrawExtendGraph(left, bottom, right, bottom + size, hImage, true);
}
