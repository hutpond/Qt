#ifndef QFRENETWIDGET_H
#define QFRENETWIDGET_H

#include "qbaseshowwidget.h"

struct MapPoint;

class QFrenetWidget : public QBaseShowWidget
{
  Q_OBJECT
public:
  explicit QFrenetWidget(QWidget *parent = nullptr);

  void setReferencePoints(const QList<QSharedPointer<MapPoint>> &);

protected:
  virtual void drawImage() final;
  virtual void calcMapRect() final;

signals:

private:
  QList<QSharedPointer<QPointF>> m_listReference;
};

#endif // QFRENETWIDGET_H
