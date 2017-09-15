#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileSystemModel>
#include <QMetaObject>
#include <QStandardItem>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFileSystemModel *model = new QFileSystemModel;
    ui->treeView->setModel(model);

    model->setRootPath(QDir::currentPath());
    ui->treeView->setRootIndex(model->index(model->rootPath()));
    QModelIndex index = model->index(model->rootPath());
    ui->treeView->setCurrentIndex(index);
    qWarning() << model->fileName(index) <<
                  model->rootPath();

    qWarning() << model->rowCount(index) <<
                  model->columnCount(index);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *e)
{
    QMainWindow::showEvent(e);
}

void MainWindow::onBtnClicked()
{
    QAbstractItemModel * model = ui->treeView->model();
    QModelIndex index = ui->treeView->currentIndex();

//    while (index.parent().isValid())
//    {
//        qWarning() << index.data().toString() <<
//                      model->rowCount(index) <<
//                      model->columnCount(index);
//        index = index.parent();
//    }

    index = model->index(0,0);
    qWarning() << index.data().toString() <<
                  model->rowCount(index) <<
                  model->columnCount(index);
    while (index.child(0,0).isValid())
    {
        index = index.child(0,0);
        qWarning() << index.data().toString() <<
                      model->rowCount(index) <<
                      model->columnCount(index);
    }
}
