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

/*
 * 加载文件夹
 * 内容显示在TreeView中
 */
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

/*
 * 遍历QTreeView中的文件
 * 显示在QTextEdit中
 */
void MainWindow::onBtnShow()
{
    QFileSystemModel *model = dynamic_cast<QFileSystemModel*>
            (ui->treeView->model());
    if (model == NULL)    return;
    ui->textEdit->clear();

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

/*
 * 递归函数，通过view, model, index递归遍历model节点
 *
 */
void MainWindow::getChildrenIndex(QTreeView * view, QFileSystemModel * model,
                      QModelIndex * index, QStringList * list)
{
    list->append(model->filePath(*index));

    view->expand(*index);
    int nRow = model->rowCount(*index);
    for (int i = 0; i < nRow; ++i)
    {
        QModelIndex indexTmp = index->child(i, 0);
        getChildrenIndex(view, model, &indexTmp, list);
    }
    view->collapse(*index);
}
