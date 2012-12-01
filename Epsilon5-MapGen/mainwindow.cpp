#include "mainwindow.h"
#include <QMenuBar>
#include <QMessageBox>
#include <stdexcept>

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
    try {
        _mapPainter = new MapCreator(_dialog.mapName(), _dialog.mapSize(), _dialog.mapBackground(),
                                     _dialog.mapPath(), _dialog.mapObjsPath());
    } catch (std::exception &e) {
        delete _mapPainter;
        qDebug("Error: %s", e.what());
        QMessageBox::critical(this, "Error", e.what());
        return;
    }

    this->setCentralWidget(_mapPainter);
}
