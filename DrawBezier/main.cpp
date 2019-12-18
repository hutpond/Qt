#include "qmainwidget.h"
#include <QApplication>
#include <QScreen>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QMainWidget w;
  QList<QScreen *> screens = QGuiApplication::screens();
  QRect rect = screens.at(0)->availableGeometry();
  QPoint pt = rect.center();
  rect.setSize(QSize(1024, 768));
  rect.moveCenter(pt);
  w.setGeometry(rect);
  w.show();

  return a.exec();
}
