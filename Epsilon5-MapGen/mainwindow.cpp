#include "mainwindow.h"
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QMenuBar *mBar = new QMenuBar;
    QMenu *m = new QMenu("File");
    m->addAction("New", &_mapDialog, SLOT(exec()));
    m->addAction("Open");
    mBar->addMenu(m);

    this->setMenuBar(mBar);
}
