#ifndef QENUWIDGET_H
#define QENUWIDGET_H

#include "qbaseshowwidget.h"

struct MapPoint;

class QEnuWidget : public QBaseShowWidget
{
  Q_OBJECT
public:
  explicit QEnuWidget(QWidget *);
  void setReferencePoints(const QList<QSharedPointer<MapPoint>> &);

protected:
  virtual void mousePressEvent(QMouseEvent *) final;

  virtual void drawImage() final;
  virtual void calcMapRect() final;

  void drawReference(QPainter &);

signals:
  void selectPoints(const QList<QSharedPointer<MapPoint>> &);

private:
  QList<QSharedPointer<MapPoint>> m_listReference;
};

#endif // QENUWIDGET_H
