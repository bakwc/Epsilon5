#ifndef BULLET_H
#define BULLET_H

#include "basicitem.h"

namespace basic {

class Bullet : public BasicItem
{
public:
    Bullet();

    QRectF boundingRect() const;
};

}

#endif // BULLET_H
