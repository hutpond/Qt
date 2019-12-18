#ifndef QVEHICLEWIDGET_H
#define QVEHICLEWIDGET_H

#include "qbaseshowwidget.h"

struct MapPoint;

class QVehicleWidget : public QBaseShowWidget
{
  Q_OBJECT
public:
  explicit QVehicleWidget(QWidget *parent = nullptr);

protected slots:
  void setReferencePoints(const QList<QSharedPointer<MapPoint>> &);

protected:
  virtual void drawImage() final;
  virtual void calcMapRect() final;

  void drawReference(QPainter &);

signals:

private:
  QList<QSharedPointer<QPointF>> m_listReference;
};

#endif // QVEHICLEWIDGET_H
