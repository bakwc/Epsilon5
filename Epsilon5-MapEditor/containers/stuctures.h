// structures.h
#pragma once
#include <QMetaType>
//------------------------------------------------------------------------------
enum ETeam {
    T_Neutral = 0,
    T_One,
    T_Second
};
//------------------------------------------------------------------------------
struct TObjectItem {
    quint32 id;
    quint32 width;
    quint32 height;
    bool isDynamic;
    bool isValid;
    QString name;
    QString fileName;
};
//------------------------------------------------------------------------------
struct TMapInfo {
    quint32 width;
    quint32 height;
    QString name;
};
//------------------------------------------------------------------------------
struct TMapObjectInfo {
    quint32 id;
    qint32 x;
    qint32 y;
    qreal angle;
};
//------------------------------------------------------------------------------
struct TMapRespawnInfo {
    qint32 x;
    qint32 y;
    quint32 captureRadius;
    quint32 spawnRadius;
    bool isCapturable;
    bool isMain;
    quint32 captireTime;
    ETeam team;
};
//------------------------------------------------------------------------------
Q_DECLARE_METATYPE(TObjectItem)
Q_DECLARE_METATYPE(TMapInfo)
Q_DECLARE_METATYPE(TMapObjectInfo)
Q_DECLARE_METATYPE(TMapRespawnInfo)
//------------------------------------------------------------------------------
