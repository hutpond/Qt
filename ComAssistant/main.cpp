#include "qcommainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QComMainWindow w;
    w.showMaximized();
    w.show();

    return a.exec();
}
