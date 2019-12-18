#ifndef QCENTERWIDGET_H
#define QCENTERWIDGET_H

#include <QWidget>

class QFrenetWidget;
class QVehicleWidget;
class QEnuWidget;

struct MapPoint
{
  int id;

  double lat;
  double lon;
  double alt;

  double east;
  double north;
  double up;

  double pitch;
  double roll;
  double yaw;

  double left_w;
  double right_w;

  int dir;   // -1: left  0: line 1: right
  int side;  // -1: left  1: right
};

class QCenterWidget : public QWidget
{
  Q_OBJECT
public:
  explicit QCenterWidget(QWidget *parent = nullptr);

  void loadReference(const QString &);

protected:
  virtual void resizeEvent(QResizeEvent *) final;

signals:

private:
  QFrenetWidget *m_pWdgFrenet;
  QVehicleWidget *m_pWdgVehicle;
  QEnuWidget *m_pWdgEnu;
};

#endif // QCENTERWIDGET_H
