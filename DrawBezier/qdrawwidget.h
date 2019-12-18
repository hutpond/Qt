#ifndef QDRAWWIDGET_H
#define QDRAWWIDGET_H

#include <QWidget>

class QDrawWidget : public QWidget
{
  Q_OBJECT

public:
  enum
  {
    start,
    end,
    control1,
    control2,
    number
  };

public:
  explicit QDrawWidget(QWidget *parent = nullptr);

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

#endif // QDRAWWIDGET_H
