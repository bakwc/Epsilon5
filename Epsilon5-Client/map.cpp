#include "../utils/uexception.h"
#include "../utils/usettings.h"
#include "map.h"


TMap::TMap(QObject* parent)
    : QObject(parent)
    , Width(0)
    , Height(0)
    , Background(new QImage)
    , Loaded(false)
    , WHRatio(QPointF(1.0, 1.0))
{
}

void TMap::LoadMap(QString map) {
    USettings settings;
    settings.Load("maps/" + map + "/config.ini");
    QString color = settings.GetParameter("color");
    Color = QColor(color);
    Background->load("maps/" + map + "/background.png");
    Width = settings.GetParameter("width");
    Height = settings.GetParameter("height");
    Loaded = true;
    WHRatio = QPointF(1.0, 1.0);
    if( Width && Height ) {
        // 1.0 means max size, other always less than 1
        WHRatio = QPointF(Width > Height ?  1.0 : (qreal)Width / Height,
                          Width > Height ? (qreal)Height / Width : 1.0);
    }
}

TMap::~TMap() {
    if (Background) {
        delete Background;
    }
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
    painter.fillRect(0, 0, frameSize.width(), frameSize.height(), Color);
    painter.drawImage(-cutX, -cutY, *Background);
}

size_t TMap::GetWidth()
{
    return Width;
}

size_t TMap::GetHeight()
{
    return Height;
}

QSize TMap::GetMinimapSize(quint8 maxMinimapSize)
{
    return QSize(maxMinimapSize * WHRatio.x(), maxMinimapSize * WHRatio.y());
}

QPoint TMap::GetObjectPosOnMinimap(int objectPosX, int objectPosY, quint8 maxMinimapSize)
{
    return QPoint(
        ((qreal)objectPosX / Width + 0.5) * maxMinimapSize * WHRatio.x(),
        ((qreal)objectPosY / Height + 0.5) * maxMinimapSize * WHRatio.y());
}

QPoint TMap::GetObjectPosOnMinimap(QPoint objectPos, quint8 maxMinimapSize)
{
    return GetObjectPosOnMinimap(objectPos.x(), objectPos.y(), maxMinimapSize);
}
