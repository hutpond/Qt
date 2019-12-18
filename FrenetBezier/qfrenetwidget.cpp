#include "qfrenetwidget.h"

#include <QPainter>
#include "qcenterwidget.h"

QFrenetWidget::QFrenetWidget(QWidget *parent)
  : QBaseShowWidget(FrenetCoord, parent)
{

}

void QFrenetWidget::setReferencePoints(const QList<QSharedPointer<MapPoint>> &points)
{
  m_listReference.clear();
  const int size_points = points.size();
  QSharedPointer<QPointF> point(new QPointF(0, 0));
  m_listReference.push_back(point);
  for (int i = 1; i < size_points; ++i) {
    QLineF linef(points[i]->east, points[i]->north,
                 points[i - 1]->east, points[i - 1]->north);
    point.reset(new QPointF(0, 0));
    point->setX(m_listReference[i - 1]->x() + linef.length());
    m_listReference.push_back(point);
  }

  this->doUpdate(true);
}

void QFrenetWidget::drawImage()
{
  m_image = QImage(m_rectPicture.width(), m_rectPicture.height(), QImage::Format_RGB888);
  QPainter painter(&m_image);
  painter.fillRect(m_image.rect(), QColor(230, 230, 230));
  this->drawMapBorder(painter);
  this->drawAxis(painter);
}

void QFrenetWidget::calcMapRect()
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

  const float map_height = m_fDisplayRatio * (x_max - x_min);
  const float map_width = map_height * m_rectPicture.height() / m_rectPicture.width();
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
