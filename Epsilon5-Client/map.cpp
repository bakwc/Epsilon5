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
    , Background(new QImage)
    , Loaded(false)
{
}

void TMap::LoadMap(QString map) {
    Background->load("maps/" + map + "/background.png");
    Loaded = true;
}

TMap::~TMap()
{
    if(Background)
        delete Background;
}

QImage TMap::GetFrame(int x, int y, const QSize& frameSize) {
    if (!Loaded) {
        throw UException("Map not loaded!");
    }
    int centerX = Background->width() / 2;
    int centerY = Background->height() / 2;
    int newPekaPosX = centerX + x;
    int newPekaPosY = centerY + y;
    int cutX = newPekaPosX - frameSize.width() / 2;
    int cutY = newPekaPosY - frameSize.height() / 2;
    return Background->copy(cutX, cutY, frameSize.width(), frameSize.height());
}
