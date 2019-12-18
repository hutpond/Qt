#include "qenuwidget.h"

#include <QPainter>
#include <QMouseEvent>
#include "qcenterwidget.h"

QEnuWidget::QEnuWidget(QWidget *parent)
  : QBaseShowWidget(EnuCoord, parent)
{
  m_fDisplayRatio = 1.2;
}

void QEnuWidget::setReferencePoints(const QList<QSharedPointer<MapPoint>> &points)
{
  m_listReference = points;
  this->calcMapRect();
  this->doUpdate(true);
}

void QEnuWidget::drawImage()
{
  m_image = QImage(m_rectPicture.width(), m_rectPicture.height(), QImage::Format_RGB888);
  QPainter painter(&m_image);
  painter.fillRect(m_image.rect(), QColor(230, 230, 230));
  this->drawMapBorder(painter);
  this->drawAxis(painter);

  this->drawReference(painter);
}

void QEnuWidget::drawReference(QPainter &painter)
{
  painter.save();
  QPen pen;
  pen.setWidth(1);

  for (const auto &point : m_listReference) {
    pen.setColor(point->dir == 0 ? Qt::blue : Qt::red);
    pen.setWidth(point->dir == 0 ? 1 : 2);
    painter.setPen(pen);

    QPointF ptf(point->east, point->north);
    ptf = m_transform.map(ptf);
    painter.drawEllipse(ptf, 4, 4);
  }
  painter.restore();
}

void QEnuWidget::calcMapRect()
{
  double x_min = 10000.0;
  double x_max = -10000.0;
  double y_min = 10000.0;
  double y_max = -10000.0;
  for (const auto &point : m_listReference) {
    if (x_min > point->east) {
      x_min = point->east;
    }
    if (x_max < point->east) {
      x_max = point->east;
    }

    if (y_min > point->north) {
      y_min = point->north;
    }
    if (y_max < point->north) {
      y_max = point->north;
    }
  }

  const float map_height = m_fDisplayRatio * (y_max - y_min);
  const float map_width = map_height * m_rectPicture.width() / m_rectPicture.height();
  const float map_x = -(map_width - (x_max + x_min)) / 2.0 - m_ptfTranslate.x();
  const float map_y = -(map_height - (y_max + y_min)) / 2.0 - m_ptfTranslate.y();
  m_rectfMap = QRectF(map_x, map_y, map_width, map_height);

  // 坐标转换
  m_transform.reset();
  m_transform.rotate(180, Qt::XAxis);
  m_transform.scale(m_rectPicture.width() / m_rectfMap.width(),
                    m_rectPicture.height() / m_rectfMap.height());
  m_transform.translate(-m_rectfMap.x(), -(m_rectfMap.y() + m_rectfMap.height()));
}

void QEnuWidget::mousePressEvent(QMouseEvent *e)
{
  QBaseShowWidget::mousePressEvent(e);

  QList<QSharedPointer<MapPoint>> listPoints;
  bool bSelect = false;
  for (auto &point : m_listReference) {
    point->dir = 0;
    if (!bSelect) {
      QPointF ptf(point->east, point->north);
      ptf = m_transform.map(ptf);
      QLineF linef(m_ptfMouseMove, ptf);
      bSelect = linef.length() < 4;
      if (bSelect) {
        point->dir = 1;
      }
    }
    if (bSelect && listPoints.size() < 50) {
      listPoints.push_back(point);
    }
  }

  if (listPoints.size() > 0) {
    selectPoints(listPoints);
  }
  this->doUpdate(true);
}
