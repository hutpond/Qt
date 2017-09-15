#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString strStyle = "QTreeView::item{"
        "margin:13px;"
        "background: #5B677A;"
        "background-clip: margin;}";
    MainWindow w;
    //w.setStyleSheet(strStyle);
    w.show();

    return a.exec();
}
