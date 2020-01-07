#ifndef QNUMBERKEYBOARD_H
#define QNUMBERKEYBOARD_H

#include "QBaseKeyboard.h"

class QNumberKeyboard : public QBaseKeyboard
{
  Q_OBJECT
public:
  explicit QNumberKeyboard(QWidget *parent = nullptr);
private:
  KeyValue m_KeyValues[ROW * COLUMN] = {
    {Qt::Key_1, "1", "1"}, {Qt::Key_2, "2", "2"}, {Qt::Key_3, "3", "3"}, {Qt::Key_4, "4", "4"},
    {Qt::Key_5, "5", "5"}, {Qt::Key_6, "6", "6"}, {Qt::Key_7, "7", "7"}, {Qt::Key_8, "8", "8"},
    {Qt::Key_9, "9", "9"}, {Qt::Key_0, "0", "0"},

    {Qt::Key_Plus, "+", "+"}, {Qt::Key_Minus, "-", "-"}, {Qt::Key_multiply, "*", "*"},
    {Qt::Key_division, "/", "/"}, {Qt::Key_Equal, "=", "="}, {Qt::Key_Exclam, "!", "!"},
    {Qt::Key_Less, "<", "<"}, {Qt::Key_Greater, ">", ">"}, {Qt::Key_Percent, "%", "%"},
    {Qt::Key_Backspace, "", "x"},

    {Qt::Key_Period, ".", "."}, {Qt::Key_Comma, ",", ","}, {Qt::Key_ParenLeft, "(", "("},
    {Qt::Key_ParenRight, ")", ")"}, {Qt::Key_BracketLeft, "[", "["}, {Qt::Key_BracketRight, "]", "]"},
    {Qt::Key_QuoteLeft, "\"", "\""}, {Qt::Key_Space, " ", "Sp"},
    {Qt::Key_Up, "", "Up"}, {Qt::Key_Enter, "", "En"},

    {-1, "", "SW"}, {Qt::Key_AsciiCircum, "^", "^"}, {Qt::Key_NumberSign, "#", "#"},
    {Qt::Key_At, "@", "@"}, {Qt::Key_Dollar, "$", "$"}, {Qt::Key_Semicolon, ";", ";"},
    {Qt::Key_Colon, ":", ":"}, {Qt::Key_Left, "", "Lf"}, {Qt::Key_Down, "", "Dn"},
    {Qt::Key_Right, "", "Rt"}
  };
};

#endif // QNUMBERKEYBOARD_H
