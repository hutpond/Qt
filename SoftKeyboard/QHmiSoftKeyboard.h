#ifndef QHMISOFTKEYBOARD_Hu
#define QHMISOFTKEYBOARD_H

#include <QWidget>

class QAlphabetKeyboard;

class QHmiSoftKeyboard : public QWidget
{
  Q_OBJECT

public:
  QHmiSoftKeyboard(QWidget *parent = nullptr);
  ~QHmiSoftKeyboard();

protected:
  virtual void resizeEvent(QResizeEvent *) final;

private:
  QAlphabetKeyboard *m_pWdgAlphabetKeyboard;
};
#endif // QHMISOFTKEYBOARD_H
