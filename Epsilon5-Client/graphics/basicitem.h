#pragma once

#include <QPainter>
#include <QPixmap>
#include <QVector>

class TBasicItem
{
public:
    TBasicItem();

    virtual void paint(QPainter *painter) = 0;

private:
    QPixmap pix;
};

class TAnimation
{
public:
    TAnimation(const QVector<QPixmap>& frames)
        : Frames(frames)
    {}

    void Anim() {
        if (Ind == Frames.size()-1)
            Ind = 0;
        else
            ++Ind;
    }

    QPixmap& GetPix() {
        return Frames[Ind];
    }
private:
    QVector<QPixmap>    Frames;
    int                 Ind;
};
