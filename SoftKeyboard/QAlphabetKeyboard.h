#ifndef QALPHABETKEYBOARD_H
#define QALPHABETKEYBOARD_H

#include <QWidget>

class QHmiKeyboardButton;

class QAlphabetKeyboard : public QWidget
{
  enum
  {
    Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Y, Key_U, Key_I, Key_O, Key_P,
    Key_A, Key_S, Key_D, Key_F, Key_G, Key_H, Key_J, Key_K, Key_L, Key_Del,
    Key_Swith, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_N, Key_M, Key_SP, Key_Enter,
    Key_Count
  };

  struct KeyValue
  {
    int value;
    QString text;
    QString name;
  };

  Q_OBJECT
public:
  explicit QAlphabetKeyboard(QWidget *parent = nullptr);

protected:
  virtual void resizeEvent(QResizeEvent *) final;

protected slots:
signals:

private:
  QHmiKeyboardButton *m_pBtnKey[Key_Count];
  KeyValue m_KeyValues[Key_Count] = {
    {Qt::Key_Q, "Q", "Q"}, {Qt::Key_W, "W", "W"}, {Qt::Key_E, "E", "E"}, {Qt::Key_R, "R", "R"}, {Qt::Key_T, "T", "T"},
    {Qt::Key_Y, "Y", "Y"}, {Qt::Key_U, "U", "U"}, {Qt::Key_I, "I", "I"}, {Qt::Key_O, "O", "O"}, {Qt::Key_P, "P", "P"},
    {Qt::Key_A, "A", "A"}, {Qt::Key_S, "S", "S"}, {Qt::Key_D, "D", "D"}, {Qt::Key_F, "F", "F"}, {Qt::Key_G, "G", "G"},
    {Qt::Key_H, "H", "H"}, {Qt::Key_J, "J", "J"}, {Qt::Key_K, "K", "K"}, {Qt::Key_L, "L", "L"}, {Qt::Key_Backspace, "", "x"},
    {-1, "", "SW"}, {Qt::Key_Z, "Z", "Z"}, {Qt::Key_X, "X", "X"}, {Qt::Key_C, "C", "C"}, {Qt::Key_V, "V", "V"},
    {Qt::Key_B, "B", "B"}, {Qt::Key_N, "N", "N"}, {Qt::Key_M, "M", "M"}, {Qt::Key_Space, " ", "SP"}, {Qt::Key_Enter, "", "En"},
  };
};

#endif // QALPHABETKEYBOARD_H
