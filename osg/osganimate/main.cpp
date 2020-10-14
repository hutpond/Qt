#include <QApplication>

#include "QAnimateWidget.h"

int main(int argc, char **argv)
{
  QApplication a(argc, argv);

  QAnimateWidget w(nullptr);
  w.setGeometry(720, 350, 600, 400);
  w.show();

  return a.exec();
}
