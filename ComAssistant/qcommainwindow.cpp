#include "qcommainwindow.h"
#include "ui_qcommainwindow.h"

QComMainWindow::QComMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QComMainWindow)
{
    ui->setupUi(this);
}

QComMainWindow::~QComMainWindow()
{
    delete ui;
}
