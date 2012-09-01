/**
* @file
* Definition of MainDisplay
*/
#include <QDebug>
#include <QPainter>
#include "maindisplay.h"
#include "ui_maindisplay.h"

MainDisplay::MainDisplay(QWidget *parent) :
    QGLWidget(parent),
    _currentFrame(new QImage(800,600,QImage::Format_ARGB32))
{
    this->resize(800,600);
}

MainDisplay::~MainDisplay()
{
}

void MainDisplay::start()
{
    qDebug() <<  this->format().doubleBuffer();
    startTimer(10); // TODO: Remove MN
}

void MainDisplay::redraw(const DrawableObjects &objects)
{
    _currentFrame->fill(Qt::black);
    QPainter painter(_currentFrame);
    QPen pen(Qt::green);
    pen.setWidth(3);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing);

    for (auto i=objects.begin();i!=objects.end();i++)
    {
        painter.drawEllipse(i->x,i->y,20,20);
    }
    this->update();
        /*
        qDebug() << objects[0].imageName
                 << QString::number(objects[0].x, 'f', 2)
                 << QString::number(objects[0].y, 'f', 2);
                 */
    // TODO: Draw received objects
}

void MainDisplay::timerEvent(QTimerEvent *event)
{
    emit requestRedrawObjects();
}

void MainDisplay::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawImage(0, 0, *_currentFrame);
    /*static quint32 counter=0;
    counter++;
    qDebug() << "Frames: " << counter;*/
}
