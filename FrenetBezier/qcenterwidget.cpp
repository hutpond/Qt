#include "qcenterwidget.h"

#include <fstream>

#include "qfrenetwidget.h"
#include "qvehiclewidget.h"
#include "qenuwidget.h"

QCenterWidget::QCenterWidget(QWidget *parent) : QWidget(parent)
{
  m_pWdgFrenet = new QFrenetWidget(this);
  m_pWdgVehicle = new QVehicleWidget(this);
  m_pWdgEnu = new QEnuWidget(this);

  connect(m_pWdgEnu, SIGNAL(selectPoints(QList<QSharedPointer<MapPoint> >)),
          m_pWdgVehicle, SLOT(setReferencePoints(QList<QSharedPointer<MapPoint> >)));
  connect(m_pWdgEnu, SIGNAL(selectPoints(QList<QSharedPointer<MapPoint> >)),
          m_pWdgFrenet, SLOT(setReferencePoints(QList<QSharedPointer<MapPoint> >)));

  connect(m_pWdgVehicle, SIGNAL(clickedPoints(QList<QSharedPointer<QPointF> >)),
          m_pWdgFrenet, SLOT(onClickedPoints(QList<QSharedPointer<QPointF> >)));
  connect(m_pWdgVehicle, SIGNAL(bezierPoints(QList<QSharedPointer<QPointF> >)),
          m_pWdgFrenet, SLOT(onBezierPoints(QList<QSharedPointer<QPointF> >)));
}

void QCenterWidget::resizeEvent(QResizeEvent *)
{
  const int WIDTH = this->width();
  const int HEIGHT = this->height();

  m_pWdgFrenet->setGeometry(0, 0, WIDTH / 3.0, HEIGHT);
  m_pWdgVehicle->setGeometry(WIDTH / 3.0, 0, WIDTH / 3.0, HEIGHT);
  m_pWdgEnu->setGeometry(WIDTH * 2.0 / 3.0, 0, WIDTH / 3.0, HEIGHT);
}

void QCenterWidget::loadReference(const QString &name)
{
  QList<QSharedPointer<MapPoint>> listReference;

  std::ifstream in(name.toStdString(), std::ios::binary);

  int size_point = 0;
  in.read(reinterpret_cast<char*>(&size_point), sizeof(int));

  while (!in.eof()) {
    QSharedPointer<MapPoint> point(new MapPoint);
    point->dir = 0;

    in.read(reinterpret_cast<char*>(&point->id), sizeof(point->id));
    in.read(reinterpret_cast<char*>(&point->lat), sizeof(point->lat));
    in.read(reinterpret_cast<char*>(&point->lon), sizeof(point->lon));
    in.read(reinterpret_cast<char*>(&point->alt), sizeof(point->alt));
    in.read(reinterpret_cast<char*>(&point->pitch), sizeof(point->pitch));
    in.read(reinterpret_cast<char*>(&point->roll), sizeof(point->roll));
    in.read(reinterpret_cast<char*>(&point->yaw), sizeof(point->yaw));
    in.read(reinterpret_cast<char*>(&point->east), sizeof(point->east));
    in.read(reinterpret_cast<char*>(&point->north), sizeof(point->north));
    in.read(reinterpret_cast<char*>(&point->up), sizeof(point->up));
    in.read(reinterpret_cast<char*>(&point->left_w), sizeof(point->left_w));
    in.read(reinterpret_cast<char*>(&point->right_w), sizeof(point->right_w));
    in.read(reinterpret_cast<char*>(&point->dir), sizeof(point->dir));
    in.read(reinterpret_cast<char*>(&point->side), sizeof(point->side));

    listReference.push_back(point);
  }
  in.close();

  m_pWdgEnu->setReferencePoints(listReference);
}
