// object.h
#pragma once
#include <QObject>
#include <QVector>
//------------------------------------------------------------------------------
struct TObject {
    quint32 id;
    quint32 width;
    quint32 height;
    bool isDynamic;
    QString name;
};
//------------------------------------------------------------------------------
class TObjectContainer : public QObject {
    Q_OBJECT
public:
    typedef QVector<TObject> TObjectsVector;

public:
    explicit TObjectContainer(QObject* parent = 0);
    int count();
    TObject operator[](int value);

private:
    TObjectsVector mItems;
};
//------------------------------------------------------------------------------
