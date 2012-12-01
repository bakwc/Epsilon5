#include "mainwindow.h"
#include <QMenuBar>
#include <QMessageBox>
#include <stdexcept>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QMenuBar *mBar = new QMenuBar;
    QMenu *m = new QMenu("File");
    m->addAction("New", this, SLOT(newDialogSlot()));
    m->addAction("Open");
    mBar->addMenu(m);

    this->setMenuBar(mBar);
}

void MainWindow::newDialogSlot()
{
    CreateMapDialog d(this);
    if (!d.exec())
        return;

    try {
        _mapPainter = new MapCreator(d.mapName(), d.mapSize(), d.mapBackground(),
                                     d.mapPath(), d.mapObjsPath());
    } catch (std::exception &e) {
        delete _mapPainter;
        qDebug("Error: %s", e.what());
        QMessageBox::critical(this, "Error", e.what());
        return;
    }

    this->setCentralWidget(_mapPainter);
}
