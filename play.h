#pragma once
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif
#include <qmainwindow.h>
#include<QMenubar>
#include<QPainter>
#include"MyPushButton.h"
#include<QTimer>
#include<QLabel>
#include<QFont>
#include"MyCoin.h"
#include "dataconfig.h"
#include<QDebug>
#include<QSound>
class play :
	public QMainWindow
{
	Q_OBJECT;
public:
	play(int i);
	void paintEvent(QPaintEvent* event);
	void startStop();				//转化停止和开始的图标，同时暂停和开始计时器
signals:
	void changeplay(int i,bool l);	//自定义信号，完成下一关的转化
	void backChoose();				//自定义信号，返回choose界面
private:
	int index;				//用于保存关卡
	int a[4][4];			//用于保存date的值
	MyCoin *mycoin[4][4];
	bool iswin;				
	MyPushButton* win;		//胜利图标
	int time1;				//用于保存时间
	MyPushButton* stopBtn;	//停止键
	QSound* backsound;		//返回声音
	QTimer* timer;			//计时器
	bool isStop;			//保存是否要停止计时器，true代表要停止
	int count ;				//用于计数
	QPixmap pix;
};

