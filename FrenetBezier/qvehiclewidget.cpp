#include "qvehiclewidget.h"

#include <QPainter>
#include "qcenterwidget.h"

QVehicleWidget::QVehicleWidget(QWidget *parent)
  : QBaseShowWidget(VehicleCoord, parent)
{
  m_fDisplayRatio = 1.2;
}

void QVehicleWidget::setReferencePoints(const QList<QSharedPointer<MapPoint>> &points)
{
  m_listReference.clear();
  const int size_points = points.size();
  if (size_points <= 2) {
    return;
  }
  m_fDisplayRatio = 1.2;

  QTransform transform;
  QLineF linef(points[3]->east, points[3]->north,
      points[0]->east, points[0]->north);
  double angle = linef.angle();
  transform.rotate(180 + angle);
  transform.translate(-points[0]->east, -points[0]->north);

  for (int i = 0; i < size_points; ++i) {
    QSharedPointer<QPointF> ptf(new QPointF);
    ptf->setX(points[i]->east);
    ptf->setY(points[i]->north);
    *ptf = transform.map(*ptf);

    m_listReference.push_back(ptf);
  }

  this->calcMapRect();
  this->doUpdate(true);
}

void QVehicleWidget::drawImage()
{
  m_image = QImage(m_rectPicture.width(), m_rectPicture.height(), QImage::Format_RGB888);
  QPainter painter(&m_image);
  painter.fillRect(m_image.rect(), QColor(230, 230, 230));
  this->drawMapBorder(painter);
  this->drawAxis(painter);

  this->drawReference(painter);
}

void QVehicleWidget::drawReference(QPainter &painter)
{
  painter.save();
  QPen pen;
  pen.setWidth(1);
  pen.setColor(Qt::black);
  painter.setPen(pen);

  QPolygonF pgf;
  for (const auto &point : m_listReference) {
    pgf << QPointF(point->x(), point->y());
  }
  pgf = m_transform.map(pgf);
  painter.drawPolyline(pgf);
  painter.restore();
}

void QVehicleWidget::calcMapRect()
{
  double x_min = 10000.0;
  double x_max = -10000.0;
  double y_min = 10000.0;
  double y_max = -10000.0;
  for (const auto &point : m_listReference) {
    if (x_min > point->x()) {
      x_min = point->x();
    }
    if (x_max < point->x()) {
      x_max = point->x();
    }

    if (y_min > point->y()) {
      y_min = point->y();
    }
    if (y_max < point->y()) {
      y_max = point->y();
    }
  }

  float map_width = m_fDisplayRatio * (x_max - x_min);
  float map_height = m_fDisplayRatio * (y_max - y_min);
  if (map_width / map_height > (double)m_rectPicture.height() / (double)m_rectPicture.width()) {
    map_height = map_width * m_rectPicture.width() / m_rectPicture.height();
  }
  else {
    map_width = map_height * m_rectPicture.height() / m_rectPicture.width();
  }
  const float map_x = -(map_width - (x_max + x_min)) / 2.0 - m_ptfTranslate.x();
  const float map_y = -(map_height - (y_max + y_min)) / 2.0 - m_ptfTranslate.y();
  m_rectfMap = QRectF(map_x, map_y, map_width, map_height);

  // 坐标转换
  m_transform.reset();
  m_transform.rotate(90);
  m_transform.rotate(180, Qt::YAxis);
  m_transform.scale(m_rectPicture.height() / m_rectfMap.width(),
                    m_rectPicture.width() / m_rectfMap.height());
  m_transform.translate(-(m_rectfMap.x() + m_rectfMap.width()),
                        -(m_rectfMap.y() + m_rectfMap.height()));
}
