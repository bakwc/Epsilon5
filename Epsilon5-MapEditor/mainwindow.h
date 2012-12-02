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
    void newDialogSlot();
    void openDialogSlot();

private:
    void connectMapCreator();

private:
    TMapCreator* mMapPainter;
    QAction* mSaveAtc;
};
//------------------------------------------------------------------------------
