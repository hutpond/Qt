#include <QMouseEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QCursor>
#include <QDebug>
#include "qdrawwidget.h"


QDrawWidget::QDrawWidget(QWidget *parent)
  : QWidget(parent)
  , m_nNumber(0)
  , m_nSelect(0)
{
  this->setMouseTracking(true);
}

void QDrawWidget::paintEvent(QPaintEvent *)
{
  int index = m_nNumber - 1;
  QPainter painter(this);
  QPen pen;
  pen.setColor(Qt::black);
  pen.setBrush(Qt::black);
  pen.setStyle(Qt::SolidLine);
  pen.setWidth(1);
  painter.setPen(pen);
  switch (index) {
    case start:
      painter.drawEllipse(m_ptf[start], 2, 2);
      break;
    case end:
      painter.drawEllipse(m_ptf[start], 2, 2);
      painter.drawEllipse(m_ptf[end], 2, 2);
      painter.drawLine(m_ptf[start], m_ptf[end]);
      break;
    case control1:
      painter.drawEllipse(m_ptf[start], 2, 2);
      painter.drawEllipse(m_ptf[end], 2, 2);
      painter.drawEllipse(m_ptf[control1], 2, 2);
      painter.drawLine(m_ptf[start], m_ptf[end]);
      break;
    case control2:
      {
        painter.drawEllipse(m_ptf[start], 2, 2);
        painter.drawEllipse(m_ptf[end], 2, 2);
        painter.drawEllipse(m_ptf[control1], 2, 2);
        painter.drawEllipse(m_ptf[control2], 2, 2);

        QPainterPath path(m_ptf[start]);
        path.cubicTo(m_ptf[control1] ,m_ptf[control2] ,m_ptf[end] );
        painter.drawPath(path);

        pen.setColor(Qt::red);
        pen.setWidth(3);
        painter.setPen(pen);
        const int SIZE = 20;
        double length = path.length();
        double per_len = length / (SIZE - 1);
        for (int i = 0; i < SIZE; ++i) {
          double percent = path.percentAtLength(i * per_len);
          QPointF ptf = path.pointAtPercent(percent);
          painter.drawPoint(ptf);
        }
      }
      break;
    default:
      break;
  }
}

void QDrawWidget::mousePressEvent(QMouseEvent *e)
{
  if (Qt::RightButton == e->button()) {
    m_nNumber = 0;
  }
  else if (Qt::LeftButton == e->button()) {
    QPointF ptf = e->pos();
    if (m_nNumber < number) {
      m_ptf[m_nNumber] = ptf;
      ++ m_nNumber;
    }
    else {
      if (ptf == m_ptf[control1]) {
        m_nSelect = control1;
      }
      else if (ptf == m_ptf[control2]) {
        m_nSelect = control2;
      }
    }
  }
  this->update();
}

void QDrawWidget::mouseReleaseEvent(QMouseEvent *e)
{
  if (Qt::LeftButton == e->button()) {
    m_nSelect = 0;
  }
}

void QDrawWidget::mouseMoveEvent(QMouseEvent *e)
{
  QPointF ptf = e->pos();
  constexpr double DIS = 10;
  if (m_nSelect == 0) {
    if (m_nNumber == number) {
      if (QLineF(ptf, m_ptf[control1]).length() < DIS) {
        QCursor::setPos(mapToGlobal(m_ptf[control1].toPoint()));
      }
      else if (QLineF(ptf, m_ptf[control2]).length() < DIS) {
        QCursor::setPos(mapToGlobal(m_ptf[control2].toPoint()));
      }
    }
  }
  else if (m_nSelect == control1) {
    m_ptf[control1] = ptf;
    this->update();
  }
  else if (m_nSelect == control2) {
    m_ptf[control2] = ptf;
    this->update();
  }
}

