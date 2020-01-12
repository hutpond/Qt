#include "QHmiTableWidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QHmiTableWidget w(12, 7);
  w.setGeometry(400, 200, 800, 600);
  w.setHeaderWidthPercent(0.06);
  w.setHeaderHeightPercent(0.05);
  w.show();
  return a.exec();
}
