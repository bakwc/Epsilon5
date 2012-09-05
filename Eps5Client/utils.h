#ifndef UTILS_H
#define UTILS_H

#include <QPoint>
#include <cmath>

const float PI=3.1415926f;

inline double getAngle(const QPoint& point)
{
    double x=point.x();
    double y=point.y();
    if (x>0) return atan(y/x);
    if (x<0 && y>0) return PI + atan(y/x);
    if (x<0 && y<0) return -PI + atan(y/x);
    if (x==0 && y>0) return PI/2;
    return -PI/2;
}

#endif // UTILS_H
