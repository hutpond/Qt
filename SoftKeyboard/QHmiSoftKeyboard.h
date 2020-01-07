#ifndef QHMISOFTKEYBOARD_Hu
#define QHMISOFTKEYBOARD_H

#include <QWidget>

class QBaseKeyboard;

class QHmiSoftKeyboard : public QWidget
{
  Q_OBJECT

public:
  enum
  {
    Alphabet,
    Number,
    Count
  };

public:
  QHmiSoftKeyboard(int, QWidget *parent = nullptr);
  ~QHmiSoftKeyboard();

protected:
  virtual void resizeEvent(QResizeEvent *) final;

  void setBoardIndex(int);

protected slots:
  void onSwitchBoard();

private:
  QBaseKeyboard *m_pWdgKeyboard[Count];
  int m_nBoardIndex;
};
#endif // QHMISOFTKEYBOARD_H
