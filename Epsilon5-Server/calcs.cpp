#include "calcs.h"
#include <cmath>

QPointF GetDirection(const QPointF &a, const QPointF &b) {
    return -Normalize(a - b);
}


QPointF Normalize(const QPointF& point) {
    qreal max = std::max(fabs(point.x()), fabs(point.y()));
    return point / fabs(max);
}
