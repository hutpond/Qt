#ifndef QALPHABETKEYBOARD_H
#define QALPHABETKEYBOARD_H

#include "QBaseKeyboard.h"

class QAlphabetKeyboard : public QBaseKeyboard
{
  Q_OBJECT
public:
  explicit QAlphabetKeyboard(QWidget *parent = nullptr);

private:
  KeyValue m_KeyValues[ROW * COLUMN] = {
    {Qt::Key_Q, "Q", "Q"}, {Qt::Key_W, "W", "W"}, {Qt::Key_E, "E", "E"}, {Qt::Key_R, "R", "R"},
    {Qt::Key_T, "T", "T"}, {Qt::Key_Y, "Y", "Y"}, {Qt::Key_U, "U", "U"}, {Qt::Key_I, "I", "I"},
    {Qt::Key_O, "O", "O"}, {Qt::Key_P, "P", "P"},

    {Qt::Key_A, "A", "A"}, {Qt::Key_S, "S", "S"}, {Qt::Key_D, "D", "D"}, {Qt::Key_F, "F", "F"},
    {Qt::Key_G, "G", "G"}, {Qt::Key_H, "H", "H"}, {Qt::Key_J, "J", "J"}, {Qt::Key_K, "K", "K"},
    {Qt::Key_L, "L", "L"}, {Qt::Key_Backspace, "", "x"},

    {Qt::Key_Z, "Z", "Z"}, {Qt::Key_X, "X", "X"}, {Qt::Key_C, "C", "C"}, {Qt::Key_V, "V", "V"},
    {Qt::Key_B, "B", "B"}, {Qt::Key_N, "N", "N"}, {Qt::Key_M, "M", "M"},
    {Qt::Key_Space, " ", "Sp"}, {Qt::Key_Up, " ", "Up"}, {Qt::Key_Enter, "", "En"},

    {-1, "", "SW"}, {Qt::Key_Tab, "\t", "Tab"}, {Qt::Key_Question, "?", "?"},
    {Qt::Key_Slash, "\\", "\\"}, {Qt::Key_Ampersand, "&", "&&"}, {Qt::Key_Underscore, "_", "_"},
    {Qt::Key_Insert, "", "In"}, {Qt::Key_Left, "", "Lf"}, {Qt::Key_Down, "", "Dn"},
    {Qt::Key_Right, "", "Rt"}
  };
};

#endif // QALPHABETKEYBOARD_H
