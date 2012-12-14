#pragma once
#include <QtCore>
#include <QColor>
//------------------------------------------------------------------------------
namespace containers
{
//------------------------------------------------------------------------------
enum ETeam {
    T_Neutral = 0,
    T_One,
    T_Second,
    ETEAM_SIZE      // MUST be the lastest!
};
//------------------------------------------------------------------------------
struct TMapInfo {
    QString name;
    quint32 width;
    quint32 height;
    QColor color;
};
//------------------------------------------------------------------------------
struct TObjectInfo {
    quint32 id;
    qint32 x;
    qint32 y;
    qreal angle;
};
//------------------------------------------------------------------------------
struct TRespawnInfo {
    qint32 x;
    qint32 y;
    quint32 captureRadius;
    quint32 spawnRadius;
    bool isCapturable;
    bool isMain;
    quint32 captureTime;
    ETeam team;
};
//------------------------------------------------------------------------------
struct TSObjectInfo {
    quint32 width;
    quint32 height;
    bool isDynamic;
    quint32 id;
    QString name;
};
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
