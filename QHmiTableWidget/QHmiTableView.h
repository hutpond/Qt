#ifndef QHMITABLEVIEW_H
#define QHMITABLEVIEW_H

#include <QWidget>

class QHmiTableModel;

class QHmiTableView : public QWidget
{
  Q_OBJECT
public:
  explicit QHmiTableView(QWidget *parent = nullptr);
  void setHeaderVisible(bool, bool);
  void setModel(QHmiTableModel *);
  void setDataPrecision(int, int);

protected:
  virtual void resizeEvent(QResizeEvent *) final;
  virtual void paintEvent(QPaintEvent *) final;

signals:

private:
  QHmiTableModel *m_pObjModel;
  bool m_bHHeaderVisible;
  bool m_bVHeaderVisible;

  QVector<QRectF> m_vctHHeaderRects;
  QVector<QRectF> m_vctVHeaderRects;
  QVector<QVector<QRectF>> m_vctCellRects;

  QFont m_fontData;
  QFont m_fontHeader;

  int m_nIntegerDigital;
  int m_nDecimalDigital;
};

#endif // QHMITABLEVIEW_H
