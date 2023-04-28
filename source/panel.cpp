#include"panel.h"

Panel::Panel(const int& maxPanel)
	:myNumberList(maxPanel, 0)
	, myMaxPanel(maxPanel)
{
	Align();
}

Panel::~Panel() {

}
void Panel::Disp(const int& positionX, const int& positionY, const int& size, const int& graph) {

	const int width = sqrt(myMaxPanel);
	for(int i=0;i<myMaxPanel;i++)
		Sideways(i, positionX, positionY, size, graph);
}
//Dispの中身
void Panel::Sideways(const int& i, const int& positionX, const int& positionY, const int& size, const int& graph) {
	int width = sqrt(myMaxPanel);
	int x = 0, y = 0;
	x = i % width;
	y = i / width;
	int index = ChangeIndex(x, y);
	int number = myNumberList.at(index);

	if (not JastAll() && (number == (myMaxPanel - 1)))
		return;
	SidewaysDisp(x, y, positionX, positionY, size, graph, number);
}
//Sidewaysの中身
void Panel::SidewaysDisp(const int& x, const int& y, const int& positionX, const int& positionY, const int& size, const int& graph, const int& number) {
	if (graph > -1) {
		DrawGraph(positionX + x * size, positionY + y * size, graph, false);
		return;
	}

	const std::string dispNumber(std::to_string(number+1));
	const int middleOffset = size / 3;

	DrawString(positionX+ x* size+ middleOffset
			  ,positionY+ y* size+ middleOffset
			  ,dispNumber.c_str(), 0xffffff
	);
}
void Panel::DispFrame(const int& x, const int& y, const int& size, const int& color) {
	const int frameSize = size * sqrt(myMaxPanel);
	DrawBox(x, y, x + frameSize, y + frameSize, color, false);
	LineDisp(x, y, size, color);
}
void Panel::LineDisp(const int& x, const int& y, const int& size, const int& color)const {
	const int width = sqrt(myMaxPanel);
	for (int i = 0; i < width; i++) {
		DrawLine(x + i * size, y, x + i * size, y + width * size, color);
		DrawLine(x, y + i * size, x + width * size, y + i * size, color);
	}
}
//16とのみ入れ替え
void Panel::Replace(const int& index) {
	std::vector<int>::iterator indexNumber = FindNumber(myNumberList.at(index));
	std::vector<int>::iterator sixTeen = FindNumber(myMaxPanel - 1);

	if (Adjacent(index))
		std::swap((*sixTeen), (*indexNumber));
}
//隣接しているか
bool Panel::Adjacent(const int& index) {
	int  width			= sqrt(myMaxPanel);
	int	 sixTeenIndex	= PanelId(myMaxPanel - 1);

	bool upSame			= (sixTeenIndex - width) == (index);
	bool downSame		= (sixTeenIndex + width) == (index);
	bool leftSame		= (sixTeenIndex - 1)	 == (index);
	bool rightSame		= (sixTeenIndex + 1)	 == (index);

	leftSame	= ((sixTeenIndex % width) == 0) ? false : leftSame ;
	rightSame	= ((sixTeenIndex % width) == 3) ? false : rightSame;


	return (upSame || downSame || rightSame || leftSame);
}

void Panel::Mix(const int& value) {
	for (int i = 0; i < value; i++) 
		MixMethod();
}

void Panel::MixMethod() {
	int sixTeenIndex = PanelId(myMaxPanel - 1);

	int changeIndex = MixDirection(sixTeenIndex);
	Replace(changeIndex);
}
//MixMethodの中身
int Panel::MixDirection(int index) {
	enum Direction {
		up
		,right
		,down
		,left
		,max
	};
	Direction direction= (Direction)GetRand(max);
	int width = sqrt(myMaxPanel);

	switch (direction) {
	case up:	index -= width;	break;
	case right:	index += 1;		break;
	case down:	index += width;	break;
	case left:	index -= 1;		break;
	default:	break;
	}

	 return std::clamp(index, 0, myMaxPanel - 1);
}
//全て揃っているか
bool Panel::JastAll() {
	bool isJast = true;
	for (int i = 0; i < myMaxPanel; i++)
		isJast = (isJast && JastPanel(i));
	return isJast;
}

void Panel::Align() {
	for (int i = 0; i < myMaxPanel; i++)
		myNumberList.at(i) = i;
}
//正規の位置かどうか
bool Panel::JastPanel(const int& index) {
	if (index >= myMaxPanel)
		return false;
	return (myNumberList.at(index) == index);
}
//中身からindexを得る
int Panel::PanelId(const int& number) {
	int anser = -1;

	for (int i = 0; (number != myNumberList.at(i)) && (i < myMaxPanel); i++)
		anser = i;
	++anser;

	return SixTeenRange(anser);
}
int Panel::ChangeIndex(const int& x, const int& y) {
	int index = x + y * (int)(sqrt(myMaxPanel));
	return SixTeenRange(index);
}

bool Panel::OnPanel(const int& x, const int& y, const int& size) {
	int cursorX = 0, cursorY = 0;
	GetMousePoint(&cursorX, &cursorY);

	RECT cursor;
	cursor.left = cursorX;
	cursor.top = cursorY;
	cursor.right = 5;
	cursor.bottom = 5;

	RECT panel;
	panel.left = x;
	panel.top = y;
	panel.right = size * sqrt(myMaxPanel);
	panel.bottom = size * sqrt(myMaxPanel);

	return SquareCollision(panel, cursor);
}

//中身からそのオペレーターを返す
std::vector<int>::iterator Panel::FindNumber(const int& number) {
	return std::find(myNumberList.begin(), myNumberList.end(), number);
}

//16範囲内に収める
int Panel::SixTeenRange(const int& value) {
	return (value >= myMaxPanel) ? -1 : value;
}