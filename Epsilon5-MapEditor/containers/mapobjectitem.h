// mapobjectitem.h
#pragma once
#include <QObject>
#include "containers/structures.h"
//------------------------------------------------------------------------------
class TMapObjectItem : public QObject
{
    Q_OBJECT
public:
    TMapObjectItem(QObject* parent = 0);
    TMapObjectItem(const TMapObjectItem& object);
    TMapObjectItem(const TMapObjectInfo& objectInfo,
        QObject* parent = 0);
    ~TMapObjectItem();
    TMapObjectInfo objectInfo() const;
    QString serialize() const;
    bool isValid();
    bool isValid() const;

private:
    bool checkData();

private:
    TMapObjectInfo* mInfo;
    bool mValid;
};
//------------------------------------------------------------------------------
Q_DECLARE_METATYPE(TMapObjectItem)
//------------------------------------------------------------------------------
