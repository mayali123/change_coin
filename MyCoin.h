#pragma once

#include <QPushButton>
#include<QPixmap>
#include<QTimer>
#include<QSound>
class MyCoin : public QPushButton
{
	Q_OBJECT

public:
	MyCoin(QString butImg);
	void load();
	void changecoin();
	void mousePressEvent(QMouseEvent* event);
	~MyCoin();

	int posx, posy;				//x,y���������i,j
	bool flag;					//���滹�Ƿ���
	QTimer *timer1,*timer2;
	int max = 8;				//��Ƭ�����ֵ
	int min = 1;				//��Ƭ����Сֵ
	bool win;					//��������ж��Ƿ�ʤ��
private:
	bool bl;
	QPixmap pix;
	
};
