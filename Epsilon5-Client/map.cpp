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

void TMap::DrawBackground(const QPoint& playerPos, const QSize& frameSize, QPainter& painter) {
    if (!Loaded) {
        throw UException("Map not loaded!");
    }
    int centerX = Background->width() / 2;
    int centerY = Background->height() / 2;
    int newPekaPosX = centerX + playerPos.x();
    int newPekaPosY = centerY + playerPos.y();
    int cutX = newPekaPosX - frameSize.width() / 2;
    int cutY = newPekaPosY - frameSize.height() / 2;

    painter.drawImage(-cutX, -cutY, *Background);
}
