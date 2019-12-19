#include "qvehiclewidget.h"

#include <QPainter>
#include <QMouseEvent>
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
  this->drawBezier(painter);
}

void QVehicleWidget::drawReference(QPainter &painter)
{
  painter.save();
  QPen pen;
  pen.setWidth(1);
  pen.setColor(Qt::blue);
  painter.setPen(pen);

  QPolygonF pgf;
  for (const auto &point : m_listReference) {
    pgf << QPointF(point->x(), point->y());
  }
  pgf = m_transform.map(pgf);
  painter.drawPolyline(pgf);
  painter.restore();
}

void QVehicleWidget::drawBezier(QPainter &painter)
{
  painter.save();

  QPen pen;
  pen.setWidth(2);

  const int size_points = m_ptfClicked.size();
  for (int i = 0; i < size_points; ++i) {
    if (i < 2) {
      pen.setColor(Qt::darkMagenta);
    }
    else if (i < 4) {
      pen.setColor(Qt::darkGreen);
    }
    else {
      pen.setColor(Qt::black);
    }
    painter.setPen(pen);

    QPointF ptf = m_transform.map(*m_ptfClicked[i]);
    painter.drawEllipse(ptf, 4, 4);
  }

  if (size_points >= 4) {
    QPainterPath path;
    path.moveTo(*m_ptfClicked[0]);
    path.cubicTo(*m_ptfClicked[2], *m_ptfClicked[3], *m_ptfClicked[1]);
    path = m_transform.map(path);

    pen.setWidth(2);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.drawPath(path);
  }

  QPolygonF pgf;
  for (const auto &point : m_ptfBezier) {
    pgf << *point;
  }
  if (pgf.size() > 0) {
    pgf = m_transform.map(pgf);

    pen.setWidth(2);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawPolyline(pgf);
  }

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

void QVehicleWidget::mousePressEvent(QMouseEvent *e)
{
  QBaseShowWidget::mousePressEvent(e);

  if (e->button() == Qt::LeftButton) {
    if (m_ptfClicked.size() <= 5) {
      QSharedPointer<QPointF> ptf(new QPointF);
      *ptf = m_ptfMouseMove;
      QTransform inverted = m_transform.inverted();
      *ptf = inverted.map(*ptf);
      if (m_ptfClicked.size() == 5) {
        *m_ptfClicked[4] = *ptf;
      }
      else {
        m_ptfClicked.push_back(ptf);
      }
    }
  }
  else {
    m_ptfClicked.clear();
  }

  m_ptfBezier.clear();
  QList<QSharedPointer<QPointF>> listBezier;
  if (m_ptfClicked.size() >= 4) {
    QPainterPath path;
    path.moveTo(*m_ptfClicked[0]);
    path.cubicTo(*m_ptfClicked[2], *m_ptfClicked[3], *m_ptfClicked[1]);

    const int size_points = 50;
    for (int i = 0; i <= size_points; ++i) {
      double percent = (double)i / size_points;
      QPointF ptf = path.pointAtPercent(percent);

      QSharedPointer<QPointF> ptfPtr(new QPointF(ptf.x(), ptf.y()));
      m_ptfBezier.push_back(ptfPtr);

      double s, l;
      this->xyToSl(ptf, s, l);

      ptfPtr.reset(new QPointF(s, l));
      listBezier.push_back(ptfPtr);
    }
    emit bezierPoints(listBezier);
  }

  QList<QSharedPointer<QPointF>> listClicked;
  for (const auto &point : m_ptfClicked) {
    double s, l;
    this->xyToSl(*point, s, l);

    QSharedPointer<QPointF> ptf(new QPointF(s, l));
    listClicked.push_back(ptf);
  }
  emit clickedPoints(listClicked);
  this->doUpdate(true);
}

/**
 * @brief xy坐标转换为sl坐标
 * @param ptfXy: 车体坐标系，x, 车头正向, y, 车左侧
 * @param s: sl坐标系, s, 参考线切线方向
 * @param s: sl坐标系, l, 参考线垂直向左

 * @return
*/
void QVehicleWidget::xyToSl(const QPointF &ptfXy, double &s, double &l)
{
  const int size_points = m_listReference.size();
  int index = -1;
  for (int i = 0; i < size_points - 1; ++i) {
    QLineF linef(m_listReference[i]->x(), m_listReference[i]->y(),
                 m_listReference[i + 1]->x(), m_listReference[i + 1]->y());
    QLineF linef2(m_listReference[i]->x(), m_listReference[i]->y(), ptfXy.x(), ptfXy.y());
    double angle = linef.angleTo(linef2);
    if (angle > 90 && angle < 270) {
      continue;
    }

    linef = QLineF(m_listReference[i + 1]->x(), m_listReference[i + 1]->y(),
        m_listReference[i]->x(), m_listReference[i]->y());
    linef2 = QLineF(m_listReference[i + 1]->x(), m_listReference[i + 1]->y(),
        ptfXy.x(), ptfXy.y());
    angle = linef.angleTo(linef2);
    if (angle <= 90 || angle >= 270) {
      index = i;
      break;
    }
  }
  if (index == -1) {
    l = 1.0e8;
    for (int i = 0; i < size_points; ++i) {
      double len = QLineF(m_listReference[i]->x(), m_listReference[i]->y(), ptfXy.x(), ptfXy.y()).length();
      if (l > len) {
        index = i;
        l = len;
      }
    }
    s = this->calcS(index);
    if (index > 1 && index < size_points - 1) {
      double angle = QLineF(ptfXy, QPointF(m_listReference[index - 1]->x(), m_listReference[index - 1]->y())).
          angleTo(QLineF(ptfXy, QPointF(m_listReference[index + 1]->x(), m_listReference[index + 1]->y())));
      if (angle < 180) {
        l *= -1;
      }
    }
    return;
  }

  QLineF linef(m_listReference[index]->x(), m_listReference[index]->y(),
               m_listReference[index + 1]->x(), m_listReference[index + 1]->y());
  QLineF linef2(ptfXy.x(), ptfXy.y(), ptfXy.x(), ptfXy.y() + 1);
  linef2.setAngle(linef.normalVector().angle());

  QPointF ptfInter;
  QLineF::IntersectType type = linef.intersect(linef2, &ptfInter);
  if (type == QLineF::NoIntersection) {
    return;
  }

  l = QLineF(ptfXy, ptfInter).length();
  double angle = QLineF(
        ptfXy, QPointF(m_listReference[index]->x(), m_listReference[index]->y())).angleTo(
        QLineF(ptfXy, QPointF(m_listReference[index + 1]->x(), m_listReference[index + 1]->y())));
  if (angle < 180) {
    l *= -1;
  }
  s = QLineF(m_listReference[index]->x(), m_listReference[index]->y(), ptfInter.x(), ptfInter.y()).length();
  s += this->calcS(index);

  return;
}

double QVehicleWidget::calcS(int index)
{
  double s = 0;
  for (int i = 1; i < index; ++i) {
    QLineF linef(m_listReference[i - 1]->x(), m_listReference[i - 1]->y(),
        m_listReference[i]->x(), m_listReference[i]->y());
    s += linef.length();
  }
  return s;
}

