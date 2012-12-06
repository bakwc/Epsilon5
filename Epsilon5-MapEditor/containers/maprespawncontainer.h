// maprespawncontainer.h
#pragma once
#include <QObject>
#include "containers/structures.h"
#include "containers/container.h"
#include "containers/maprespawnitem.h"
//------------------------------------------------------------------------------
class TMapRespawnContainer : public QObject
{
    Q_OBJECT
public:
    TMapRespawnContainer(QObject* parent = 0);
    ~TMapRespawnContainer();
    void addRespawn(const TMapRespawnInfo& info);
//    void removeRespawn(const TMapRespawnItem& item);
    void removeRespawn(const QModelIndex& index);
    QStandardItemModel* model();
    void loadFromFile(const QString& fileName);
    void saveToFile(const QString& fileName);

private:
    QStandardItemModel* mModel;
};
//------------------------------------------------------------------------------
