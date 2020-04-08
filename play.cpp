#include "play.h"
#include<QDebug>
play::play(int  i)
{
	//qDebug() << "进入" << i << "关";
	
	//保存本关 关卡
	this->index = i;
	//计时
	time1=1;

	//设置窗口
	this->setFixedSize(480, 800);
	this->setWindowIcon(QIcon(":/first_game/Resources/Coin0001.png"));
	this->setWindowTitle("玩耍");

	//设置状态栏
	QMenuBar* bar = menuBar();
	this->setMenuBar(bar);
	QMenu* open = bar->addMenu("开始");
	QAction* close = open->addAction("关闭");
	connect(close, &QAction::triggered, [=]() {
		this->close();
		});

	//显示图片
	update();

	
	//翻金币音效
	QSound * flipSound = new QSound(":/first_game/Resources/ConFlipSound.wav", this);

	//胜利按钮音效
	QSound* winSound = new QSound(":/first_game/Resources/LevelWinSound.wav", this);

	//设置返回键
	MyPushButton *btn4 = new MyPushButton(":/first_game/Resources/BackButton.png",":/first_game/Resources/BackButtonSelected.png");
	btn4->setParent(this);
	btn4->move(this->width()-btn4->width(),this->height()-btn4->height());

	//返回的声音
	backsound = new QSound(":/first_game/Resources/BackButtonSound.wav", this);

	//自定义信号的发射
	connect(btn4, &MyPushButton::clicked, [=]() {
		//播放返回声音
		backsound->play();
		//qDebug() << " 发出声音";
		//发出返回的信号
		emit this->backChoose();	
		});

	
	//显示关卡
	QLabel* text = new QLabel(this);
	QLabel* text2 = new QLabel(this);
	QFont font("楷体",20,65);
	text->setFont(font);
	text2->setFont(font);
	//text->setAlignment(Qt::AlignLeft);
	text->setText(QString("第%1关").arg(index));
	text->move(text->width(),this->height()-text->height()-10);

	//显示时间
	timer = new QTimer(this);
	timer->start(1000);
	
	//设置texe2的框的位置和大小
	text2->setGeometry((this->width() - text2->width()) * 0.5, this->height() * 0.7,120,50);
	connect(timer, &QTimer::timeout, [=]() {
		text2->setText(QString("耗时%1s").arg(time1++));
		});
	

	//创建出胜利的图片
	win = new MyPushButton(":/first_game/Resources/LevelCompletedDialogBg.png");
	win->setParent(this);
	win->move((this->width()-win->width()) * 0.5,-win->height());


	//胜利之后的再来一次
	MyPushButton* againBtn = new MyPushButton(":/first_game/Resources/AGAIN.png");
	againBtn->setParent(this);
	againBtn->move((this->width() - againBtn->width()) * 0.2, -againBtn->height());

	//重新玩一次的信号发射
	connect(againBtn, &MyPushButton::clicked, [=]() {
		backsound->play();
		emit this->changeplay(this->index,false);
		qDebug() << "发出信号";
		});

	//下一关
	MyPushButton* nextBtn = new MyPushButton(":/first_game/Resources/NEXT.png");
	nextBtn->setParent(this);
	nextBtn->move((this->width() - nextBtn->width()) * 0.8, -nextBtn->height());
	connect(nextBtn, &MyPushButton::clicked, [=]() {
		backsound->play();
		emit this->changeplay(this->index, true);
		qDebug() << "发出信号";
		});

	//创建计时器的按钮
	stopBtn = new MyPushButton(":/first_game/Resources/STOP.png");
	stopBtn->setParent(this);
	stopBtn->move(this->width()-stopBtn->width(),stopBtn->height());
	isStop = true;
	//初始化数组a
	dataConfig date;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			a[i][j] = date.mData[this->index][i][j];
	}
	
	for(int i=0;i<4;i++)
		for (int j = 0; j < 4; j++)
		{
			//创建金币背景
			MyPushButton* bg = new MyPushButton(":/first_game/Resources/BoardNode(1).png");
			bg->setParent(this);
			bg->move(110+ i * 62.5, 230 + j * 62.5);
			
			//startStop(isStop);
				//实现计时器的暂停和开始
				//qDebug ()<< "lll";
			count = 0;
				connect(stopBtn, &MyPushButton::clicked, [=]() {
					count++;
					if (count == 15)
						count = 0;
					startStop();				//转化停止和开始的图标，同时暂停和开始计时器
					}); 
			
			//创建金币
			QString str;
			if (a[i][j] == 1)
				str = ":/first_game/Resources/Coin0001.png";//金币
			else 
				str = ":/first_game/Resources/Coin0008.png";//银币
			MyCoin* coin = new MyCoin(str);
			//对posx，posy,flag赋值
			coin->posx = i;
			coin->posy = j;
			coin->flag = a[i][j];

			//显示金币
			coin->setParent(this);
			coin->move(113 + i * 62.5, 234 + j * 62.5);


			//记录金币位置
			mycoin[i][j] = coin;
			mycoin[i][j]->win = false;//用于判断是否要禁止鼠标对按键的点击


			connect(coin, &MyCoin::clicked, [=]() {
				//播放翻金币的声音
				flipSound->play();

				//解决手速过快，导致胜利时出现bug
				for (int i = 0; i < 4; i++)
					for (int j = 0; j < 4; j++)
						mycoin[i][j]->win = true;

				//翻硬币
				coin->changecoin();
				//同步一下内部数组
				a[i][j] = a[i][j] == 0 ? 1 : 0;//如果为0则为1，反之则为0
				//翻周围的金币
				QTimer::singleShot(150, this, [=]() {
					//让上面的币翻
					if (coin->posy + 1 <= 3)
					{
						mycoin[i][j + 1]->changecoin();
						a[i][j + 1] = a[i][j + 1] == 0 ? 1 : 0;
					}
					//让下面的币翻
					if (coin->posy - 1 >= 0)
					{
						mycoin[i][j - 1]->changecoin();
						a[i][j - 1] = a[i][j - 1] == 0 ? 1 : 0;
					}
					//向让右面的币翻
					if (coin->posx + 1 <= 3)
					{
						mycoin[i + 1][j]->changecoin();
						a[i + 1][j] = a[i + 1][j] == 0 ? 1 : 0;
					}
					//向让左面的币翻
					if (coin->posx - 1 >= 0)
					{
						mycoin[i - 1][j]->changecoin();
						a[i - 1][j] = a[i - 1][j] == 0 ? 1 : 0;
					}
					//解决手速过快，导致胜利时出现bug
					for (int i = 0; i < 4; i++)
						for (int j = 0; j < 4; j++)
							mycoin[i][j]->win = false;


					//检查是否全为金币
					this->iswin = true;
					for (int i = 0; i < 4; i++)
						for (int j = 0; j < 4; j++)
							if (mycoin[i][j]->flag == false)
							{
								this->iswin = false;
								break;
							}

					if (this->iswin == true)
					{ 
						win->zoom(true,-200);//弹出胜利图片
						againBtn->zoom(true,-650);//弹出再玩一次
						nextBtn->zoom(true, -650);//弹出next
						for (int i = 0; i < 4; i++)			//让鼠标不能再点
							for (int j = 0; j < 4; j++)
								mycoin[i][j]->win = true;
						//计时器停止
						timer->stop();
						//让时间归零
						time1 = 1;
						//播放胜利的声音
						winSound->play();
					}
					});
				});
		}
}

void play::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	QPixmap pix;
	pix.load(":/first_game/Resources/PlayLevelSceneBg.png");
	painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

//转化停止和开始的图标，同时暂停和开始计时器
void play::startStop()
{		//isStop为true表示要停止
	if (isStop && count == 14)						//判断count是否为14主要的目的是让isStop只改变一次
		pix.load(":/first_game/Resources/START.png");		//加载开始图标
	else if (!isStop && count == 14)
		pix.load(":/first_game/Resources/STOP.png");	//加载开始图标
	else
		return;										//如果count不为14则无反应
	pix = pix.scaled(pix.width() * 1.3, pix.height() * 1.3);	//把尺寸图片变大
	stopBtn->setIconSize(QSize(pix.width(), pix.height()));		//设置图片的大小
	stopBtn->setIcon(pix);							
	backsound->play();					
	if (isStop)
		timer->stop();						//计时器停止
	else 
		timer->start();
	for (int i = 0; i < 4; i++)				//禁止鼠标对硬币的点击
		for (int j = 0; j < 4; j++)
			mycoin[i][j]->win = isStop;
	isStop = !isStop;
}