#include "choose.h"


choose::choose(QWidget* parent)
	: QMainWindow(parent)
{
	//���ô���
	this->setFixedSize(480, 800);
	this->setWindowIcon(QIcon(":/first_game/Resources/Coin0001.png"));
	this->setWindowTitle("ѡ��");

	//���ð���
	btn2 = new MyPushButton(":/first_game/Resources/BackButton.png", ":/first_game/Resources/BackButtonSelected.png");
	btn2->setParent(this);
	btn2->move(this->width() - btn2->width(), this->height() - btn2->height());
	
	//�˵��� 
	QMenuBar* bar = menuBar();
	this ->setMenuBar(bar);
	QMenu *start=bar->addMenu("��ʼ");
	QAction *close= start->addAction("�˳�");
	connect(close, &QAction::triggered, [=] (){
		this->close();
		});//�����˳������ӵ��رմ���

	//���ص�����
	backsound = new QSound(":/first_game/Resources/BackButtonSound.wav",this);

	//�����źţ����ؿ�ʼ�˵�
	connect(btn2, &MyPushButton::clicked, [=]() {
		emit this->changeBack();
		//���ŷ�������
		backsound->play();
		});
	
	Play = NULL;
	//ѡ��ؿ�������
	QSound* chooseSound = new QSound(":/first_game/Resources/TapButtonSound.wav", this);



	//ѡ��ؿ���ť
	int i,y;
	for(i=0;i<4;i+=1)
		for(y=0;y<5;y+=1)
		{ 
			//ѡ��ؿ���ť
			MyPushButton* btn3 = new MyPushButton(":/first_game/Resources/LevelIcon.png");
			btn3->setParent(this);
			btn3->move(50+i*100,190+y*100);

			//��QLabel����ʾ��
			QLabel *text= new QLabel(this);

			//����label��С����ҪĿ���ǰ��ַ��ڰ������м�
			text->setFixedSize(btn3->width(), btn3->height());

			//��ʾ��
			text->setText(QString("%1").arg(y*4+i+1));
			text->move(50 + i * 100, 190 + y * 100);

			//labelˮƽ����ֱ����
			text->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

			//51���źŵĴ�͸����
			text->setAttribute(Qt::WA_TransparentForMouseEvents);

			connect(btn3, &MyPushButton::clicked, [=](){
				//qDebug() << QString("ѡ����%1��").arg(y * 4 + i + 1);
				chooseSound->play();
				this->hide();
				Play = new play(y * 4 + i + 1);
				upShow();//��ʾPlay���������ź�
				});
		}
}

void choose::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	//���ñ���ͼƬ
	painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/first_game/Resources/OtherSceneBg.png"));
	QPixmap pix;
	pix.load(":/first_game/Resources/Title.png");
	//pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
	painter.drawPixmap(10, 30, pix);
}


//����
void choose::myslot(int i,bool bl)
{
	qDebug() << "�����ź�";
	Play->close();
	if(bl)
		Play = new play(i+1);
	else
		Play = new play(i);
	Play->setGeometry(this->geometry());
	Play->show();
	upShow();	//��ʾPlay���������ź�
}


//��ʾPlay���������ź�
void choose::upShow()
{
	//����λ��
	Play->setGeometry(this->geometry());
	Play->show();

	//����play�������ź�
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