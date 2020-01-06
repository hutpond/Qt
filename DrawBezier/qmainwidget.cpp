#include "qmainwidget.h"
#include "qdrawwidget.h"
#include "qfittingwidget.h"

QMainWidget::QMainWidget(QWidget *parent)
  : QWidget(parent)
{
  this->setMouseTracking(true);
  m_pWdgDraw = new QDrawWidget(this);
  m_pWdgFitting = new QFittingWidget(this);
  m_pWdgDraw->hide();
  //m_pWdgFitting->hide();
}

QMainWidget::~QMainWidget()
{

}

void QMainWidget::resizeEvent(QResizeEvent *)
{
  m_pWdgDraw->setGeometry(this->rect());
  m_pWdgFitting->setGeometry(this->rect());
}
