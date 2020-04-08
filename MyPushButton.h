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
	MyPushButton(QString normalImg,QString pressImg="");	//��д���캯��
	
	void zoom(bool i,int y=8);										//�����ĵ���

	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void load();
	~MyPushButton();

private:
	QString normalImgPath;									//Ĭ����ʾͼƬ·��
	QString pressedImgPath;									 //���º���ʾͼƬ·��
	QPixmap pix;
	bool bl;

};
