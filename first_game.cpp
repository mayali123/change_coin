#include "first_game.h"
#include<QAction>
#include"MyPushButton.h"
#include<QSound>
first_game::first_game(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.actionabout, &QAction::triggered, [=] (){
		//�򿪽���
		QMessageBox::about(this,"������Ϸ","���Ŀ����ǽ����е����ҷ��ɽ�ң�������Ӳ��ʱ�������Χ��Ӳ�ҷ���");
		});


	//���ô���
	this->setFixedSize(480, 800);
	this->setWindowIcon(QIcon(":/first_game/Resources/Coin0001.png"));
	this->setWindowTitle("�����");
	connect(ui.actionclose, &QAction::triggered, this,&QMainWindow::close);
	//�����һ��Ķ�����ʾ����
	update();		
	
	//��ʼ��ť������
	QSound* startSound = new QSound(":/first_game/Resources/TapButtonSound.wav",this);
	//startSound->setLoops(-1);   //����ѭ���Ĵ��������ֵ��-1������ѭ��


	//���Լ���װ����newһ��btn�����������ڿ�ʼ����
	MyPushButton *btn =new MyPushButton (":/first_game/Resources/MenuSceneStartButton.png" );
	btn->setParent(this);

	//new����һ��ѡ�񴰿�
	newchoose =new choose;

	btn->move(this->width()*0.5-btn->width()*0.5,this->height()*0.7);
	connect(btn, &QPushButton::clicked, [=]() {
		//��������
		startSound->play();
		btn->zoom(true);//ʵ�ְ����ĵ���
		btn->zoom(false);
		//QTimer::singleShot������ ��ʱ����Ҫ����QTimerͷ�ļ�
		QTimer::singleShot(90, this, [=]() {
			this->hide();								//����this
			newchoose->setGeometry(this->geometry());	//��newchoose��λ����Ϊthis��λ��
			newchoose->show();							//newchoose
			});
		});
	//�����źţ����ص���ʼ����
	connect(newchoose, &choose::changeBack,[=]() {
			newchoose->hide();
			//���÷��ص�λ��
			this->setGeometry(newchoose->geometry());
			this->show();
		});

}


void first_game::paintEvent(QPaintEvent* event)
{
	//����һ�����ң���Ҫ����QPainterͷ�ļ�
	QPainter painter(this);
	//���һ�ͼƬ
	painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/first_game/Resources/PlayLevelSceneBg.png"));

	QPixmap pix;
	pix.load(":/first_game/Resources/Title.png");
	//��pix����������
	pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);//��ͼƬ����Ϊԭ����0.5��
	painter.drawPixmap(10, 30,pix);
}
