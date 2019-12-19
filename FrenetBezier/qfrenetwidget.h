#ifndef QFRENETWIDGET_H
#define QFRENETWIDGET_H

#include "qbaseshowwidget.h"

struct MapPoint;

class QFrenetWidget : public QBaseShowWidget
{
  Q_OBJECT
public:
  explicit QFrenetWidget(QWidget *parent = nullptr);

protected:
  virtual void drawImage() final;
  virtual void calcMapRect() final;

  void drawBezier(QPainter &);

signals:

protected slots:
  void setReferencePoints(const QList<QSharedPointer<MapPoint>> &);
  void onClickedPoints(const QList<QSharedPointer<QPointF>> &);
  void onBezierPoints(const QList<QSharedPointer<QPointF>> &);

private:
  QList<QSharedPointer<QPointF>> m_listReference;
  QList<QSharedPointer<QPointF>> m_ptfClicked;
  QList<QSharedPointer<QPointF>> m_ptfBezier;
};

#endif // QFRENETWIDGET_H
