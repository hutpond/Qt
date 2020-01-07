#include "QNumberKeyboard.h"

#include "QHmiKeyboardButton.h"

QNumberKeyboard::QNumberKeyboard(QWidget *parent)
  : QBaseKeyboard(parent)
{
  for (int i = 0; i < ROW * COLUMN; ++i) {
    m_pBtnKey[i]->setButtonValue(m_KeyValues[i].value,
                                 m_KeyValues[i].text,
                                 m_KeyValues[i].name);
  }
}
