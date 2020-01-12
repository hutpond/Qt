#include "QHmiTableWidget.h"

#include "QHmiTableModel.h"
#include "QHmiTableView.h"

QHmiTableWidget::QHmiTableWidget(int row, int column, QWidget *parent)
  : QWidget(parent)
{
  m_pWdgView = new QHmiTableView(this);
  m_pObjModel = new QHmiTableModel(this);
  m_pObjModel->setRowColumn(row, column);
  m_pWdgView->setModel(m_pObjModel);

  connect(m_pWdgView, SIGNAL(selected(int,int)), this, SIGNAL(selected(int,int)));
}

QHmiTableWidget::~QHmiTableWidget()
{
}

void QHmiTableWidget::resizeEvent(QResizeEvent *)
{
  m_pWdgView->setGeometry(this->rect());
}

void QHmiTableWidget::setHeaderVisible(bool hVisible, bool vVisible)
{
  m_pWdgView->setHeaderVisible(hVisible, vVisible);
}

void QHmiTableWidget::setHeaderHeightPercent(float percent)
{
  m_pWdgView->setHeaderHeightPercent(percent);
}

void QHmiTableWidget::setHeaderWidthPercent(float percent)
{
  m_pWdgView->setHeaderWidthPercent(percent);
}

void QHmiTableWidget::setDataPrecision(int integer, int decimal)
{
  m_pWdgView->setDataPrecision(integer, decimal);
}

void QHmiTableWidget::setHHeader(const QStringList &headers)
{
  m_pObjModel->setHHeader(headers);
}

void QHmiTableWidget::setVHeader(const QStringList &headers)
{
  m_pObjModel->setVHeader(headers);
}

void QHmiTableWidget::setData(int row, int column, double data, bool changed)
{
  m_pObjModel->setData(row, column, data, changed);
}
