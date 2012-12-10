// mainwindow.cpp
#include <QVBoxLayout>
#include <QListView>
#include <QMenuBar>
#include <QMessageBox>
#include "global.h"
#include "mainwindow.h"
//#include "openmapdialog.h"
#include "ui/configurationdialog.h"
//#include "ui/objectseditorform.h"
#include "ui/mapseditorform.h"
//#include "containers/maprespawncontainer.h"
//------------------------------------------------------------------------------
TMainWindow::TMainWindow(QWidget* parent)
    : QMainWindow(parent)
    , mObjectsEditorAction(new QAction(this))
    , mMapsEditorAction(new QAction(this))
//    , mObjectsEditorWidget(new TObjectsEditorForm(this))
    , mMapsEditorWidget(new TMapsEditorForm(this))
{
    // Relocate window
    resize(Global::Settings()->GetWindowSize());
    move(Global::Settings()->GetWindowPos());
    QMenuBar* menuBar = new QMenuBar(this);
    // File menu
    QMenu* fileMenu = new QMenu(tr("File"), menuBar);
    fileMenu->addAction(tr("New"), this, SLOT(newAction()));
    fileMenu->addAction(tr("Open"), this, SLOT(openAction()));
    mSaveAtc = fileMenu->addAction(tr("Save"));
    fileMenu->addSeparator();
    fileMenu->addAction(tr("Quit"), this, SLOT(close()), QKeySequence("F12"));
    // View menu
    QMenu* viewMenu = new QMenu(tr("View"), menuBar);
    viewMenu->addAction(tr("Fullscreen"), this,
            SLOT(fullscreenAction()), QKeySequence("F11"));
    viewMenu->addAction(tr("Toggle panel mode"), mMapsEditorWidget,
            SLOT(toggleBrowserBox()), QKeySequence("F1"));
    // Tools menu
    QMenu* toolsMenu = new QMenu(tr("Tools"), menuBar);
    toolsMenu->addAction(tr("Options..."), this, SLOT(optionsAction()));
    toolsMenu->addSeparator();
    mObjectsEditorAction = toolsMenu->addAction(tr("Objects Editor"),
            this, SLOT(objectsEditorAction()), QKeySequence("Alt+1"));
    mMapsEditorAction = toolsMenu->addAction(tr("Maps Editor"),
            this, SLOT(mapsEditorAction()), QKeySequence("Alt+2"));
    mMapsEditorAction->setCheckable(true);
    mObjectsEditorAction->setCheckable(true);
    menuBar->addMenu(fileMenu);
    menuBar->addMenu(viewMenu);
    menuBar->addMenu(toolsMenu);
    this->setMenuBar(menuBar);
    setMinimumSize(600, 400);
//    connect(this, SIGNAL(resized()), mObjectsEditorWidget, SLOT(updateDataList()));
    QWidget* widget = new QWidget(this);
    setCentralWidget(widget);
    QVBoxLayout* vbox = new QVBoxLayout(widget);
//    vbox->addWidget(mObjectsEditorWidget);
    vbox->addWidget(mMapsEditorWidget);
    widget->setLayout(vbox);
    // Activate default widget

//    mObjectsEditorAction->setChecked(true);
//    mMapsEditorWidget->hide();

    mMapsEditorAction->setChecked(true);
//    mObjectsEditorWidget->hide();

    mObjectsEditorAction->setDisabled(true);


//    mMapsEditorWidget->setObjectsModel(mObjectsEditorWidget->objectsModel());
}
//------------------------------------------------------------------------------
TMainWindow::~TMainWindow()
{
    if (!isFullScreen()) {
        Global::Settings()->SetWindowSize(size());
        Global::Settings()->SetWindowPos(pos());
    }
}
//------------------------------------------------------------------------------
void TMainWindow::newAction()
{
//    TCreateMapDialog dialog(this);
//    if (!dialog.exec()) {
//        return;
//    }
//    // TODO: temporary disabled
//    return;
//    try {
//        mMapPainter = new TMapCreator(dialog.mapName(), dialog.mapSize(),
//                dialog.mapBackground(), dialog.mapPath(),
//                dialog.mapObjsPath(), this);
//        connectMapCreator();
//    } catch (std::exception& e) {
//        //delete mMapPainter;
//        qDebug("Error: %s", e.what());
//        QMessageBox::critical(this, "Error", e.what());
//        return;
//    }
}
//------------------------------------------------------------------------------
void TMainWindow::openAction()
{
//    TOpenMapDialog d(this);
//    if (!d.exec()) {
//        return;
//    }
//    // TODO: temporary disabled
//    return;
//    try {
//        mMapPainter = new TMapCreator(d.mapDir(), d.objDir(), this);
//        connectMapCreator();
//    } catch (std::exception& e) {
//        //delete mMapPainter;
//        qDebug("Error: %s", e.what());
//        QMessageBox::critical(this, "Error", e.what());
//        return;
//    }
}
//------------------------------------------------------------------------------
void TMainWindow::connectMapCreator()
{
//    connect(mSaveAtc, SIGNAL(triggered()), mMapPainter, SLOT(save()));
//    this->setCentralWidget(mMapPainter);
}
//------------------------------------------------------------------------------
void TMainWindow::optionsAction()
{
    TConfigurationDialog configDialog(this);
    configDialog.exec();
}
//------------------------------------------------------------------------------
void TMainWindow::objectsEditorAction()
{
//    mObjectsEditorWidget->show();
    mMapsEditorWidget->hide();
    mObjectsEditorAction->setChecked(true);
    mMapsEditorAction->setChecked(false);
}
//------------------------------------------------------------------------------
void TMainWindow::mapsEditorAction()
{
//    mObjectsEditorWidget->hide();
    mMapsEditorWidget->show();
    mObjectsEditorAction->setChecked(false);
    mMapsEditorAction->setChecked(true);
}
//------------------------------------------------------------------------------
void TMainWindow::resizeEvent(QResizeEvent*)
{
    emit resized();
}
//------------------------------------------------------------------------------
void TMainWindow::fullscreenAction()
{
    setWindowState(windowState() ^ Qt::WindowFullScreen);
}
//------------------------------------------------------------------------------
