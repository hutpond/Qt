#include "QBaseKeyboard.h"

#include "QHmiKeyboardButton.h"

QBaseKeyboard::QBaseKeyboard(QWidget *parent)
  : QWidget(parent)
{
  for (int i = 0; i < ROW * COLUMN; ++i) {
    m_pBtnKey[i] = new QHmiKeyboardButton(this);
  }

  connect(m_pBtnKey[SWITCH_INDEX], SIGNAL(switchBoard()), this, SIGNAL(switchBoard()));
}

void QBaseKeyboard::resizeEvent(QResizeEvent *)
{
  const int WIDTH = this->width();
  const int HEIGHT = this->height();

  const float SPACE_X_PF = 0.007;
  const float SPACE_Y_PF = 0.03;

  const float BTN_W = WIDTH * (1.0f - SPACE_X_PF * (COLUMN + 1)) / COLUMN;
  const float BTN_H = HEIGHT * (1.0f - SPACE_Y_PF * (ROW + 1)) / ROW;
  const float BTN_LEN = qMin<float>(BTN_W, BTN_H);
  const float SPACE_X = (float)(WIDTH - BTN_LEN * COLUMN) / (float)(COLUMN + 1);
  const float SPACE_Y = (float)(HEIGHT - BTN_LEN * ROW) / (float)(ROW + 1);

  float fPosX = 0;
  float fPosY = 0;
  for (int i = 0; i < ROW; ++i) {
    fPosY = SPACE_Y + i * (SPACE_Y + BTN_LEN);
    for (int j = 0; j < COLUMN; ++j) {
      fPosX = SPACE_X + j * (SPACE_X + BTN_LEN);
      m_pBtnKey[i * COLUMN + j]->setGeometry(fPosX, fPosY, BTN_LEN, BTN_LEN);
    }
  }
}
