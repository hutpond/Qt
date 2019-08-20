#ifndef QMAINWIDGET_H
#define QMAINWIDGET_H

#include <QWidget>

class QMainWidget : public QWidget
{
  Q_OBJECT

  enum
  {
    start,
    end,
    control1,
    control2,
    number
  };

public:
  QMainWidget(QWidget *parent = 0);
  ~QMainWidget();

protected:
  void paintEvent(QPaintEvent *);
  void mousePressEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);
  void mouseMoveEvent(QMouseEvent *);

private:
  QPointF m_ptf[number];
  int m_nNumber;
  int m_nSelect;
};

#endif // QMAINWIDGET_H
