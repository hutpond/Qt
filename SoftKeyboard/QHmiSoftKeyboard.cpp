#include "QHmiSoftKeyboard.h"

#include "QAlphabetKeyboard.h"

QHmiSoftKeyboard::QHmiSoftKeyboard(QWidget *parent)
  : QWidget(parent)
{
  m_pWdgAlphabetKeyboard = new QAlphabetKeyboard(this);
}

QHmiSoftKeyboard::~QHmiSoftKeyboard()
{
}

void QHmiSoftKeyboard::resizeEvent(QResizeEvent *)
{
  m_pWdgAlphabetKeyboard->setGeometry(this->rect());
}

