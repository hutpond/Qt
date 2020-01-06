#include "QHmiSoftKeyboard.h"

#include <QApplication>
#include <QScreen>
#include <QTextEdit>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QWidget w;

  QList<QScreen *> screens = QGuiApplication::screens();
  QRect rect = screens.at(0)->availableGeometry();
  QPoint pt = rect.center();
  rect.setSize(QSize(800, 600));
  rect.moveCenter(pt);
  w.setGeometry(rect);

  QHmiSoftKeyboard keyboard(&w);
  keyboard.setGeometry(0, 0, 683, 220);

  QTextEdit textEdit(&w);
  textEdit.setGeometry(0, 250, 800, 200);

  w.show();
  return a.exec();
}
