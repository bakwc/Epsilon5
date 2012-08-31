/**
* @file
* Definition of MainDisplay
*/
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

void MainDisplay::redraw(const DrawableObjects &objects)
{
    // TODO: Draw received objects
}
