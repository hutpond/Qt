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

protected:
  virtual void resizeEvent(QResizeEvent *) final;

private:
  QHmiTableModel *m_pObjModel;
  QHmiTableView *m_pWdgView;
};
#endif // QHMITABLEWIDGET_H
