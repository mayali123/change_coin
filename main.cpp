#include "first_game.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	first_game w;
	w.show();

	return a.exec();
}
