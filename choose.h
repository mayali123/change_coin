#pragma once
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif
#include <qmainwindow.h>
#include<QPainter>
#include"MyPushButton.h"
#include<QLabel>
#include<QMenubar>
#include"play.h"
#include<QDebug>
#include<QTimer>
#include<QSound>
class choose :public QMainWindow
{
	Q_OBJECT;								//在使用信号槽时必须要有"Q_OBJECT"
public:
	choose(QWidget *parent = Q_NULLPTR);
	void paintEvent(QPaintEvent* event);
	void upShow();	//显示Play，并接受信号
	play* Play;
	MyPushButton* btn2;
	QSound* backsound;
signals:
	void changeBack();
public slots:
	void myslot(int i,bool bl);
};

