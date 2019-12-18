#include "qstudiowindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QStudioWindow w;
  w.showMaximized();
  return a.exec();
}
