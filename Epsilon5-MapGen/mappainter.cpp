#include "mappainter.h"
#include <QDebug>

MapPainter::MapPainter(QString name, QSize size, QImage background, QWidget *parent) :
    QWidget(parent), _name(name), _size(size), _background(background)
{
    qDebug() << Q_FUNC_INFO << _name << _size;// << _background;
}
