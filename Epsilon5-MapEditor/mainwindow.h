// mainwindow.h
#pragma once
#include <QMainWindow>
#include <QAction>
#include "createmapdialog.h"
#include "mapcreator.h"
//------------------------------------------------------------------------------
class TSettings;
//------------------------------------------------------------------------------
class TMainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit TMainWindow(QWidget* parent = 0);
    ~TMainWindow();

public slots:
    void newAction();
    void openAction();
    void optionsAction();
    void objectsEditorAction();
    void mapsEditorAction();

private:
    void connectMapCreator();

private:
    TMapCreator* mMapPainter;
    QAction* mSaveAtc;
};
//------------------------------------------------------------------------------
