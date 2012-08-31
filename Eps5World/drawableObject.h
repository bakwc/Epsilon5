#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include <QString>
#include <QVector>

struct DrawableObject
{
    double x,y,angle;
    QString imageName;
};

typedef QVector<DrawableObject> DrawableObjects;

#endif // DRAWABLEOBJECT_H
