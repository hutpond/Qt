#include "QShowWidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QShowWidget w;
  w.show();
  return a.exec();
}
