#pragma once
#include"library/includer.h"

class Panel {
public:
	Panel(const int& maxPanel);//�p�l���̑�����Ⴄ
	~Panel();
	void Disp(const int& x,const int& y,const int &size, const int& graph=-1);
	void DispFrame(const int& x,const int& y,const int& size,const int& color);

	void Replace(const int& index);//16�Ƃ̂ݓ���ւ�
	void Mix(const int& value);
	bool JastAll();//�S�đ����Ă��邩
	void Align();//������
	bool JastPanel(const int& index);//���K�̈ʒu���ǂ���
	int ChangeIndex(const int& x,const int& y);//2������1������
	bool OnPanel(const int& x,const int& y,const int& size);

private:
	std::vector<int>myNumberList;
	int myMaxPanel;

	int PanelId(const int& number);//���g����index�𓾂�
	std::vector<int>::iterator FindNumber(const int& number);//���g���炻�̃I�y���[�^�[��Ԃ�	
	int SixTeenRange(const int& value);//16�͈͓��Ɏ��߂�

	void MixMethod();//Mix�̒��g
	int MixDirection(int index);//MixMethod�̒��g

	bool Adjacent(const int& index);//�㉺���E�̂ǂ����ɂ��邩

	void Sideways(const int& i, const int& positionX, const int& positionY, const int& size, const int& graph);//Disp�̒��g 
	void SidewaysDisp(const int& x, const int& y, const int& positionX, const int& positionY, const int& size, const int& graph,const int& number);//Sideways�̒��g

	void LineDisp(const int& x, const int& y, const int& size, const int& color)const;

};