// mapobjectitem.h
#pragma once
#include <QObject>
#include "containers/structures.h"
//------------------------------------------------------------------------------
namespace oldcontainers
{
//------------------------------------------------------------------------------
class TMapObjectItem : public QObject
{
    Q_OBJECT
public:
    TMapObjectItem(QObject* parent = 0);
    TMapObjectItem(const TMapObjectInfo& objectInfo,
                   QObject* parent = 0);
    TMapObjectItem(const TMapObjectItem& object);
    ~TMapObjectItem();
    TMapObjectItem& operator =(const TMapObjectItem& object);

    TMapObjectInfo* objectInfo() const;
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
}
//------------------------------------------------------------------------------
Q_DECLARE_METATYPE(oldcontainers::TMapObjectItem)
//------------------------------------------------------------------------------
