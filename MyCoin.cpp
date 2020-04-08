#include "MyCoin.h"
#include<QDebug>
MyCoin::MyCoin(QString butImg)
{
	 bl =pix.load(butImg);
	 //加载图片
	 load();
	 timer1 = new QTimer(this);
	 timer2=new QTimer(this);
	 //金币翻银币
	 connect(timer1, &QTimer::timeout, [=]() {
		 bl = pix.load(QString(":/first_game/Resources/Coin000%1.png").arg(this->min++));
		 load(); //加载图片
		 if (this->min > this->max)
		 {
			 this->min = 1;
			 timer1->stop();
		 }
		 });
	 //银币翻金币
	 connect(timer2, &QTimer::timeout, [=]() {
		 bl = pix.load(QString(":/first_game/Resources/Coin000%8.png").arg(this->max--));
		 load(); //加载图片
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
	//设置不规则图片的样式表，就是去边框
	this->setStyleSheet("QPushButton{border:0px;}");
	//设置图片
	this->setIcon(pix);
	//设置图片的大小
	this->setIconSize(QSize(pix.width(), pix.height()));
	
}

void MyCoin::changecoin()
{
	if (this->flag)//金币
	{
		timer1->start(30);
		this->flag = false;
	}
	else
	{
		timer2->start(30);
		this->flag = true;
	}//银币
}

void MyCoin::mousePressEvent(QMouseEvent* event)
{
	if (win)
		return;
	else
		QPushButton::mousePressEvent(event); 
}