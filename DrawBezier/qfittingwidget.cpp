#include <QPainter>
#include <QMouseEvent>
#include "qfittingwidget.h"
#include "QBezierCurve.h"

QFittingWidget::QFittingWidget(QWidget *parent) : QWidget(parent)
{

}

void QFittingWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  QPen pen;

  QBezierCurve bezier_curve;

  pen.setColor(Qt::black);
  pen.setWidth(1);
  painter.setBrush(Qt::white);
  painter.setPen(pen);
  for (const auto &pt : m_ptfs) {
    painter.drawEllipse(pt, 4, 4);

    bezier_curve.addPoint(pt);
  }

  if (m_ptfs.size() == 5) {
    bezier_curve.calcBezier();
    const auto &beziers = bezier_curve.getBezier();

    for (const auto &bezier :beziers) {
      QPainterPath path(bezier.start);
      path.cubicTo(bezier.control, bezier.control2, bezier.end);
      painter.setBrush(Qt::NoBrush);
      painter.setPen(pen);
      painter.drawPath(path);

      painter.setBrush(Qt::magenta);
      painter.setPen(pen);
      painter.drawEllipse(bezier.control, 4, 4);
      painter.drawEllipse(bezier.control2, 4, 4);
    }

  }
}

void QFittingWidget::mousePressEvent(QMouseEvent *e)
{
  if (Qt::RightButton == e->button()) {
    m_ptfs.clear();
  }
  else if (Qt::LeftButton == e->button()) {
    if (m_ptfs.size() < 5) {
      QPointF ptf = e->pos();
      m_ptfs.push_back(ptf);
    }
  }
  this->update();
}
