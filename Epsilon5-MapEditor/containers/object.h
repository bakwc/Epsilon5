// object.h
#pragma once
#include <QObject>
#include <QVector>
#include <QMetaType>
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
Q_DECLARE_METATYPE(TObjectItem)
//------------------------------------------------------------------------------
class TObjectContainer : public QObject {
    Q_OBJECT
public:
    typedef QVector<TObjectItem> TObjectsVector;

public:
    explicit TObjectContainer(QObject* parent = 0);
    int count();
    TObjectItem operator[](int value);

private:
    TObjectsVector mItems;
};
//------------------------------------------------------------------------------
