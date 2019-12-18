#ifndef QMAINWIDGET_H
#define QMAINWIDGET_H

#include <QWidget>

class QDrawWidget;
class QFittingWidget;

class QMainWidget : public QWidget
{
  Q_OBJECT

public:
  QMainWidget(QWidget *parent = 0);
  ~QMainWidget();

protected:
  void resizeEvent(QResizeEvent *);

private:
  QDrawWidget *m_pWdgDraw;
  QFittingWidget *m_pWdgFitting;
};

#endif // QMAINWIDGET_H
