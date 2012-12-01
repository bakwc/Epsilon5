#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "createmapdialog.h"
#include "mapcreator.h"
#include <QAction>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    
signals:
    
public slots:
    void newDialogSlot();
    void openDialogSlot();

private:
    MapCreator      *_mapPainter;
    QAction         *saveAtc;

    void connectMapCreator();
};

#endif // MAINWINDOW_H
