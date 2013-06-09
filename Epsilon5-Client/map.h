#pragma once

#include <QObject>
#include <QImage>
#include <QPainter>
#include <QPoint>
#include <QColor>
#include <QFile>
#include <QTextStream>
#include <QHash>
#include <QImage>
#include <QPixmap>
#include <QStringList>
#include <QDebug>
#include <QDir>


enum ETerrain {
  T_Water,
  T_Dirt
};

typedef QHash<ETerrain, QPixmap> ImageHash;

class TMap : public QObject {
    Q_OBJECT
public:
    TMap(QObject* parent = 0);
    ~TMap();
    size_t GetWidth();
    size_t GetHeight();
    QSize GetMinimapSize(quint8 maxMinimapSize);
    QPoint GetObjectPosOnMinimap(int objectPosX, int objectPosY, quint8 maxMinimapSize);
    QPoint GetObjectPosOnMinimap(QPoint objectPos, quint8 maxMinimapSize);

    // Draw background at correct position
    void DrawBackground(const QPoint& playerPos, const QSize& frameSize, QPainter &painter);
public slots:
    void LoadMap(const QString& map);
private:

    void makeBackgroundImage();

    QVector<ETerrain> loadTerrainMap();

    void LoadTiles();

    size_t Width;
    size_t Height;
    QPixmap* Background;
    QColor Color;
    bool Loaded;
    QPointF WHRatio;

    ImageHash Images;
};
