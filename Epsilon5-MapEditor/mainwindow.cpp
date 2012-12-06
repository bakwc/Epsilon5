// mainwindow.cpp
#include <QListView>
#include <QMenuBar>
#include <QMessageBox>
#include "global.h"
#include "mainwindow.h"
//#include "openmapdialog.h"
#include "ui/configurationdialog.h"
#include "ui/objectseditorform.h"
#include "containers/maprespawncontainer.h"
//------------------------------------------------------------------------------
TMainWindow::TMainWindow(QWidget* parent)
    : QMainWindow(parent)
    , mObjectsEditorAction(new QAction(this))
    , mMapsEditorAction(new QAction(this))
    , mObjectsEditorWidget(new TObjectsEditorForm(this))
    , mMapsEditorWidget(new QWidget(this))
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
    // Tools menu
    QMenu* toolsMenu = new QMenu(tr("Tools"), menuBar);
    toolsMenu->addAction(tr("Options..."), this, SLOT(optionsAction()));
    toolsMenu->addSeparator();
    mObjectsEditorAction = toolsMenu->addAction(tr("Objects Editor"),
            this, SLOT(objectsEditorAction()));
    mMapsEditorAction = toolsMenu->addAction(tr("Maps Editor"),
            this, SLOT(mapsEditorAction()));
    mMapsEditorAction->setCheckable(true);
    mObjectsEditorAction->setCheckable(true);


    // Activate default widget
//    setCentralWidget(mObjectsEditorWidget);
//    setCentralWidget(mMapsEditorWidget);
//    mObjectsEditorAction->setChecked(true);
    mObjectsEditorWidget->hide();


    TMapRespawnContainer* container = new TMapRespawnContainer(this);
    QListView* listView = new QListView(this);
    listView->resize(400,300);
    setCentralWidget(listView);

    try {
        listView->setModel(container->model());
        container->loadFromFile(Global::Settings()->GetObjectsPath() + "/points.txt");
        container->addRespawn(TMapRespawnInfo());
        container->saveToFile(Global::Settings()->GetObjectsPath() + "/points-new.txt");
    } catch (const UException& ex) {
        qDebug( "%s", qPrintable(ex.what()) );
    }

    menuBar->addMenu(fileMenu);
    menuBar->addMenu(toolsMenu);
    this->setMenuBar(menuBar);
    setMinimumSize(600, 400);
    connect(this, SIGNAL(resized()), mObjectsEditorWidget, SLOT(updateDataList()));
}
//------------------------------------------------------------------------------
TMainWindow::~TMainWindow()
{
    Global::Settings()->SetWindowSize(size());
    Global::Settings()->SetWindowPos(pos());
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
//    setCentralWidget(mObjectsEditorWidget);
    mObjectsEditorAction->setChecked(true);
    mMapsEditorAction->setChecked(false);
}
//------------------------------------------------------------------------------
void TMainWindow::mapsEditorAction()
{
//    setCentralWidget(mMapsEditorWidget);
    mObjectsEditorAction->setChecked(false);
    mMapsEditorAction->setChecked(true);
}
//------------------------------------------------------------------------------
void TMainWindow::resizeEvent(QResizeEvent*)
{
    emit resized();
}
//------------------------------------------------------------------------------
