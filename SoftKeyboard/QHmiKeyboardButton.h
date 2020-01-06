#ifndef QHMIKEYBOARDBUTTON_H
#define QHMIKEYBOARDBUTTON_H

#include <QPushButton>

class QKeyEvent;

class QHmiKeyboardButton : public QPushButton
{
  Q_OBJECT
public:
  explicit QHmiKeyboardButton(QWidget *, int, const QString &, const QString &);

protected slots:
  void onPressed();
  void onReleased();

signals:
  void switchBoard();

private:
  int m_keyValue;
  QString m_strText;
  QKeyEvent *m_pKeyEvent;
};

#endif // QHMIKEYBOARDBUTTON_H
