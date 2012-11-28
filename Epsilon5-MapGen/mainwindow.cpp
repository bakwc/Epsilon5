#include "mainwindow.h"
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QMenuBar *mBar = new QMenuBar;
    QMenu *m = new QMenu("File");
    m->addAction("New", &_dialog, SLOT(exec()));
    m->addAction("Open");
    mBar->addMenu(m);

    this->setMenuBar(mBar);

    connect(&_dialog, SIGNAL(accepted()), SLOT(openDialogSlot()));
}

void MainWindow::openDialogSlot()
{
    _mapPainter = new MapPainter(_dialog.mapName(), _dialog.mapSize(), _dialog.mapBackground());
    this->setCentralWidget(_mapPainter);
}
