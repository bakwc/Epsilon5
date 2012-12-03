// mainwindow.cpp
#include <QMenuBar>
#include <QMessageBox>
#include "global.h"
#include "mainwindow.h"
#include "openmapdialog.h"
//------------------------------------------------------------------------------
TMainWindow::TMainWindow(QWidget* parent)
    : QMainWindow(parent) {
    // Relocate window
    resize(Global::Settings()->GetWindowSize());
    move(Global::Settings()->GetWindowPos());

    QMenuBar* menuBar = new QMenuBar(this);
    QMenu* menu = new QMenu(tr("File"), this);
    menu->addAction(tr("New"), this, SLOT(newDialogSlot()));
    menu->addAction(tr("Open"), this, SLOT(openDialogSlot()));
    mSaveAtc = menu->addAction(tr("Save"));
    menu->addSeparator();
    menu->addAction(tr("Quit"), this, SLOT(close()), QKeySequence("F12"));
    menuBar->addMenu(menu);
    this->setMenuBar(menuBar);
}
//------------------------------------------------------------------------------
TMainWindow::~TMainWindow() {
    Global::Settings()->SetWindowSize(size());
    Global::Settings()->SetWindowPos(pos());
}
//------------------------------------------------------------------------------
void TMainWindow::newDialogSlot() {
    TCreateMapDialog dialog(this);
    if (!dialog.exec()) {
        return;
    }
    try {
        mMapPainter = new TMapCreator(dialog.mapName(), dialog.mapSize(),
                dialog.mapBackground(), dialog.mapPath(),
                dialog.mapObjsPath(), this);
        connectMapCreator();
    } catch (std::exception& e) {
        //delete mMapPainter;
        qDebug("Error: %s", e.what());
        QMessageBox::critical(this, "Error", e.what());
        return;
    }
}
//------------------------------------------------------------------------------
void TMainWindow::openDialogSlot() {
    TOpenMapDialog d(this);
    if (!d.exec()) {
        return;
    }
    try {
        mMapPainter = new TMapCreator(d.mapDir(), d.objDir(), this);
        connectMapCreator();
    } catch (std::exception& e) {
        //delete mMapPainter;
        qDebug("Error: %s", e.what());
        QMessageBox::critical(this, "Error", e.what());
        return;
    }
}
//------------------------------------------------------------------------------
void TMainWindow::connectMapCreator() {
    connect(mSaveAtc, SIGNAL(triggered()), mMapPainter, SLOT(save()));
    this->setCentralWidget(mMapPainter);
}
//------------------------------------------------------------------------------
