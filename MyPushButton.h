#pragma once
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif
#include <QPushButton>
#include<QString>
#include<QDebug>
#include <QPropertyAnimation> 
class MyPushButton : public QPushButton
{
	Q_OBJECT

public:
	MyPushButton(QString normalImg,QString pressImg="");	//重写构造函数
	
	void zoom(bool i,int y=8);										//按键的弹跳

	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void load();
	~MyPushButton();

private:
	QString normalImgPath;									//默认显示图片路径
	QString pressedImgPath;									 //按下后显示图片路径
	QPixmap pix;
	bool bl;

};
