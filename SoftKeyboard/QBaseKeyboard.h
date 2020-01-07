#ifndef QBASEKEYBOARD_H
#define QBASEKEYBOARD_H

#include <QWidget>

class QHmiKeyboardButton;

class QBaseKeyboard : public QWidget
{
  Q_OBJECT

public:
  explicit QBaseKeyboard(QWidget *);

protected:
  virtual void resizeEvent(QResizeEvent *) final;

signals:
  void switchBoard();

protected:
  enum
  {
    ROW = 4,
    COLUMN = 10,
    SWITCH_INDEX = 30
  };

  struct KeyValue
  {
    int value;
    QString text;
    QString name;
  };

protected:
  QHmiKeyboardButton *m_pBtnKey[ROW * COLUMN];
};

#endif // QBASEKEYBOARD_H
