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
    saveAtc = m->addAction("Save");
    mBar->addMenu(m);

    this->setMenuBar(mBar);
}

void MainWindow::newDialogSlot()
{
    try {
        CreateMapDialog d(this);
        if (!d.exec())
            return;

        _mapPainter = new MapCreator(d.mapName(), d.mapSize(), d.mapBackground(),
                                     d.mapPath(), d.mapObjsPath());
    } catch (std::exception &e) {
        delete _mapPainter;
        qDebug("Error: %s", e.what());
        QMessageBox::critical(this, "Error", e.what());
        return;
    }

    connect(saveAtc, SIGNAL(triggered()), _mapPainter, SLOT(save()));
    this->setCentralWidget(_mapPainter);
}
