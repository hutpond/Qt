#include "qmiguanwidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QMiGuanWidget w;
	w.show();
	return a.exec();
}
