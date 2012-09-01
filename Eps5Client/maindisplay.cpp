/**
* @file
* Definition of MainDisplay
*/
#include <QDebug>
#include "maindisplay.h"
#include "ui_maindisplay.h"

MainDisplay::MainDisplay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainDisplay)
{
    ui->setupUi(this);
}

MainDisplay::~MainDisplay()
{
    delete ui;
}

void MainDisplay::start()
{
    startTimer(80); // TODO: Remove MN
}

void MainDisplay::redraw(const DrawableObjects &objects)
{
    if (objects.size()>0)
        qDebug() << objects[0].imageName
                 << QString::number(objects[0].x, 'f', 2)
                 << QString::number(objects[0].y, 'f', 2);
    // TODO: Draw received objects
}

void MainDisplay::timerEvent(QTimerEvent *event)
{
    emit requestRedrawObjects();
}
