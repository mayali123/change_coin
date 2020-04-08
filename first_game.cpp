#include "first_game.h"
#include<QAction>
#include"MyPushButton.h"
#include<QSound>
first_game::first_game(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.actionabout, &QAction::triggered, [=] (){
		//打开介绍
		QMessageBox::about(this,"关于游戏","你的目标就是将所有的银币翻成金币，而翻动硬币时会带动周围的硬币翻动");
		});


	//设置窗口
	this->setFixedSize(480, 800);
	this->setWindowIcon(QIcon(":/first_game/Resources/Coin0001.png"));
	this->setWindowTitle("翻金币");
	connect(ui.actionclose, &QAction::triggered, this,&QMainWindow::close);
	//将画家画的东西显示出来
	update();		
	
	//开始按钮的声音
	QSound* startSound = new QSound(":/first_game/Resources/TapButtonSound.wav",this);
	//startSound->setLoops(-1);   //设置循环的次数，如果值是-1则无限循环


	//用自己封装的类new一个btn，并将它放在开始窗口
	MyPushButton *btn =new MyPushButton (":/first_game/Resources/MenuSceneStartButton.png" );
	btn->setParent(this);

	//new出来一个选择窗口
	newchoose =new choose;

	btn->move(this->width()*0.5-btn->width()*0.5,this->height()*0.7);
	connect(btn, &QPushButton::clicked, [=]() {
		//播放音乐
		startSound->play();
		btn->zoom(true);//实现按键的弹起
		btn->zoom(false);
		//QTimer::singleShot作用是 延时，需要包含QTimer头文件
		QTimer::singleShot(90, this, [=]() {
			this->hide();								//隐藏this
			newchoose->setGeometry(this->geometry());	//将newchoose的位置设为this的位置
			newchoose->show();							//newchoose
			});
		});
	//接受信号，并回到开始窗口
	connect(newchoose, &choose::changeBack,[=]() {
			newchoose->hide();
			//设置返回的位置
			this->setGeometry(newchoose->geometry());
			this->show();
		});

}


void first_game::paintEvent(QPaintEvent* event)
{
	//创建一个画家，需要包含QPainter头文件
	QPainter painter(this);
	//画家画图片
	painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/first_game/Resources/PlayLevelSceneBg.png"));

	QPixmap pix;
	pix.load(":/first_game/Resources/Title.png");
	//对pix按比例伸缩
	pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);//将图片设置为原来的0.5倍
	painter.drawPixmap(10, 30,pix);
}
