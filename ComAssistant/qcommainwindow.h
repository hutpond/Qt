#ifndef QCOMMAINWINDOW_H
#define QCOMMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class QComMainWindow;
}

class QComMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QComMainWindow(QWidget *parent = nullptr);
    ~QComMainWindow();

private:
    Ui::QComMainWindow *ui;
};

#endif // QCOMMAINWINDOW_H
