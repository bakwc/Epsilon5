// mainwindow.cpp
#include <QMenuBar>
#include <QMessageBox>
#include "global.h"
#include "mainwindow.h"
#include "openmapdialog.h"
//------------------------------------------------------------------------------
TMainWindow::TMainWindow(QWidget* parent)
    : QMainWindow(parent) {
    resize(Global::Settings()->GetWindowSize());
    QMenuBar* menuBar = new QMenuBar;
    QMenu* menu = new QMenu("File");
    menu->addAction("New", this, SLOT(newDialogSlot()));
    menu->addAction("Open", this, SLOT(openDialogSlot()));
    mSaveAtc = menu->addAction("Save");
    menuBar->addMenu(menu);
    this->setMenuBar(menuBar);
}
//------------------------------------------------------------------------------
TMainWindow::~TMainWindow() {
    Global::Settings()->SetWindowSize(size());
}
//------------------------------------------------------------------------------
void TMainWindow::newDialogSlot() {
    TCreateMapDialog dialog(this);
    if (!dialog.exec()) {
        return;
    }
    try {
        mMapPainter = new TMapCreator(dialog.mapName(), dialog.mapSize(),
                dialog.mapBackground(), dialog.mapPath(), dialog.mapObjsPath());
    } catch (std::exception& e) {
        delete mMapPainter;
        qDebug("Error: %s", e.what());
        QMessageBox::critical(this, "Error", e.what());
        return;
    }
    connectMapCreator();
}
//------------------------------------------------------------------------------
void TMainWindow::openDialogSlot() {
    OpenMapDialog d(this);
    if (!d.exec()) {
        return;
    }
    try {
        mMapPainter = new TMapCreator(d.mapDir(), d.objDir());
    } catch (std::exception& e) {
        delete mMapPainter;
        qDebug("Error: %s", e.what());
        QMessageBox::critical(this, "Error", e.what());
        return;
    }
    connectMapCreator();
}
//------------------------------------------------------------------------------
void TMainWindow::connectMapCreator() {
    connect(mSaveAtc, SIGNAL(triggered()), mMapPainter, SLOT(save()));
    this->setCentralWidget(mMapPainter);
}
//------------------------------------------------------------------------------
