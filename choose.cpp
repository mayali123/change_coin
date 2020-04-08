#include "choose.h"


choose::choose(QWidget* parent)
	: QMainWindow(parent)
{
	//设置窗口
	this->setFixedSize(480, 800);
	this->setWindowIcon(QIcon(":/first_game/Resources/Coin0001.png"));
	this->setWindowTitle("选择");

	//设置按键
	btn2 = new MyPushButton(":/first_game/Resources/BackButton.png", ":/first_game/Resources/BackButtonSelected.png");
	btn2->setParent(this);
	btn2->move(this->width() - btn2->width(), this->height() - btn2->height());
	
	//菜单栏 
	QMenuBar* bar = menuBar();
	this ->setMenuBar(bar);
	QMenu *start=bar->addMenu("开始");
	QAction *close= start->addAction("退出");
	connect(close, &QAction::triggered, [=] (){
		this->close();
		});//将“退出”连接到关闭窗口

	//返回的声音
	backsound = new QSound(":/first_game/Resources/BackButtonSound.wav",this);

	//发出信号，返回开始菜单
	connect(btn2, &MyPushButton::clicked, [=]() {
		emit this->changeBack();
		//播放返回声音
		backsound->play();
		});
	
	Play = NULL;
	//选择关卡的声音
	QSound* chooseSound = new QSound(":/first_game/Resources/TapButtonSound.wav", this);



	//选择关卡按钮
	int i,y;
	for(i=0;i<4;i+=1)
		for(y=0;y<5;y+=1)
		{ 
			//选择关卡按钮
			MyPushButton* btn3 = new MyPushButton(":/first_game/Resources/LevelIcon.png");
			btn3->setParent(this);
			btn3->move(50+i*100,190+y*100);

			//用QLabel来显示字
			QLabel *text= new QLabel(this);

			//设置label大小，主要目的是把字放在按键的中间
			text->setFixedSize(btn3->width(), btn3->height());

			//显示字
			text->setText(QString("%1").arg(y*4+i+1));
			text->move(50 + i * 100, 190 + y * 100);

			//label水平和竖直对齐
			text->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

			//51号信号的穿透属性
			text->setAttribute(Qt::WA_TransparentForMouseEvents);

			connect(btn3, &MyPushButton::clicked, [=](){
				//qDebug() << QString("选择了%1关").arg(y * 4 + i + 1);
				chooseSound->play();
				this->hide();
				Play = new play(y * 4 + i + 1);
				upShow();//显示Play，并接受信号
				});
		}
}

void choose::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	//设置背景图片
	painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/first_game/Resources/OtherSceneBg.png"));
	QPixmap pix;
	pix.load(":/first_game/Resources/Title.png");
	//pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
	painter.drawPixmap(10, 30, pix);
}


//设置
void choose::myslot(int i,bool bl)
{
	qDebug() << "接收信号";
	Play->close();
	if(bl)
		Play = new play(i+1);
	else
		Play = new play(i);
	Play->setGeometry(this->geometry());
	Play->show();
	upShow();	//显示Play，并接受信号
}


//显示Play，并接受信号
void choose::upShow()
{
	//设置位置
	Play->setGeometry(this->geometry());
	Play->show();

	//接受play发来的信号
	connect(Play, &play::backChoose, [=]() {
		QTimer::singleShot(50, this, [=]() {
			Play->close();
			this->setGeometry(Play->geometry());
			delete Play;
			this->show();
			qDebug() << " back choose";
			});
		});
	connect(Play, &play::changeplay, this, &choose::myslot);
}