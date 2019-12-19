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
  virtual void mousePressEvent(QMouseEvent *) final;

  virtual void drawImage() final;
  virtual void calcMapRect() final;

  void drawReference(QPainter &);
  void drawBezier(QPainter &);

  void xyToSl(const QPointF &, double &, double &);
  double calcS(int);

signals:
  void clickedPoints(const QList<QSharedPointer<QPointF>> &);
  void bezierPoints(const QList<QSharedPointer<QPointF>> &);

private:
  QList<QSharedPointer<QPointF>> m_listReference;
  QList<QSharedPointer<QPointF>> m_ptfClicked;
  QList<QSharedPointer<QPointF>> m_ptfBezier;
};

#endif // QVEHICLEWIDGET_H
