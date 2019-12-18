#ifndef QFITTINGWIDGET_H
#define QFITTINGWIDGET_H

#include <QWidget>

class QFittingWidget : public QWidget
{
  Q_OBJECT
public:
  explicit QFittingWidget(QWidget *parent = nullptr);

  void paintEvent(QPaintEvent *);
  void mousePressEvent(QMouseEvent *);

private:
  QVector<QPointF> m_ptfs;
};

#endif // QFITTINGWIDGET_H
