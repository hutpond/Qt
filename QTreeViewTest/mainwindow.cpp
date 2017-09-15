#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileSystemModel>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFileSystemModel *model = new QFileSystemModel;
    ui->treeView->setModel(model);
    //ui->treeView->expandAll(); ?无效
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *e)
{
    QMainWindow::showEvent(e);
}

void MainWindow::onBtnLoad()
{
    QFileSystemModel *model = dynamic_cast<QFileSystemModel*>
            (ui->treeView->model());
    if (model == NULL)    return;

    QString strPath = QFileDialog::getExistingDirectory(
                this, tr("Open Directory"), "C:/",
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
                );
    model->setRootPath(strPath);
    ui->treeView->setRootIndex(model->index(model->rootPath()));
}

void MainWindow::onBtnShow()
{
    QFileSystemModel *model = dynamic_cast<QFileSystemModel*>
            (ui->treeView->model());
    if (model == NULL)    return;

    QString strRootPath = model->rootPath();
    QModelIndex index = model->index(strRootPath);

    QStringList list;
    getChildrenIndex(ui->treeView, model, &index, &list);

    int nCount = list.count();
    for (int i = 0; i < nCount; ++i)
    {
        ui->textEdit->append(list.at(i));
    }
}

void MainWindow::getChildrenIndex(QTreeView * view, QFileSystemModel * model,
                      QModelIndex * index, QStringList * list)
{
    list->append(model->filePath(*index));

    view->expand(*index);
    int nRow = model->rowCount(*index);
    list->append(QString::number(nRow));
    for (int i = 0; i < nRow; ++i)
    {
        QModelIndex indexTmp = index->child(i, 0);
        getChildrenIndex(view, model, &indexTmp, list);
    }
    view->collapse(*index);
}
