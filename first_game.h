#pragma once
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif
#include <QtWidgets/QMainWindow>
#include "ui_first_game.h"
#include<QPainter>
#include<QDebug>
#include"choose.h"
#include<QTimer>
#include <QMessageBox>
class first_game : public QMainWindow
{
	Q_OBJECT

public:
	first_game(QWidget *parent = Q_NULLPTR);
	void paintEvent(QPaintEvent* event);
	choose* newchoose;
private:
	Ui::first_gameClass ui;
};
