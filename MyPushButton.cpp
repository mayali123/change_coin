#include "MyPushButton.h"

MyPushButton::MyPushButton(QString normalImg, QString pressImg )
{
	this->normalImgPath = normalImg;	//用于保存按下之前的照片
	this->pressedImgPath = pressImg;	//同于保存按下之后的照片
	//加载图片，并将返回值赋给 bool 型的bl,用于判断图片是否正常打开，正常打开返回true
	bl = pix.load(this->normalImgPath);
	load();								//加载图片
	
}

MyPushButton::~MyPushButton()
{
}

//实现按键的弹起效果，这个代码基本上靠复制
void MyPushButton::zoom(bool i,int y)
{
	//int y=8;    y的默认值是8
	//创建QPropertyAnimation
	QPropertyAnimation* am = new QPropertyAnimation(this, "geometry");
	//设置时间间隔，单位毫秒
	am->setDuration(1200);
	if (i)//当y为正值时，向上走
	{
		am->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
		am->setEndValue(QRect(this->x(), this->y() - y, this->width(), this->height()));
	}
	else//接着上面那个向下走
	{
		am->setStartValue(QRect(this->x(), this->y() + y, this->width(), this->height()));
		am->setEndValue(QRect(this->x(), this->y() , this->width(), this->height()));
	}
	
	//设置进行的曲线
	am->setEasingCurve(QEasingCurve::OutBounce);
	am->start();
}
//对有两张图片的进行操作
void MyPushButton::mousePressEvent(QMouseEvent* event)
{
	if (this->pressedImgPath != "")//判断是否有按下后的照片
	{
		pix.load(this->pressedImgPath);
		load();
	}
	QPushButton::mousePressEvent(event);//将其他事件交给父类
}
void MyPushButton::mouseReleaseEvent(QMouseEvent* event)
{
	if (this->pressedImgPath != "")//判断是否有按下后的照片
	{
		pix.load(this->normalImgPath);
		load();
	}
	QPushButton::mouseReleaseEvent(event);//将其他事件交给父类
}

//加载图片
void MyPushButton::load()
{
	if (bl == false)
		return;
	pix=pix.scaled(pix.width()*1.3,pix.height()*1.3);	//放大图片
	this->setFixedSize(pix.width(), pix.height());		//设置this窗口大小
	//设置不规则图片的样式表，就是去边框
	this->setStyleSheet("QPushButton{border:0px;}");
	//设置图片
	this->setIcon(pix);									//设置一个照片
	//设置图片的大小
	this->setIconSize(QSize(pix.width(), pix.height()));	//将照片的大小设为图片的大小
}

