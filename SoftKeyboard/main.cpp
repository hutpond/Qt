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

  QHmiSoftKeyboard keyboard(QHmiSoftKeyboard::Alphabet, &w);
  keyboard.setGeometry(0, 0, 683, 270);

  QTextEdit textEdit(&w);
  textEdit.setGeometry(0, 300, 800, 200);

  w.show();
  return a.exec();
}
