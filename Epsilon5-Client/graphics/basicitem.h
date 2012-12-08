#ifndef BASICITEM_H
#define BASICITEM_H

#include <QPainter>
#include <QPixmap>
#include <QVector>

class BasicItem
{
public:
    BasicItem();

    virtual void paint(QPainter *painter) = 0;

private:
    QPixmap pix;
};

class Animation
{
public:
    Animation(const QVector<QPixmap>& frames) :
        Frames(frames) {}

    void Anim()
    {
        if (Ind == Frames.size()-1)
            Ind = 0;
        else
            ++Ind;
    }

    QPixmap& GetPix() { Frames[Ind]; }

private:
    QVector<QPixmap>    Frames;
    int                 Ind;
};

#endif // BASICITEM_H
