#pragma once
#include"library/includer.h"

class Panel {
public:
	Panel(const int& maxPanel);//パネルの総数を貰う
	~Panel();
	void Disp(const int& x,const int& y,const int &size, const int& graph=-1);
	void DispFrame(const int& x,const int& y,const int& size,const int& color);

	void Replace(const int& index);//16とのみ入れ替え
	void Mix(const int& value);
	bool JastAll();//全て揃っているか
	void Align();//揃える
	bool JastPanel(const int& index);//正規の位置かどうか
	int ChangeIndex(const int& x,const int& y);//2次元を1次元に
	bool OnPanel(const int& x,const int& y,const int& size);

private:
	std::vector<int>myNumberList;
	int myMaxPanel;

	int PanelId(const int& number);//中身からindexを得る
	std::vector<int>::iterator FindNumber(const int& number);//中身からそのオペレーターを返す	
	int SixTeenRange(const int& value);//16範囲内に収める

	void MixMethod();//Mixの中身
	int MixDirection(int index);//MixMethodの中身

	bool Adjacent(const int& index);//上下左右のどこかにあるか

	void Sideways(const int& i, const int& positionX, const int& positionY, const int& size, const int& graph);//Dispの中身 
	void SidewaysDisp(const int& x, const int& y, const int& positionX, const int& positionY, const int& size, const int& graph,const int& number);//Sidewaysの中身

	void LineDisp(const int& x, const int& y, const int& size, const int& color)const;

};