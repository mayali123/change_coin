#include "MyCoin.h"
#include<QDebug>
MyCoin::MyCoin(QString butImg)
{
	 bl =pix.load(butImg);
	 //����ͼƬ
	 load();
	 timer1 = new QTimer(this);
	 timer2=new QTimer(this);
	 //��ҷ�����
	 connect(timer1, &QTimer::timeout, [=]() {
		 bl = pix.load(QString(":/first_game/Resources/Coin000%1.png").arg(this->min++));
		 load(); //����ͼƬ
		 if (this->min > this->max)
		 {
			 this->min = 1;
			 timer1->stop();
		 }
		 });
	 //���ҷ����
	 connect(timer2, &QTimer::timeout, [=]() {
		 bl = pix.load(QString(":/first_game/Resources/Coin000%8.png").arg(this->max--));
		 load(); //����ͼƬ
		 if (this->max < this->min)
		 {
			 this->max = 8;
			 timer2->stop();
		 }
		 });
}

MyCoin::~MyCoin()
{
}
void MyCoin::load()
{
	if (bl == false)
		return;
	pix = pix.scaled(pix.width() * 1.3, pix.height() * 1.3);
	this->setFixedSize(pix.width(), pix.height());
	//���ò�����ͼƬ����ʽ������ȥ�߿�
	this->setStyleSheet("QPushButton{border:0px;}");
	//����ͼƬ
	this->setIcon(pix);
	//����ͼƬ�Ĵ�С
	this->setIconSize(QSize(pix.width(), pix.height()));
	
}

void MyCoin::changecoin()
{
	if (this->flag)//���
	{
		timer1->start(30);
		this->flag = false;
	}
	else
	{
		timer2->start(30);
		this->flag = true;
	}//����
}

void MyCoin::mousePressEvent(QMouseEvent* event)
{
	if (win)
		return;
	else
		QPushButton::mousePressEvent(event); 
}