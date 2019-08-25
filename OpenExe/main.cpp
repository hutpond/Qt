#include "QOpenExeWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QOpenExeWidget w;
	w.show();
	return a.exec();
}
