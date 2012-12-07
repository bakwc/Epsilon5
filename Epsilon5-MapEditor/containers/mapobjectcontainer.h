// mapobjectcontainer.h
#pragma once
#include "containers/structures.h"
#include "containers/container.h"
#include "containers/mapobjectitem.h"
//------------------------------------------------------------------------------
class TMapObjectContainer : public TContainer
{
public:
    TMapObjectContainer(QObject* parent = 0);
    TMapObjectContainer(const TMapObjectContainer& container);
    ~TMapObjectContainer();
    TMapObjectContainer& operator =(const TMapObjectContainer& container);

    qint32 x(const QModelIndex& index) const;
    qint32 y(const QModelIndex& index) const;
    qreal angle(const QModelIndex& index) const;
    quint32 id(const QModelIndex& index) const;

    void setX(const QModelIndex& index, qint32 x);
    void setY(const QModelIndex& index, qint32 y);
    void setAngle(const QModelIndex& index, qreal angle);
    void setId(const QModelIndex& index, quint32 id);

    void addObject(const TMapObjectInfo& info);
    void removeObject(const QModelIndex& index);
    void loadFromFile(const QString& fileName);
    void saveToFile(const QString& fileName);
};
//------------------------------------------------------------------------------
