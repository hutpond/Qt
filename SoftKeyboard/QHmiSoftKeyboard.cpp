#include "QHmiSoftKeyboard.h"

#include "QAlphabetKeyboard.h"
#include "QNumberKeyboard.h"

QHmiSoftKeyboard::QHmiSoftKeyboard(int board, QWidget *parent)
  : QWidget(parent)
{
  m_pWdgKeyboard[Alphabet] = new QAlphabetKeyboard(this);
  m_pWdgKeyboard[Number] = new QNumberKeyboard(this);
  this->setBoardIndex(board);

  for (int i = 0; i < Count; ++i) {
    connect(m_pWdgKeyboard[i], SIGNAL(switchBoard()),
            this, SLOT(onSwitchBoard()));
  }
}

QHmiSoftKeyboard::~QHmiSoftKeyboard()
{
}

void QHmiSoftKeyboard::resizeEvent(QResizeEvent *)
{
  for (int i = 0; i < Count; ++i) {
    m_pWdgKeyboard[i]->setGeometry(this->rect());
  }
}

void QHmiSoftKeyboard::onSwitchBoard()
{
  ++ m_nBoardIndex %= Count;
  this->setBoardIndex(m_nBoardIndex);
}

void QHmiSoftKeyboard::setBoardIndex(int board)
{
  m_nBoardIndex = board;
  for (int i = 0; i < Count; ++i) {
    m_pWdgKeyboard[i]->setVisible(i == m_nBoardIndex);
  }

}
