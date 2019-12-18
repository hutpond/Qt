#ifndef QSTUDIOWINDOW_H
#define QSTUDIOWINDOW_H

#include <QMainWindow>

class QStudioWindow : public QMainWindow
{
  Q_OBJECT

public:
  QStudioWindow(QWidget *parent = nullptr);
  ~QStudioWindow();
};
#endif // QSTUDIOWINDOW_H
