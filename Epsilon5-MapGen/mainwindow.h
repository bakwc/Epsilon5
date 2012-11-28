#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "createmapdialog.h"
#include "mappainter.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    
signals:
    
public slots:
    void openDialogSlot();

private:
    CreateMapDialog _dialog;
    MapPainter      *_mapPainter;
};

#endif // MAINWINDOW_H
