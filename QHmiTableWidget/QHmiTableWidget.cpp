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
}

QHmiTableWidget::~QHmiTableWidget()
{
}

void QHmiTableWidget::resizeEvent(QResizeEvent *)
{
  m_pWdgView->setGeometry(this->rect());
}
