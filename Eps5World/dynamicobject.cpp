#include "dynamicobject.h"

DynamicObject::DynamicObject(QObject *parent) :
    QObject(parent)
{
    _x=0;
    _y=0;
    _vx=0;
    _vy=0;
    _angle=0;
}
