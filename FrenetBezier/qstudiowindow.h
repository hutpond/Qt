#ifndef QSTUDIOWINDOW_H
#define QSTUDIOWINDOW_H

#include <QMainWindow>

class QCenterWidget;

class QStudioWindow : public QMainWindow
{
  Q_OBJECT

public:
  QStudioWindow(QWidget *parent = nullptr);
  ~QStudioWindow();

protected:
  void createMenu();

protected slots:
  void onActionLoadReference();

private:
  QCenterWidget *m_pWdgCentral;
};
#endif // QSTUDIOWINDOW_H
