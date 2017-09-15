#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QTreeView;
class QFileSystemModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void showEvent(QShowEvent *);

    void getChildrenIndex(QTreeView *, QFileSystemModel *, QModelIndex *,
                          QStringList *);

protected slots:
    void onBtnLoad();
    void onBtnShow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
