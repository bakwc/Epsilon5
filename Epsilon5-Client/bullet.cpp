#include "bullet.h"

namespace basic {

Bullet::Bullet()
{
    Size = QSize(10, 10);
}

QRectF Bullet::boundingRect() const
{
    return QRectF(0, 0, 10, 10);
}

}
