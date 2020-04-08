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

	int posx, posy;				//x,y代表数组的i,j
	bool flag;					//正面还是反面
	QTimer *timer1,*timer2;
	int max = 8;				//照片的最大值
	int min = 1;				//照片的最小值
	bool win;					//用于最后判断是否胜利
private:
	bool bl;
	QPixmap pix;
	
};
