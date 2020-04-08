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
	void startStop();				//ת��ֹͣ�Ϳ�ʼ��ͼ�꣬ͬʱ��ͣ�Ϳ�ʼ��ʱ��
signals:
	void changeplay(int i,bool l);	//�Զ����źţ������һ�ص�ת��
	void backChoose();				//�Զ����źţ�����choose����
private:
	int index;				//���ڱ���ؿ�
	int a[4][4];			//���ڱ���date��ֵ
	MyCoin *mycoin[4][4];
	bool iswin;				
	MyPushButton* win;		//ʤ��ͼ��
	int time1;				//���ڱ���ʱ��
	MyPushButton* stopBtn;	//ֹͣ��
	QSound* backsound;		//��������
	QTimer* timer;			//��ʱ��
	bool isStop;			//�����Ƿ�Ҫֹͣ��ʱ����true����Ҫֹͣ
	int count ;				//���ڼ���
	QPixmap pix;
};

