// mainwindow.cpp
#include <QVBoxLayout>
#include <QListView>
#include <QMenuBar>
#include <QMessageBox>
#include "global.h"
#include "mainwindow.h"
#include "ui/configurationdialog.h"
#include "ui/mapseditorform.h"
//------------------------------------------------------------------------------
TMainWindow::TMainWindow(QWidget* parent)
    : QMainWindow(parent)
    , mMapsEditorAction(new QAction(this))
    , mMapsEditorWidget(new TMapsEditorForm(this))
{
    // Relocate window
    resize(Global::Settings()->GetWindowSize());
    move(Global::Settings()->GetWindowPos());
    if( Global::Settings()->GetWindowFullscreen() )
        fullscreenAction();

    QMenuBar* menuBar = new QMenuBar(this);
    // Tools menu
    QMenu* toolsMenu = new QMenu(tr("Tools"), menuBar);
    toolsMenu->addSeparator();
    mMapsEditorAction = toolsMenu->addAction(tr("Maps Editor"),
            this, SLOT(mapsEditorAction()), QKeySequence("Alt+2"));
    mMapsEditorAction->setCheckable(true);

    // Application menu
    QMenu* appMenu = new QMenu(tr("Application"), menuBar);
    appMenu->addAction(tr("Options..."), this, SLOT(optionsAction()));
    appMenu->addMenu(toolsMenu);
    appMenu->addSeparator();
    appMenu->addAction(tr("Quit"), this, SLOT(close()), QKeySequence("F12"));

    // Maplist menu
    QMenu* maplistMenu = new QMenu(tr("Maps"), menuBar);
    maplistMenu->addAction(tr("Open map folder..."),
            mMapsEditorWidget, SLOT(openMapFolderAction()));
    maplistMenu->addSeparator();
    maplistMenu->addAction(tr("Clear list"), mMapsEditorWidget,
            SLOT(clearMapListAction()));
    maplistMenu->addSeparator();
    maplistMenu->addAction(tr("Add new map"), mMapsEditorWidget,
            SLOT(addNewMapAction()));
    maplistMenu->addAction(tr("Save current map"), mMapsEditorWidget,
    SLOT(saveMapAction()), QKeySequence("F5"));
    maplistMenu->addAction(tr("Save all maps"), mMapsEditorWidget,
            SLOT(saveMapListAction()), QKeySequence("Shift+F5"));

    // Source objects list menu
    QMenu* sObjectsList = new QMenu(tr("Source objects"), menuBar);
    sObjectsList->addAction(tr("Open..."));
    sObjectsList->addSeparator();
    sObjectsList->addAction(tr("Clear list"));

    // Grid menu
    QMenu* gridMenu = new QMenu(tr("Grid"), menuBar);
    gridMenu->addAction(tr("Toggle grid"), mMapsEditorWidget,
            SLOT(toggleGridAction()), QKeySequence("F2"));
    gridMenu->addSeparator();
    gridMenu->addAction(tr("Set dark color"), mMapsEditorWidget,
            SLOT(setDarkGrid()));
    gridMenu->addAction(tr("Set light color"), mMapsEditorWidget,
            SLOT(setLightGrid()));
    gridMenu->addSeparator();
    gridMenu->addAction(tr("Set small size"), mMapsEditorWidget,
            SLOT(setSmallGrid()));
    gridMenu->addAction(tr("Set big size"), mMapsEditorWidget,
            SLOT(setBidGrid()));

    // View menu
    QMenu* viewMenu = new QMenu(tr("View"), menuBar);
    viewMenu->addAction(tr("Fullscreen"), this,
            SLOT(fullscreenAction()), QKeySequence("F11"));
    viewMenu->addAction(tr("Toggle panel mode"), mMapsEditorWidget,
            SLOT(toggleBrowserBox()), QKeySequence("F1"));
    viewMenu->addAction(tr("Reset zoom"), mMapsEditorWidget,
            SLOT(resetZoom()));
    viewMenu->addMenu(gridMenu);

    menuBar->addMenu(appMenu);
    menuBar->addMenu(maplistMenu);
    menuBar->addMenu(viewMenu);
    this->setMenuBar(menuBar);

    setMinimumSize(1024, 900);
    QWidget* widget = new QWidget(this);
    setCentralWidget(widget);
    QVBoxLayout* vbox = new QVBoxLayout(widget);
    vbox->addWidget(mMapsEditorWidget);
    widget->setLayout(vbox);
    mMapsEditorAction->setChecked(true);
}
//------------------------------------------------------------------------------
TMainWindow::~TMainWindow()
{
    Global::Settings()->SetWindowFullscreen(isFullScreen());
    if (!isFullScreen()) {
        Global::Settings()->SetWindowSize(size());
        Global::Settings()->SetWindowPos(pos());
    }
}
//------------------------------------------------------------------------------
void TMainWindow::optionsAction()
{
    TConfigurationDialog configDialog(this);
    configDialog.exec();
}
//------------------------------------------------------------------------------
void TMainWindow::mapsEditorAction()
{
    mMapsEditorWidget->show();
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
