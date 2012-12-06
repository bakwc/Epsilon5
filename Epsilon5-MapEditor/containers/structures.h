// structures.h
#pragma once
#include <QMetaType>
//------------------------------------------------------------------------------
enum ETeam {
    T_Neutral = 0,
    T_One,
    T_Second,
    ETEAM_SIZE      // MUST be last!
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
    QString name;
    quint32 width;
    quint32 height;

    TMapInfo();
    QString pack();
    bool unpack(const QString& string);
};
//------------------------------------------------------------------------------
struct TMapObjectInfo {
    quint32 id;
    qint32 x;
    qint32 y;
    qreal angle;

    TMapObjectInfo();
    QString pack();
    bool unpack(const QString& string);
};
//------------------------------------------------------------------------------
struct TMapRespawnInfo {
    qint32 x;
    qint32 y;
    quint32 captureRadius;
    quint32 spawnRadius;
    bool isCapturable;
    bool isMain;
    quint32 captureTime;
    ETeam team;

    TMapRespawnInfo();
    QString pack();
    bool unpack(const QString& string);
};
//------------------------------------------------------------------------------
Q_DECLARE_METATYPE(TObjectItem)
//------------------------------------------------------------------------------
