#include "QHmiKeyboardButton.h"

#include <QApplication>
#include <QKeyEvent>

QHmiKeyboardButton::QHmiKeyboardButton(QWidget *parent, int value, const QString &text, const QString &name)
  : QPushButton(parent)
  , m_keyValue(value)
  , m_strText(text)
{
  this->setText(name);
  this->setFocusPolicy(Qt::NoFocus);

  connect(this, SIGNAL(pressed()), this, SLOT(onPressed()));
  connect(this, SIGNAL(released()), this, SLOT(onReleased()));
}

void QHmiKeyboardButton::onPressed()
{
  if (m_keyValue >= 0) {
    m_pKeyEvent = new QKeyEvent(QEvent::KeyPress, m_keyValue, Qt::NoModifier, m_strText);
    QCoreApplication::postEvent(QApplication::focusObject(), m_pKeyEvent);
  }
}

void QHmiKeyboardButton::onReleased()
{
  if (m_keyValue >= 0) {
    m_pKeyEvent = new QKeyEvent(QEvent::KeyRelease, m_keyValue, Qt::NoModifier, m_strText);
    QCoreApplication::postEvent(QApplication::focusObject(), m_pKeyEvent);
  }
  else {
    emit switchBoard();
  }
}
