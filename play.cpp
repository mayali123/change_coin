#include "play.h"
#include<QDebug>
play::play(int  i)
{
	//qDebug() << "����" << i << "��";
	
	//���汾�� �ؿ�
	this->index = i;
	//��ʱ
	time1=1;

	//���ô���
	this->setFixedSize(480, 800);
	this->setWindowIcon(QIcon(":/first_game/Resources/Coin0001.png"));
	this->setWindowTitle("��ˣ");

	//����״̬��
	QMenuBar* bar = menuBar();
	this->setMenuBar(bar);
	QMenu* open = bar->addMenu("��ʼ");
	QAction* close = open->addAction("�ر�");
	connect(close, &QAction::triggered, [=]() {
		this->close();
		});

	//��ʾͼƬ
	update();

	
	//�������Ч
	QSound * flipSound = new QSound(":/first_game/Resources/ConFlipSound.wav", this);

	//ʤ����ť��Ч
	QSound* winSound = new QSound(":/first_game/Resources/LevelWinSound.wav", this);

	//���÷��ؼ�
	MyPushButton *btn4 = new MyPushButton(":/first_game/Resources/BackButton.png",":/first_game/Resources/BackButtonSelected.png");
	btn4->setParent(this);
	btn4->move(this->width()-btn4->width(),this->height()-btn4->height());

	//���ص�����
	backsound = new QSound(":/first_game/Resources/BackButtonSound.wav", this);

	//�Զ����źŵķ���
	connect(btn4, &MyPushButton::clicked, [=]() {
		//���ŷ�������
		backsound->play();
		//qDebug() << " ��������";
		//�������ص��ź�
		emit this->backChoose();	
		});

	
	//��ʾ�ؿ�
	QLabel* text = new QLabel(this);
	QLabel* text2 = new QLabel(this);
	QFont font("����",20,65);
	text->setFont(font);
	text2->setFont(font);
	//text->setAlignment(Qt::AlignLeft);
	text->setText(QString("��%1��").arg(index));
	text->move(text->width(),this->height()-text->height()-10);

	//��ʾʱ��
	timer = new QTimer(this);
	timer->start(1000);
	
	//����texe2�Ŀ��λ�úʹ�С
	text2->setGeometry((this->width() - text2->width()) * 0.5, this->height() * 0.7,120,50);
	connect(timer, &QTimer::timeout, [=]() {
		text2->setText(QString("��ʱ%1s").arg(time1++));
		});
	

	//������ʤ����ͼƬ
	win = new MyPushButton(":/first_game/Resources/LevelCompletedDialogBg.png");
	win->setParent(this);
	win->move((this->width()-win->width()) * 0.5,-win->height());


	//ʤ��֮�������һ��
	MyPushButton* againBtn = new MyPushButton(":/first_game/Resources/AGAIN.png");
	againBtn->setParent(this);
	againBtn->move((this->width() - againBtn->width()) * 0.2, -againBtn->height());

	//������һ�ε��źŷ���
	connect(againBtn, &MyPushButton::clicked, [=]() {
		backsound->play();
		emit this->changeplay(this->index,false);
		qDebug() << "�����ź�";
		});

	//��һ��
	MyPushButton* nextBtn = new MyPushButton(":/first_game/Resources/NEXT.png");
	nextBtn->setParent(this);
	nextBtn->move((this->width() - nextBtn->width()) * 0.8, -nextBtn->height());
	connect(nextBtn, &MyPushButton::clicked, [=]() {
		backsound->play();
		emit this->changeplay(this->index, true);
		qDebug() << "�����ź�";
		});

	//������ʱ���İ�ť
	stopBtn = new MyPushButton(":/first_game/Resources/STOP.png");
	stopBtn->setParent(this);
	stopBtn->move(this->width()-stopBtn->width(),stopBtn->height());
	isStop = true;
	//��ʼ������a
	dataConfig date;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			a[i][j] = date.mData[this->index][i][j];
	}
	
	for(int i=0;i<4;i++)
		for (int j = 0; j < 4; j++)
		{
			//������ұ���
			MyPushButton* bg = new MyPushButton(":/first_game/Resources/BoardNode(1).png");
			bg->setParent(this);
			bg->move(110+ i * 62.5, 230 + j * 62.5);
			
			//startStop(isStop);
				//ʵ�ּ�ʱ������ͣ�Ϳ�ʼ
				//qDebug ()<< "lll";
			count = 0;
				connect(stopBtn, &MyPushButton::clicked, [=]() {
					count++;
					if (count == 15)
						count = 0;
					startStop();				//ת��ֹͣ�Ϳ�ʼ��ͼ�꣬ͬʱ��ͣ�Ϳ�ʼ��ʱ��
					}); 
			
			//�������
			QString str;
			if (a[i][j] == 1)
				str = ":/first_game/Resources/Coin0001.png";//���
			else 
				str = ":/first_game/Resources/Coin0008.png";//����
			MyCoin* coin = new MyCoin(str);
			//��posx��posy,flag��ֵ
			coin->posx = i;
			coin->posy = j;
			coin->flag = a[i][j];

			//��ʾ���
			coin->setParent(this);
			coin->move(113 + i * 62.5, 234 + j * 62.5);


			//��¼���λ��
			mycoin[i][j] = coin;
			mycoin[i][j]->win = false;//�����ж��Ƿ�Ҫ��ֹ���԰����ĵ��


			connect(coin, &MyCoin::clicked, [=]() {
				//���ŷ���ҵ�����
				flipSound->play();

				//������ٹ��죬����ʤ��ʱ����bug
				for (int i = 0; i < 4; i++)
					for (int j = 0; j < 4; j++)
						mycoin[i][j]->win = true;

				//��Ӳ��
				coin->changecoin();
				//ͬ��һ���ڲ�����
				a[i][j] = a[i][j] == 0 ? 1 : 0;//���Ϊ0��Ϊ1����֮��Ϊ0
				//����Χ�Ľ��
				QTimer::singleShot(150, this, [=]() {
					//������ıҷ�
					if (coin->posy + 1 <= 3)
					{
						mycoin[i][j + 1]->changecoin();
						a[i][j + 1] = a[i][j + 1] == 0 ? 1 : 0;
					}
					//������ıҷ�
					if (coin->posy - 1 >= 0)
					{
						mycoin[i][j - 1]->changecoin();
						a[i][j - 1] = a[i][j - 1] == 0 ? 1 : 0;
					}
					//��������ıҷ�
					if (coin->posx + 1 <= 3)
					{
						mycoin[i + 1][j]->changecoin();
						a[i + 1][j] = a[i + 1][j] == 0 ? 1 : 0;
					}
					//��������ıҷ�
					if (coin->posx - 1 >= 0)
					{
						mycoin[i - 1][j]->changecoin();
						a[i - 1][j] = a[i - 1][j] == 0 ? 1 : 0;
					}
					//������ٹ��죬����ʤ��ʱ����bug
					for (int i = 0; i < 4; i++)
						for (int j = 0; j < 4; j++)
							mycoin[i][j]->win = false;


					//����Ƿ�ȫΪ���
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
						win->zoom(true,-200);//����ʤ��ͼƬ
						againBtn->zoom(true,-650);//��������һ��
						nextBtn->zoom(true, -650);//����next
						for (int i = 0; i < 4; i++)			//����겻���ٵ�
							for (int j = 0; j < 4; j++)
								mycoin[i][j]->win = true;
						//��ʱ��ֹͣ
						timer->stop();
						//��ʱ�����
						time1 = 1;
						//����ʤ��������
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

//ת��ֹͣ�Ϳ�ʼ��ͼ�꣬ͬʱ��ͣ�Ϳ�ʼ��ʱ��
void play::startStop()
{		//isStopΪtrue��ʾҪֹͣ
	if (isStop && count == 14)						//�ж�count�Ƿ�Ϊ14��Ҫ��Ŀ������isStopֻ�ı�һ��
		pix.load(":/first_game/Resources/START.png");		//���ؿ�ʼͼ��
	else if (!isStop && count == 14)
		pix.load(":/first_game/Resources/STOP.png");	//���ؿ�ʼͼ��
	else
		return;										//���count��Ϊ14���޷�Ӧ
	pix = pix.scaled(pix.width() * 1.3, pix.height() * 1.3);	//�ѳߴ�ͼƬ���
	stopBtn->setIconSize(QSize(pix.width(), pix.height()));		//����ͼƬ�Ĵ�С
	stopBtn->setIcon(pix);							
	backsound->play();					
	if (isStop)
		timer->stop();						//��ʱ��ֹͣ
	else 
		timer->start();
	for (int i = 0; i < 4; i++)				//��ֹ����Ӳ�ҵĵ��
		for (int j = 0; j < 4; j++)
			mycoin[i][j]->win = isStop;
	isStop = !isStop;
}