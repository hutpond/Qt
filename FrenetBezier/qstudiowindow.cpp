#include "qstudiowindow.h"

#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>

#include "qcenterwidget.h"

QStudioWindow::QStudioWindow(QWidget *parent)
  : QMainWindow(parent)
{
  m_pWdgCentral = new QCenterWidget(this);
  this->setCentralWidget(m_pWdgCentral);

  this->createMenu();
}

QStudioWindow::~QStudioWindow()
{
}


void QStudioWindow::createMenu()
{
  QMenu *menu = menuBar()->addMenu(QStringLiteral("&File"));
  menu->addAction(QStringLiteral("Load Reference"), this, SLOT(onActionLoadReference()));
}

void QStudioWindow::onActionLoadReference()
{
  QString fileName = QFileDialog::getOpenFileName(this,
        tr("Load Reference"), getenv("HOME"), tr("Reference Files (*.bin)"));
  if (!fileName.isEmpty()) {
    m_pWdgCentral->loadReference(fileName);
  }
}
