#include <QFile>
#include <QTextStream>
#include <QHash>
#include <QImage>
#include <QStringList>
#include <QDebug>
#include <QDir>
#include "../utils/uexception.h"

#include "map.h"


TMap::TMap(QObject *parent)
    : QObject(parent)
    , Loaded(false)
{
}

void TMap::LoadMap(QString map) {
    Background = new QImage("maps/" + map + "/background.png");
    Loaded = true;
}

TMap::~TMap()
{
    if( Background )
        delete Background;
}

QImage TMap::GetFrame(int x, int y) {
    if (!Loaded) {
        throw UException("Map not loaded!");
    }
    int centerX = Background->width() / 2;
    int centerY = Background->height() / 2;
    int newPekaPosX = centerX + x;
    int newPekaPosY = centerY + y;
    int cutX = newPekaPosX - 400;
    int cutY = newPekaPosY - 300;
    return Background->copy(cutX, cutY, 800, 600);
}
