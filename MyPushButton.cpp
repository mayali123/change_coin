#include "MyPushButton.h"

MyPushButton::MyPushButton(QString normalImg, QString pressImg )
{
	this->normalImgPath = normalImg;	//���ڱ��水��֮ǰ����Ƭ
	this->pressedImgPath = pressImg;	//ͬ�ڱ��水��֮�����Ƭ
	//����ͼƬ����������ֵ���� bool �͵�bl,�����ж�ͼƬ�Ƿ������򿪣������򿪷���true
	bl = pix.load(this->normalImgPath);
	load();								//����ͼƬ
	
}

MyPushButton::~MyPushButton()
{
}

//ʵ�ְ����ĵ���Ч���������������Ͽ�����
void MyPushButton::zoom(bool i,int y)
{
	//int y=8;    y��Ĭ��ֵ��8
	//����QPropertyAnimation
	QPropertyAnimation* am = new QPropertyAnimation(this, "geometry");
	//����ʱ��������λ����
	am->setDuration(1200);
	if (i)//��yΪ��ֵʱ��������
	{
		am->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
		am->setEndValue(QRect(this->x(), this->y() - y, this->width(), this->height()));
	}
	else//���������Ǹ�������
	{
		am->setStartValue(QRect(this->x(), this->y() + y, this->width(), this->height()));
		am->setEndValue(QRect(this->x(), this->y() , this->width(), this->height()));
	}
	
	//���ý��е�����
	am->setEasingCurve(QEasingCurve::OutBounce);
	am->start();
}
//��������ͼƬ�Ľ��в���
void MyPushButton::mousePressEvent(QMouseEvent* event)
{
	if (this->pressedImgPath != "")//�ж��Ƿ��а��º����Ƭ
	{
		pix.load(this->pressedImgPath);
		load();
	}
	QPushButton::mousePressEvent(event);//�������¼���������
}
void MyPushButton::mouseReleaseEvent(QMouseEvent* event)
{
	if (this->pressedImgPath != "")//�ж��Ƿ��а��º����Ƭ
	{
		pix.load(this->normalImgPath);
		load();
	}
	QPushButton::mouseReleaseEvent(event);//�������¼���������
}

//����ͼƬ
void MyPushButton::load()
{
	if (bl == false)
		return;
	pix=pix.scaled(pix.width()*1.3,pix.height()*1.3);	//�Ŵ�ͼƬ
	this->setFixedSize(pix.width(), pix.height());		//����this���ڴ�С
	//���ò�����ͼƬ����ʽ������ȥ�߿�
	this->setStyleSheet("QPushButton{border:0px;}");
	//����ͼƬ
	this->setIcon(pix);									//����һ����Ƭ
	//����ͼƬ�Ĵ�С
	this->setIconSize(QSize(pix.width(), pix.height()));	//����Ƭ�Ĵ�С��ΪͼƬ�Ĵ�С
}

