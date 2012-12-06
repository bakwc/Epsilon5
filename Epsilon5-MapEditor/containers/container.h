// container.h
#pragma once
#include <QObject>
#include <QStandardItemModel>
//------------------------------------------------------------------------------
class TContainer : public QObject
{
    Q_OBJECT
public:
    TContainer(QObject* parent = 0);
    QStandardItemModel* model() const;
    void clear();

protected:
    QStandardItemModel* mModel;
    quint32 mLastValidId;
};
//------------------------------------------------------------------------------
