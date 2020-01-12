#ifndef QHMITABLEWIDGET_H
#define QHMITABLEWIDGET_H

#include <QWidget>

class QHmiTableModel;
class QHmiTableView;

class QHmiTableWidget : public QWidget
{
  Q_OBJECT

public:
  QHmiTableWidget(int, int, QWidget *parent = nullptr);
  ~QHmiTableWidget();

  void setHeaderVisible(bool, bool);
  void setHeaderHeightPercent(float);
  void setHeaderWidthPercent(float);
  void setDataPrecision(int, int);

  void setHHeader(const QStringList &);
  void setVHeader(const QStringList &);
  void setData(int, int, double, bool = false);

protected:
  virtual void resizeEvent(QResizeEvent *) final;

signals:
  void selected(int, int);

private:
  QHmiTableModel *m_pObjModel;
  QHmiTableView *m_pWdgView;
};
#endif // QHMITABLEWIDGET_H
